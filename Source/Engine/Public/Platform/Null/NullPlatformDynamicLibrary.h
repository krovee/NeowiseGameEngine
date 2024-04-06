#pragma once

#include <Base/DynamicLibrary.h>

namespace Neowise::Platform::Null {

    class NW_API CDynamicLibrary : public Neowise::CDynamicLibrary {
    public:
        CDynamicLibrary(const char* name);
        ~CDynamicLibrary() = default;

        void *getProcAddressImpl(const char* signature);
    };

}
