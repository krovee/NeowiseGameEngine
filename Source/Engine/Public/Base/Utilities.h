#pragma once

#include <Base/NumericTypes.h>
#include <Base/Templated.h>

#if NW_OS_LINUX
inline void* operator new(unsigned long, void* address) {
    return address;
}
#else
#include <new>
#endif

namespace Neowise {

    /**
     * Literal converter to get bytes from kilobytes.
     */
    inline constexpr TUint operator""_kb(long double kilobytes) {
        return TUint(kilobytes * 1024.0);
    }

    /**
     * Literal converter to get bytes from megabytes.
     */
    inline constexpr TUint operator""_mb(long double megabytes) {
        return TUint(megabytes * 1024.0 * 1024.0);
    }

    /**
     * Literal converter to get bytes from gigabytes.
     */
    inline constexpr long double operator""_gb(long double gigabytes) {
        return 1024.0 * 1024.0 * 1024.0 * gigabytes;
    }

    /**
    * Enumeration to determine build type in compile time, 
    * in a 'more c++ way'.
    */
    enum EBuildType : TUint {
        E_BUILD_TYPE_UNSPECIFIED,

        /**
        * Defined if build type is debug.
        */
        E_BUILD_TYPE_DEBUG,

        /**
        * Defined if build type is release.
        */
        E_BUILD_TYPE_RELEASE,

        /**
        * Defined if build type is shipped.
        */
        E_BUILD_TYPE_SHIP,

#if		defined(_DEBUG)
        /**
        * Current build type.
        */
        E_BUILD_TYPE = E_BUILD_TYPE_DEBUG
#elif	defined(NW_SHIP_BUILD)
        /**
        * Current build type.
        */
        E_BUILD_TYPE = E_BUILD_TYPE_SHIP
#elif	defined(NDEBUG)
        /**
        * Current build type.
        */
        E_BUILD_TYPE = E_BUILD_TYPE_RELEASE
#else 
        /**
        * Current build type.
        */
        E_BUILD_TYPE = E_BUILD_TYPE_UNSPECIFIED
#endif
    };

    constexpr bool kIsDebug     = E_BUILD_TYPE == E_BUILD_TYPE_DEBUG;
    constexpr bool kIsRelease   = E_BUILD_TYPE == E_BUILD_TYPE_RELEASE;
    constexpr bool kIsShip      = E_BUILD_TYPE == E_BUILD_TYPE_SHIP;

    STATIC_ASSERT((kIsDebug != kIsRelease) || (kIsRelease != kIsShip));

    /**
     * Rotates N to the left by ROT bits. 
     * the bits that are shifted past the bit width are shifted back from the right.
     */
    constexpr TUint32 lrotate32bits(TUint32 n, TUint rot) {
        return (n << rot) | (n >> (32 - rot));
    }

    /**
     * Rotates N to the right by ROT bits. 
     * the bits that are shifted past the bit width are shifted back from the left.
     */
    constexpr TUint32 rrotate32bits(TUint32 n, TUint rot) {
        return (n >> rot) | (n << (32 - rot));
    }

    /**
     * Returns the (value) aligned by the (alignment).
     */
    constexpr TUint alignedSize(TUint value, TUint alignment) {
        return (value + alignment - 1) & ~(alignment - 1);
    }

    /**
     * Forwards lvalues as either lvalues or as rvalues, depending on T.
     */
    template<class T>
    constexpr T&& forward(TRemoveRef<T>&& t) {
        return static_cast<T&&>(t);
    }

    /**
     * Forwards lvalues as either lvalues or as rvalues, depending on T.
     */
    template<class T>
    constexpr T&& forward(TRemoveRef<T>& t) {
        return static_cast<T&&>(t);
    }

    /**
     * Used to indicate that an object t may be "moved from", 
     * i.e. allowing the efficient transfer of resources from t to another object.
     */
    template<class T>
    constexpr TRemoveRef<T>&& move(T&& t) {
        return static_cast<TRemoveRef<T>&&>(t);
    }
    
    /**
     * Returns virtual address (pointer) to object.
     */
    template<class T>
    constexpr const void* addressof(const T& obj) {
        return reinterpret_cast<const void*>(&obj);
    }

    /**
     * Returns virtual address (pointer) to object.
     */
    template<class T>
    constexpr void* addressof(T& obj) {
        return reinterpret_cast<void*>(&obj);
    }

    /**
     * Initializes a T object with arguments args...
     */
    template<class T, class...Args>
    constexpr void construct_at(T& obj, Args&&...args) {
        new (addressof(obj)) T(forward<Args>(args)...); // new (addressof(obj)) T(forward<Args>(args)...);
    }

    /**
     * Creates a T object with arguments args... at address p.
     */
    template<class T, class U, class...Args>
    constexpr void construct_at(U* p, Args&&...args) {
        new (p) T(forward<Args>(args)...); // new (p) T(forward<Args>(args)...);
    }

    /**
     * Copies pointer src to dst. This is all construction for pointers.
     */
    template<class T>
    constexpr void construct_at(T*& dst, T* src) {
        dst = src;
    }

    /**
     * Creates N objects of type T in range of (ptr, ptr + size) with arguments args...
     */
    template<class T, class...Args>
    constexpr void construct_range(T* ptr, TUint64 size, Args&&...args) {
        for (TUint64 i = 0; i < size; ++i) {
            new ((ptr + i)) T(forward<Args>(args)...);
        }
    }

    /**
     * Calls destructor for object T.
     */
    template<class T>
    constexpr void destroy_at(T& obj) {
        obj.~T();
    }

    /**
     * Calls destructor for object at address ptr.
     */
    template<class T, class U = T>
    constexpr void destroy_at(U* ptr) {
        if (ptr) {
            ptr->~U();
        }
    }

    /**
     * Calls destructor for every object T in range(ptr, ptr + size).
     */
    template<class T>
    constexpr auto destroy_range(T* ptr, TUint64 size) {
        for (TUint64 i = 0; i < size; ++i) {
            (ptr + i)->~T();
        }
    }

    /**
     * Calls copy constructor for every object T in range(ptr, ptr + size)
     * and copies every object from src to dst (corresponding to index).
     */
    template<class T>
    constexpr auto copy_range(T* dst, const T* src, TUint64 size) {
        for (TUint64 i = 0; i < size; ++i) {
            construct_at(dst[i], src[i]);
        }
    }

    /**
     * Calls move constructor for every object T in range(ptr, ptr + size)
     * and moves every object from src to dst (corresponding to index).
     */
    template<class T>
    constexpr auto move_range(T* dst, const T* src, TUint64 size) {
        for (TUint64 i = 0; i < size; ++i) {
            construct_at(dst[i], move(src[i]));
        }
    }

    /**
     * Basically swaps two objects.
     */
    template<class T>
    constexpr void swap(T& a, T& b) {
        T t(move(a));
        construct_at(a, move(b));
        construct_at(b, move(t));
    }

    /**
     * Basically swaps two static arrays with the same length N.
     */
    template<class T, TUint64 N>
    constexpr void swap(T(&l)[N], T(&r)[N]) {
        if ((T*)l != (T*)r) {
            T* f1 = l;
            T* l1 = f1 + N;
            T* f2 = r;
            for (; f1 != l1; ++f1, ++f2) {
                swap(*f1, *f2);
            }
        }
    }

    /**
     * Basically swaps two arrays with the same size,
     * performing swap operation on every object from 
     * src to dst corresponding to index.
     */
    template<class T>
    constexpr void swap_range(T* dst, T* src, TUint64 size) {
        for (TUint64 i = 0; i < size; ++i) {
            swap(dst[i], src[i]);
        }
    }

    /**
     * NOTE: part of quick sort algorithm. 
     * TODO: comment __quickSortPart()
     */
    template<class T, class PredFn>
    TUint __quickSortPart(T* array, TUint low, TUint high, const T& pivot, PredFn pred) {
        auto i = low, j = low;

        while (i <= high) {
            if (pred(array[i], pivot)) {
                ++i;
            }
            else {
                swap(array[i], array[j]);
                ++i;
                ++j;
            }
        }

        return j - 1;
    }

    /**
     * Pretty fast sorting algorithm, works well.
     */
    template<class T, class PredFn = bool(const T&, const T&)>
    void quickSort(T* array, TUint count, TUint offset = 0, PredFn pred = [](const T& a, const T& b){ return a > b; }) {
        auto low = offset;
        auto high = count - 1;
        if (low < high && high <= TUint(-100)) {
            const auto& pivot = array[high];
            const auto pos = __quickSortPart(array, low, high, pivot, pred);

            quickSort(array, pos - 1, low, pred);
            quickSort(array, high, pos + 1, pred);
        }
    }

    /**
     * Utility function to get a size of statically
     * allocated array.
     */
    template<class T, TUint N>
    constexpr TUint arrayn(T(&)[N]) {
        return N;
    }

    /**
     * Transforms n value to little endian byte representation.
     */
    constexpr TUint32 toLittleEndian32(TUint32 n) {
        if constexpr (NW_LITTLE_ENDIAN) {
            return((n << 24) & 0xFF000000)
                | ((n << 8)  & 0x00FF0000)
                | ((n >> 8)  & 0x0000FF00)
                | ((n >> 24) & 0x000000FF);
        }
        
        return n;
    }

    /**
     * Transforms n value to little endian byte representation.
     */
    constexpr TUint toLittleEndian64(TUint n) {
        if constexpr (NW_LITTLE_ENDIAN) {
            return((n << 56) & 0xFF00000000000000)
                | ((n << 40) & 0x00FF000000000000)
                | ((n << 24) & 0x0000FF0000000000)
                | ((n << 8)  & 0x000000FF00000000)
                | ((n >> 8)  & 0x00000000FF000000)
                | ((n >> 24) & 0x0000000000FF0000)
                | ((n >> 40) & 0x000000000000FF00)
                | ((n >> 56) & 0x00000000000000FF);
        }

        return n;
    }

}
