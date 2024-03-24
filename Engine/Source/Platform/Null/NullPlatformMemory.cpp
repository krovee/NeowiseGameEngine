#include <Platform/Null/NullPlatformMemory.h>

namespace Neowise::Platform::Null {
	void* CMemory::allocate(uint64) {
		return nullptr;
	}
	void CMemory::free(void*) {
	}
	void* CMemory::copy(void* dst, void*, uint64) {
		return dst;
	}
	void* CMemory::fill(void* dst, int32, uint64) {
		return dst;
	}
	uint64 CMemory::counts(const char*) {
		return 0;
	}
	uint64 CMemory::counts(const wchar_t*) {
		return 0;
	}
	bool CMemory::compare(const void *, const void *, uint64) {
		return false;
	}
}
