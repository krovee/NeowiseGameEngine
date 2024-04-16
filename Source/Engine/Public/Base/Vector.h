#pragma once

#include <Base/Templated.h>
#include <Base/Allocators.h>
#include <Base/ArrayView.h>

namespace Neowise {
    extern CFixedHeapAllocatorPolicy* GAlloc;

    /** 
    * 
    */
    template<class T>
    class NW_API TVector {
    public:
        constexpr TVector() = default;

        constexpr TVector(T* first, T* last) {
            construct(first, last - first);
        }

        constexpr TVector(const TInitializerList<T>& list) {
            construct(list.begin(), list.size());
        }

        constexpr TVector(T* data, TUint len) {
            construct(data, len);
        }

        template<TUint N>
        constexpr TVector(T(&arr)[N]) {
            construct(arr, N);
        }

        template<class...Args>
        constexpr TVector(TUint sz, Args&&...args) {
            constructArgs(sz, forward<Args>(args)...);
        }

        constexpr TVector(const TVector& o) {
            construct(o.data(), o.size());
        }
        
        constexpr TVector(TVector&& o) {
            construct(o.data(), o.size());
        }
        
        constexpr TVector& operator=(const TVector& o) {
            construct(o.data(), o.size());
            return *this;
        }

        constexpr TVector& operator=(TVector&& o) {
            construct(o.data(), o.size());
            return *this;
        }
        
        ~TVector() {
            destroy_range(_ptr, _size);
        }

        constexpr TUint size() const {
            return _size;
        }

        constexpr TUint capacity() const {
            return _capacity;
        }

        constexpr const T* data() const {
            return _ptr;
        }

        constexpr T* data() {
            return _ptr;
        }

        constexpr const T* begin() const {
            return _ptr;
        }

        constexpr T* begin() {
            return _ptr;
        }

        constexpr const T* end() const {
            return _ptr + _size;
        }
        
        constexpr T* end() {
            return _ptr + _size;
        }

        constexpr T& front() {
            return _ptr[0];
        }

        constexpr const T& front() const {
            return _ptr[0];
        }

        constexpr T& back() {
            return _ptr[_size];
        }

        constexpr const T& back() const {
            return _ptr[_size];
        }

        T& operator[](TUint i) {
            return _ptr[i];
        }

        const T& operator[](TUint i) const {
            return _ptr[i];
        }

        template<class...Args>
        constexpr T* emplace(Args&&...args) {
            if (_capacity == kInitialCap && !_size) {
                growStorage();
            }
            else if (_size >= _capacity) {
                growCapacity();
                growStorage();
            }

            constructAt(_size++, forward<Args>(args)...);
            return _ptr + _size - 1;
        }

        constexpr void pushBack(const T& obj) {
            emplace(obj);
        }

        constexpr void pushBack(T&& obj) {
            emplace(move(obj));
        }

        constexpr void popBack() {
            NW_ASSERT(_size > 0, "Failed to pop back empty vector.");

            --_size;
        }

        constexpr void clear() {
            Memory::clear(_ptr, sizeof(T) * _size);
            _size = 0;
        }

        constexpr void shrinkToFit() {
            T* p = reinterpret_cast<T*>(GAlloc->allocate(sizeof(T) * _size));
            NW_ASSERT(p, "");
            move_range(p, _ptr, _size);
            GAlloc->free(_ptr, _size);
            _capacity = _size;
            _ptr = p;
        }

        constexpr operator TArrayView<T>() const {
            return TArrayView<T>(_ptr, _size);
        }

    private:
        constexpr static inline TReal	kAdvanceCapFactor = TReal(1.4);
        constexpr static inline TUint	kInitialCap = 8;

        template<class...Args>
        constexpr void constructAt(TUint i, Args&&...args) {
            NW_ASSERT(i <= _capacity, "Failed construction in TVector: out of bounds!");

            construct_at<T>((_ptr + i), forward<Args>(args)...);
        }

        constexpr void construct(const T* data, TUint len) {
            _capacity = alignedSize(len, 4);
            _size = len;
            growStorage();
            T* p = reinterpret_cast<T*>(GAlloc->allocate(sizeof(T) * _capacity));
            NW_ASSERT(p, "");
            move_range(p, data, _size);
            _ptr = p;
        }

        template<class...Args>
        constexpr void constructArgs(TUint len, Args&&...args) {
            _capacity = alignedSize(len, 4);
            _size = len;
            growStorage();
            T* p = reinterpret_cast<T*>(GAlloc->allocate(sizeof(T) * _capacity));
            NW_ASSERT(p, "");
            for (TUint i = 0; i < _size; ++i) {
                constructAt(i, forward<Args>(args)...);
            }
            _ptr = p;
        }

        constexpr void growStorage() {
            T* p = reinterpret_cast<T*>(GAlloc->allocate(sizeof(T) * _capacity));
            NW_ASSERT(p, "");
            if (_ptr) {
                move_range(p, _ptr, _size);
                GAlloc->free(_ptr, _size);
            }
            _ptr = p;
        }

        constexpr void growCapacity() {
            _capacity = alignedSize((TUint)((TReal)(_capacity)*kAdvanceCapFactor), 4);
        }
    private:
        T*		_ptr = nullptr;
        TUint	_capacity = kInitialCap;
        TUint	_size = 0;
    };

    template<class T>
    class NW_API CObjectHash<TVector<T>> {
    public:
        static TUint get(const TVector<T>& vec) {
            auto hs = vec.size() * 0xab0ba + 1;
            for (const auto& v : vec) {
                hs *= hs + CObjectHash<T>::get(v);
            }
            return hs;
        }
    };
}
