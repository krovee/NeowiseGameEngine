#pragma once

#include <Base/Templated.h>
#include <Base/Allocators.h>
#include <Base/ArrayView.h>

namespace Neowise {
    /** 
    * Static vector is a vector but with stack-based allocated memory.
    */
    template<class T, TUint64 N>
    class NW_API TStaticVector {
    private:
        enum {
            kCapacity = N,
            kRawCapacity = sizeof(T) * kCapacity
        };

        using AllocatorType = CFixedStackAllocatorPolicy<kRawCapacity>;

    public:
        constexpr TStaticVector() 
            : _ptr((T*)(TUint8*)_zbuffer)
        {}
        
        constexpr TStaticVector(const TStaticVector& o) 
            : _ptr(o._ptr), _size(o._size)
        {
            Memory::copy(_zbuffer, o._zbuffer, _size * sizeof(T));
            _ptr = (T*)_zbuffer;
        }
        
        constexpr TStaticVector(TStaticVector&& o)
            : _ptr(o._ptr), _size(o._size)
        {
            swap(_zbuffer, o._zbuffer);
            _ptr = (T*)_zbuffer;
            o._ptr = nullptr;
            o._size = 0;
        }
        
        constexpr TStaticVector& operator=(const TStaticVector& o)	= default;
        
        constexpr TStaticVector& operator=(TStaticVector&& o)		= default;
        
        constexpr ~TStaticVector() {
            destroy_range(_ptr, _size);
        }

        constexpr TStaticVector(TInitializerList<T> ilist) : TStaticVector() {
            NW_ASSERT(ilist.size() <= _capacity, "TStaticVector(initializer_list) an attempted to construct with ilist which exceeds vector's bounds!");
            copy_range(_ptr, ilist.begin(), ilist.size());
            _size = ilist.size();
        }

        template<TEnableIf<!isLValReference<T>, int> = 0>
        constexpr TStaticVector(const T* first, const T* last) : TStaticVector() {
            _size = last - first;
            NW_ASSERT(_size <= _capacity, "TStaticVector(first, last) an attempted to construct with list which exceeds vector's bounds!");
            copy_range(_ptr, first, _size);
        }

        template<class...Args>
        constexpr TStaticVector(TUint64 count, Args&&...args) : TStaticVector() {
            NW_ASSERT(count <= _capacity, "TStaticVector(count, ...) an attempted to construct with list which exceeds vector's bounds!");
            construct_range(_ptr, count, forward<Args>(args)...);
            _size = count;
        }

        constexpr operator TArrayView<T>() const {
            return TArrayView<T>(_ptr, _size);
        }

        constexpr auto data() {
            return _ptr;  
        }

        constexpr auto data() const {
            return _ptr;
        }

        constexpr auto& operator[](TUint i) {
            return _ptr[i];
        }
        
        constexpr auto operator[](TUint i) const {
            return _ptr[i];
        }

        constexpr TUint64 size() const {
            return _size;
        }

        constexpr TBool empty() const {
            return _size == 0;
        }

        constexpr TUint64 capacity() const {
            return _capacity;
        }

        constexpr T* begin() {
            return _ptr;
        }

        constexpr const T* begin() const {
            return _ptr;
        }

        constexpr T* end() {
            return _ptr + _size;
        }

        constexpr const T* end() const {
            return _ptr + _size;
        }

        constexpr T& front() {
            return *_ptr;
        }

        constexpr const T& front() const {
            return *_ptr;
        }
        
        constexpr T& back() {
            return *(_ptr + _size - 1);
        }

        constexpr const T& back() const {
            return *(_ptr + _size - 1);
        }

        constexpr void pushBack(const T& t) {
            NW_ASSERT(_size < _capacity, "TStaticVector::pushBack() exceeds bounds!");
            construct_at(_ptr[_size++], t);
        }

        constexpr void popBack() {
            NW_ASSERT(size() > 0, "TStaticVector::popBack() an attempted to call on an empty vector!");
            destroy_at(_ptr[--_size]);
        }

        template<class...Args>
        constexpr T& emplace(Args&&...args) {
            NW_ASSERT(_size <= _capacity, "TStaticVector::emplace() exceeds bounds!");
            construct_at(_ptr[_size++], forward<Args>(args)...);
            return back();
        }

        constexpr void resize(TUint sz) {
            NW_ASSERT(sz <= _capacity, "TStaticVector::resize(n) an attempted to exceed capacity!");
            _size = sz;
            construct_range(_ptr, _size);
        }

        constexpr void clear(const TBool set0 = kFalse) {
            destroy_range(_ptr, _size);
            _size = 0;
            
            if (set0) {
                Memory::clear(_ptr, sizeof(T) * _capacity);
            }
        }

    private: 
        template<class U, TUint64 M>
        friend constexpr void swap(TStaticVector<U, M>& l, TStaticVector<U, M>& r);
    private:
        T*								_ptr = {};
        TUint64							_size = {};
        TUint8							_zbuffer[alignedSize(kRawCapacity, 8)] = {};
        static constexpr const TUint64	_capacity = N;
    };

    template<class T, TUint64 N>
    constexpr void swap(TStaticVector<T, N>& l, TStaticVector<T, N>& r) {
        swap_range(l._zbuffer, r._zbuffer, N);
        swap(l._ptr, r._ptr);
        swap(l._size, r._size);
    }

    template<class T, TUint N>
    class NW_API CObjectHash<TStaticVector<T, N>> {
    public:
        static TUint get(const TStaticVector<T, N>& vec) {
            TUint hs = vec.size() * 0xab0ba + 1;
            for (const auto& v : vec) {
                hs *= hs + CObjectHash<T>::get(v);
            }
            return hs;
        }
    };

}
