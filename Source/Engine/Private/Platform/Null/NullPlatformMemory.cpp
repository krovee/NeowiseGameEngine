#include <Platform/Null/NullPlatformMemory.h>

namespace Neowise::Platform::Null {
    void* CMemory::allocate(TUint64) {
        return nullptr;
    }
    void CMemory::free(void*) {
    }
    void* CMemory::copy(void* dst, void*, TUint64) {
        return dst;
    }
    void* CMemory::fill(void* dst, TInt32, TUint64) {
        return dst;
    }
    TUint64 CMemory::counts(const char*) {
        return 0;
    }
    TUint64 CMemory::counts(const wchar_t*) {
        return 0;
    }
    bool CMemory::compare(const void *, const void *, TUint64) {
        return false;
    }
}
