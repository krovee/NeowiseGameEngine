#pragma once

#include <Base/DynamicLibrary.h>

namespace Neowise::Platform::Windows {

    class NW_API CDynamicLibrary : public Neowise::CDynamicLibrary {
    public:
        CDynamicLibrary(const char* name);
        ~CDynamicLibrary() override;

        void *getProcAddressImpl(const char* signature);
    private:
        void* _handle = nullptr;
    };

}
