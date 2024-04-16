#pragma once

#include <Base/NumericTypes.h>

namespace Neowise {
    /** 
    * Lightweight wrapper around vector, static_vector and every
    * other 'heavy' (to copy or pass to function) container of 
    * contigous data. Captures a pointer and a length of an array.
    */
    template<class T>
    class NW_API TArrayView {
    public:
        constexpr TArrayView() = default;
        constexpr explicit TArrayView(T* p, TUint len) 
            : ptr(p), length(len) 
        {}

        constexpr TBool empty() const {
            return length == 0;
        }

        constexpr TUint size() const {
            return length;
        }

        constexpr TUint raw_size() const {
            return length * sizeof(T);
        }

        constexpr T* data() {
            return ptr;
        }

        constexpr const T* data() const {
            return ptr;
        }

        constexpr T& front() {
            return *ptr;
        }
        
        constexpr const T& front() const {
            return *ptr;
        }
        
        constexpr T& back() {
            return *(ptr + (length - 1));
        }
        
        constexpr const T& back() const {
            return *(ptr + (length - 1));
        }

        constexpr T& operator[](TUint i) {
            return ptr[i];
        }
        
        constexpr const T& operator[](TUint i) const {
            return ptr[i];
        }

        constexpr T* begin() {
            return ptr;
        }

        constexpr const T* begin() const {
            return ptr;
        }
        
        constexpr T* end() {
            return ptr + length;
        }

        constexpr const T* end() const {
            return ptr + length;
        }

    private:
        T* const	ptr = nullptr;
        const TUint	length = 0;
    };
}
