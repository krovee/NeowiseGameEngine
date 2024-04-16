#include <Platform/Windows/WindowsPlatformDynamicLibrary.h>

#include <Base/Hashtable.h>
#include <Platform/Windows/WindowsBase.h>

namespace Neowise::Platform::Windows {
    static HT<CStringView, void*> sCachedLibraries = {};

    CDynamicLibrary::CDynamicLibrary(const char *name)
    {
        const auto lib = sCachedLibraries.get(name);
        if (lib) {
            _handle = lib.unwrap();
        }
        else {
            _handle = loadLibrary(name);
            sCachedLibraries.insert(name, _handle);
        }
    }

    CDynamicLibrary::~CDynamicLibrary() {
        // if (_handle) {
        //     closeLibrary(_handle);
        //     _handle = {};
        // }
    }

    void *CDynamicLibrary::getProcAddressImpl(const char *signature) {
        return loadProcAddress(_handle, signature);
    }
}
