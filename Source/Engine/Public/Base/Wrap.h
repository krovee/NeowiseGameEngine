#pragma once

#include <Base/NumericTypes.h>
#include <Base/Templated.h>

namespace Neowise {

    /**
    * Wrap works as a wrapper around pointer to perform more safely and polish 
    * checks around it. Wrap doesn't do *anything* with data at pointers. 
    */
    template<class T>
    class NW_API CWrap {
    public:
        constexpr CWrap() = default;
        ~CWrap() = default;

        explicit CWrap(T* p) : _ptr(p) {}
        CWrap(nullptr_t) : _ptr() {}

        constexpr TBool isValid() const {
            return _ptr != nullptr;
        }

        constexpr operator TBool() const {
            return _ptr != nullptr;
        }

        constexpr T& unwrap() {
            return *_ptr;
        }

        constexpr const T& unwrap() const {
            return *_ptr;
        }

        constexpr operator T&() {
            return *_ptr;
        }

        constexpr operator const T&() const {
            return *_ptr;
        }

    private:
        T* _ptr = nullptr;
    };
}
