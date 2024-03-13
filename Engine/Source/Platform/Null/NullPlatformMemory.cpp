#include <Platform/Null/NullPlatformMemory.h>

namespace Neowise::Platform::Null {
	void* CMemory::allocate(uint64 size) {
		return nullptr;
	}
	void CMemory::free(void* p) {
	}
	void* CMemory::copy(void* dst, void* src, uint64 size) {
		return dst;
	}
	void* CMemory::fill(void* dst, int32 value, uint64 size) {
		return dst;
	}
	uint64 CMemory::counts(const char* s) {
		return 0;
	}
	uint64 CMemory::counts(const wchar_t* ws) {
		return 0;
	}
	bool CMemory::compare(const void *p1, const void *p2, uint64 len) {
		return false;
	}
}
