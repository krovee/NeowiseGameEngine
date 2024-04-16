#pragma once

#include <Base/NumericTypes.h>
#include <Base/Allocators.h>
#include <Base/Templated.h>
#include <Base/Optional.h>
#include <Base/Wrap.h>
#include <Base/Hash.h>

namespace Neowise {

    extern CFixedHeapAllocatorPolicy *GAlloc;

    template<class K>
    struct HSBucket {
        K key;
    };

    template<class K>
    class HSIterator {
    public:
        using Bucket = TOptional<HSBucket<K>>;

        explicit HSIterator(Bucket* p, Bucket* e) : ptr(p), end(e) {}
        virtual ~HSIterator() {}

        K& key() {
            return ptr->value().key;
        }
        
        const K& key() const {
            return ptr->value().key;
        }

        K* operator->() const {
            return ptr->value().key;
        }

        K& operator*() {
            return ptr->unwrap().key;
        }

        HSIterator operator++(int) {
            HSIterator tmp = *this;
            do {
                ++ptr;
            }
            while (!*ptr && ptr != end);
            return tmp;
        }

        HSIterator& operator++() {
            do {
                ++ptr;
            }
            while (!*ptr && ptr != end);
            return *this;
        }

        operator TBool() const {
            return ptr;
        }

        TBool operator==(const HSIterator& it) const {
            return ptr == it.ptr;
        }

        TBool operator!=(const HSIterator& it) const {
            return ptr != it.ptr;
        }

    private:
        Bucket* ptr = nullptr;
        Bucket* end = 0;
    };

    template<class K>
    class NW_API HS {
    public:
        using Bucket = TOptional<HSBucket<K>>;
        using Iterator = HSIterator<K>;
        using ConstIterator = HSIterator<const K>;

        HS() = default;
        HS(TInitializerList<K> ilist) {
            for (auto& key : ilist) {
                insertKey(key);
            }
        }

        void insert(const K& key) {
            insertKey(key);
        }

        Iterator begin() {
            return Iterator(_buckets, _buckets + _capacity);
        }

        Iterator end() {
            return Iterator(_buckets + _capacity, _buckets + _capacity);
        }
        
        ConstIterator begin() const {
            return ConstIterator(_buckets, _buckets + _capacity);
        }

        ConstIterator end() const {
            return ConstIterator(_buckets + _capacity, _buckets + _capacity);
        }
        

    private:
        static constexpr TUint kDefInitialCapacity = 8;

        void loadBucket(const K& key, TUint idx) {
            construct_at(_buckets[idx], key);
        }

        void extendBucketsStorage(const TUint initialCapacity = kDefInitialCapacity) {
            if (!_buckets) {
                NW_ASSERT(!_capacity, "Invalid HS, since storage is NULLPTR but not CAPACITY!");

                _size = 0;
                _capacity = initialCapacity;
                _buckets = reinterpret_cast<Bucket*>(GAlloc->allocate((1 + _capacity) * sizeof(Bucket)));
            }
            else {
                // expand an existing storage
                const TUint oldCapacity = _capacity;
                _capacity <<= 1;
                Bucket* newBuckets = reinterpret_cast<Bucket*>(GAlloc->allocate((1 + _capacity) * sizeof(Bucket)));
                for (TUint i = 0; i < oldCapacity; ++i) {
                    if (_buckets[i]) {
                        construct_at(newBuckets[i], _buckets[i].unwrap());
                        destroy_at(_buckets[i].unwrap().key);
                    }
                }

                GAlloc->free(_buckets, oldCapacity);
                _buckets = newBuckets;
            }
        }

        TUint getBucketId(const K& key) const {
            auto hv = CObjectHash<K>::get(key) & (_capacity - 1);
            for (TUint i = 0; i < _capacity && _buckets[hv] && (_buckets[hv].unwrap().key != key); ++i) {
                hv = (hv + 1) & (_capacity - 1);
            }
            return hv;
        }

        void insertKey(const K& key) {
            if (_size >= _capacity) {
                extendBucketsStorage();
            }

            const auto hv = getBucketId(key);
            loadBucket(key, hv);
            ++_size;
        }

    private:
        Bucket*     _buckets = nullptr;
        TUint       _capacity = 0;
        TUint       _size = 0;
    };

}
