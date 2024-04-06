#include <Platform/Linux/LinuxPlatformDynamicLibrary.h>

#include <Platform/Linux/LinuxBase.h>

namespace Neowise::Platform::Linux {
    CDynamicLibrary::CDynamicLibrary(const char* name) : _handle(_LoadLibrary(name)) {}

    CDynamicLibrary::~CDynamicLibrary() {
        _FreeLibrary(_handle);
        _handle = nullptr;
    }

    void* CDynamicLibrary::getProcAddressImpl(const char* signature) {
        return _GetProcAddress(_handle, signature);
    }

}
