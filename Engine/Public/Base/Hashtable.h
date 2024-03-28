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
        using Bucket = COptional<HTBucket<K, V>>;

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

        operator bool() const {
            return ptr;
        }

        bool operator==(const HTIterator& it) const {
            return ptr == it.ptr;
        }

        bool operator!=(const HTIterator& it) const {
            return ptr != it.ptr;
        }

    private:
        Bucket* ptr = nullptr;
    };

    template<class K, class V>
    class NW_API HT {
    public:
        using Bucket = COptional<HTBucket<K, V>>;
        using Iterator = HTIterator<K, V>;
        using ConstIterator = HTIterator<const K, const V>;

        virtual ~HT() {
            
        }

        uint capacity() const {
            return _capacity;
        }

        uint size() const {
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

        bool contains(const K& key) const {
            const auto hv = getBucketId(key);
            return _buckets[hv];
        }

        void insert(const K& key, const V& value) {
            insertKV(key, value);
        }

        CWrap<V> get(const K& key) const {
            return lookup(key);
        }

    private:
        uint getBucketId(const K& key) const {
            auto hv = CObjectHash<K>::get(key) & (_capacity - 1);
            for (uint i = 0; i < _capacity && _buckets[hv] && (_buckets[hv].unwrap().key != key); ++i) {
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

        CWrap<V> lookup(const K& key) const {
            if (_capacity == 0) return nullptr;

            const auto hv = getBucketId(key);
            if (_buckets && _buckets[hv] && _buckets[hv].unwrap().key == key) {
                return CWrap<V>(&_buckets[hv].unwrap().value);
            }

            return nullptr;
        }

    private:
        static constexpr uint kDefInitialCapacity = 8;

        void loadBucket(const K& key, const V& value, uint idx) {
            construct_at(_buckets[idx], key, value);
        }

        void extendBucketsStorage(const uint initialCapacity = kDefInitialCapacity) {
            if (_buckets == nullptr) {
                NW_ASSERT(!_capacity, "Invalid HashTable, since storage is NULLPTR but CAPACITY isn't!");

                _size = 0;
                _capacity = initialCapacity;
                _buckets = reinterpret_cast<Bucket*>(GAlloc->allocate(_capacity * sizeof(Bucket)));
            }
            else {
                // expand an existing storage, twice!
                const uint oldCapacity = _capacity;
                _capacity <<= 1;
                Bucket *newBuckets = reinterpret_cast<Bucket*>(GAlloc->allocate(_capacity * sizeof(Bucket)));
                for (uint i = 0; i < oldCapacity; ++i) {
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
        uint    _capacity = 0;
        uint    _size = 0;
    };

    template<class K>
    class NW_API HS {
    public:
        using Bucket = HTBucket<K, void>;

    private:

    };

}
