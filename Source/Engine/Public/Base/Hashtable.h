#pragma once

#include <Base/NumericTypes.h>
#include <Base/Allocators.h>
#include <Base/Templated.h>
#include <Base/Optional.h>
#include <Base/Wrap.h>
#include <Base/Hash.h>

namespace Neowise {

    extern CFixedHeapAllocatorPolicy *GAlloc;

    template<class K, class V>
    struct HTBucket {
        K    key;
        V    value;
    };

    template<class K>
    struct HTBucket<K, void> {
        K key;
    };

    template<class K, class V>
    class HTIterator {
    public:
        using Bucket = TOptional<HTBucket<K, V>>;

        explicit HTIterator(Bucket* p) : ptr(p) {}
        virtual ~HTIterator() {}

        K& key() {
            return ptr->value().key;
        }
        
        const K& key() const {
            return ptr->value().key;
        }

        V& value() {
            return *(ptr->value().value);
        }

        const V& value() const {
            return *(ptr->value().value);
        }

        HTBucket<K, V>* operator->() const {
            return ptr->value();
        }

        HTBucket<K, V>& operator*() {
            return ptr->unwrap();
        }

        HTIterator operator++(int) {
            HTIterator tmp = *this;
            ++(ptr->value());
            return tmp;
        }

        HTIterator& operator++() {
            ++ptr;
            return *this;
        }

        operator TBool() const {
            return ptr;
        }

        TBool operator==(const HTIterator& it) const {
            return ptr == it.ptr;
        }

        TBool operator!=(const HTIterator& it) const {
            return ptr != it.ptr;
        }

    private:
        Bucket* ptr = nullptr;
    };

    template<class K, class V>
    class NW_API HT {
    public:
        using Bucket = TOptional<HTBucket<K, V>>;
        using Iterator = HTIterator<K, V>;
        using ConstIterator = HTIterator<const K, const V>;

        virtual ~HT() {
            if (!_buckets) return;

            for (TUint i = 0; i < _capacity; ++i) {
                if (_buckets[i]) {
                    auto& kv = _buckets[i].unwrap();
                    destroy_at(kv.key);
                    destroy_at(kv.value);
                }
            }

            GAlloc->free(_buckets, sizeof *_buckets * _capacity);
            Memory::clear(this, sizeof *this);
        }

        TUint capacity() const {
            return _capacity;
        }

        TUint size() const {
            return _size;
        }
        
        Iterator begin() {
            return Iterator(_buckets);
        }

        Iterator end() {
            return Iterator(_buckets + _capacity);
        }

        ConstIterator begin() const {
            return ConstIterator(_buckets);
        }

        ConstIterator end() const {
            return ConstIterator(_buckets + _capacity);
        }

        TBool contains(const K& key) const {
            if (!_buckets) return kFalse;

            const auto hv = getBucketId(key);
            return _buckets[hv];
        }

        CWrap<V> get(const K& key) const {
            if (!_buckets) return nullptr;
            
            return lookup(key);
        }

        void insert(const K& key, const V& value) {
            insertKV(key, value);
        }

        template<class...Args>
        void emplace(const K& key, Args&&...args) {
            insertKArgs(key, forward<Args>(args)...);
        }

        void foreach(void(*fn)(HTBucket<K, V>& kv)) {
            if (!_buckets) return;
            
            for (TUint i = 0; i < _capacity; ++i) {
                if (_buckets[i]) {
                    fn(_buckets[i].unwrap());
                }
            }
        }

        void foreach(void(*fn)(const HTBucket<K, V>& kv)) const {
            if (!_buckets) return;
            
            for (TUint i = 0; i < _capacity; ++i) {
                if (_buckets[i]) {
                    fn(_buckets[i].unwrap());
                }
            }
        }

    private:
        TUint getBucketId(const K& key) const {
            auto hv = CObjectHash<K>::get(key) & (_capacity - 1);
            for (TUint i = 0; i < _capacity && _buckets[hv] && (_buckets[hv].unwrap().key != key); ++i) {
                hv = (hv + 1) & (_capacity - 1);
            }
            return hv;
        }

        void insertKV(const K& key, const V& value) {
            if (_size >= _capacity) {
                extendBucketsStorage();
            }

            const auto hv = getBucketId(key);
            loadBucket(key, value, hv);
            ++_size;
        }

        template<class...Args>
        void insertKArgs(const K& key, Args&&...args) {
            if (_size >= _capacity) {
                extendBucketsStorage();
            }

            const auto hv = getBucketId(key);
            loadBucketArgs(key, hv, forward<Args>(args)...);
            ++_size;
        }

        CWrap<V> lookup(const K& key) const {
            if (_capacity == 0) return nullptr;

            const auto hv = getBucketId(key);
            if (_buckets && _buckets[hv] && _buckets[hv].unwrap().key == key) {
                return CWrap<V>(&_buckets[hv].unwrap().value);
            }

            return nullptr;
        }

    private:
        static constexpr TUint kDefInitialCapacity = 8;

        void loadBucket(const K& key, const V& value, TUint idx) {
            construct_at(_buckets[idx], key, value);
        }

        template<class...Args>
        void loadBucketArgs(const K& key, TUint idx, Args&&...args) {
            construct_at(_buckets[idx], key);
            construct_at(_buckets[idx].unwrap().value, forward<Args>(args)...);
        }

        void extendBucketsStorage(const TUint initialCapacity = kDefInitialCapacity) {
            if (_buckets == nullptr) {
                NW_ASSERT(!_capacity, "Invalid HashTable, since storage is NULLPTR but CAPACITY isn't!");

                _size = 0;
                _capacity = initialCapacity;
                _buckets = reinterpret_cast<Bucket*>(GAlloc->allocate(_capacity * sizeof(Bucket)));
            }
            else {
                // expand an existing storage, twice!
                const TUint oldCapacity = _capacity;
                _capacity <<= 1;
                Bucket *newBuckets = reinterpret_cast<Bucket*>(GAlloc->allocate(_capacity * sizeof(Bucket)));
                for (TUint i = 0; i < oldCapacity; ++i) {
                    if (_buckets[i]) {
                        construct_at(newBuckets[i], _buckets[i].unwrap());
                        //construct_at(newBuckets[i].value().key, _buckets[i].value().key);
                        //construct_at(newBuckets[i].value().value, _buckets[i].value().value);
                        destroy_at(_buckets[i].unwrap().key);
                        destroy_at(_buckets[i].unwrap().value);
                    }
                }
                GAlloc->free(_buckets, oldCapacity);
                _buckets = newBuckets;
            }
        }

        Bucket *_buckets = nullptr;
        TUint    _capacity = 0;
        TUint    _size = 0;
    };

}
