#pragma once

#include <Base/DynamicLibrary.h>

namespace Neowise::Platform::Linux {

    class NW_API CDynamicLibrary : public Neowise::CDynamicLibrary {
    public:
        CDynamicLibrary(const char* name);
        ~CDynamicLibrary();

        void *getProcAddressImpl(const char* signature);
    private:
        void* _handle = nullptr;
    };

}
