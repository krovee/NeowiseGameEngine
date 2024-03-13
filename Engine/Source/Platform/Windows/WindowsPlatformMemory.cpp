#include <Platform/Windows/WindowsPlatformMemory.h>

#if NW_OS(WIN32)

namespace Neowise::Platform::Windows {
	
	void* CMemory::allocate(uint64 size) {
		return heapAlloc(getProcessHeap(), size, E_HEAP_ALLOC_FLAGS_ZERO_INITIALIZED);
	}

	void CMemory::free(void* p) {
		heapFree(getProcessHeap(), p);
	}

	void* CMemory::copy(void* dst, void* src, uint64 size) {
		return copyMemory(dst, src, size);
	}

	void* CMemory::fill(void* dst, int32 value, uint64 size) {
		return fillMemory(dst, value, size);
	}

	uint64 CMemory::counts(const char* s) {
		return lstrlenA(s);
	}
	
	uint64 CMemory::counts(const wchar_t* s) {
		return lstrlenW(s);
	}

	bool CMemory::compare(const void* p1, const void* p2, uint64 len) {
		return compareMemory(p1, p2, len);
	}
	
}

#endif
