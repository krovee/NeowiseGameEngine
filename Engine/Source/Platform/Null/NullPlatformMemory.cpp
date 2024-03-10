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
		const char* p = s;
		while (*p++);
		return uint64(p - s);
	}
	uint64 CMemory::counts(const wchar_t* ws) {
		const auto* p = ws;
		while (*p++);
		return uint64(p - ws);
	}
}
