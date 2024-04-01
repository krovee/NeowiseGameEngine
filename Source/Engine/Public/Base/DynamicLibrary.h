#pragma once

#include <Base/StringView.h>
#include <Base/Scope.h>

namespace Neowise {

    class CDynamicLibrary;
    using IDynamicLibrary = Scope<CDynamicLibrary>;

    class NW_API CDynamicLibrary {
    public:
        virtual ~CDynamicLibrary() = default;

        virtual void *getProcAddressImpl(const char* signature) = 0;

        template<class T>
        T getProcAddress(const char* signature) {
            return reinterpret_cast<T>(getProcAddressImpl(signature));
        }

        static IDynamicLibrary load(const CStringView& libName);
    };

}
