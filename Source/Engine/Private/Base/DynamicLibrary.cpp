#include <Base/DynamicLibrary.h>

#include <Platform/PlatformDynamicLibrary.h>

namespace Neowise {
    
    IDynamicLibrary CDynamicLibrary::load(const CStringView& libName) {
        return makeScope<Platform::CDynamicLibrary>(libName.cstr()).cast<CDynamicLibrary>();
    }

}
