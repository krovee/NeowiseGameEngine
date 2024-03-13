#include <Platform/Linux/LinuxPlatformMemory.h>

#if NW_OS(LINUX)

#include <Platform/Linux/LinuxBase.h>

namespace Neowise::Platform::Linux {
    void* CMemory::allocate(uint64 size) {
        uint alignment = 1;
        if (size >= 8) {
            alignment = 2;
        }
        if (size >= 16) {
            alignment = 4;
        }
        if (size >= 64) {
            alignment = 8;
        }
        if (size >= 128) {
            alignment = 16;
        }
        return _AlignedAlloc(size, alignment);
    }

    void CMemory::free(void *p) {
        _AlignedFree(p);
    }

    void* CMemory::copy(void *dst, const void *src, uint64 size) {
        return _MemoryCopy(dst, src, size);
    }
    
    void* CMemory::fill(void *dst, int32 value, uint64 size) {
        return _MemorySet(dst, value, size);
    }

    uint64 CMemory::counts(const char *s) {
        return _MemoryCount(s);
    }

    uint64 CMemory::counts(const wchar_t *ws) {
        return _MemoryCount(ws);
    }

    bool CMemory::compare(const void* p1, const void* p2, uint64 len) {
        return _MemoryCompare(p1, p2, len);
    }
    
}

#endif
