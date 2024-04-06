#include <Platform/Windows/WindowsPlatformDynamicLibrary.h>

#include <Platform/Windows/WindowsBase.h>

namespace Neowise::Platform::Windows {
    CDynamicLibrary::CDynamicLibrary(const char *name) : _handle(loadLibrary(name)) 
    {}

    CDynamicLibrary::~CDynamicLibrary() {
        if (_handle) {
            closeLibrary(_handle);
            _handle = {};
        }
    }

    void *CDynamicLibrary::getProcAddressImpl(const char *signature) {
        return loadProcAddress(_handle, signature);
    }
}
