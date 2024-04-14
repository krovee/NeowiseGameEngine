#include <Base/MemoryUtilities.h>

#include <Platform/PlatformMemory.h>

namespace Neowise {
    void* Memory::copy(void* dst, const void* src, TUint64 size) {
        return Platform::CMemory::copy(dst, const_cast<void*>(src), size);
    }
    
    void* Memory::fill(void* dst, const TInt32 value, TUint64 size) {
        return Platform::CMemory::fill(dst, value, size);
    }

    void* Memory::clear(void* dst, TUint64 size) {
        return Platform::CMemory::fill(dst, 0, size);
    }
}
