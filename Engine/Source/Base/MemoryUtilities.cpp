#include <Base/MemoryUtilities.h>

#include <Platform/PlatformMemory.h>

namespace Neowise {
	void* Memory::copy(void* dst, const void* src, uint64 size) {
		return Platform::CMemory::copy(dst, const_cast<void*>(src), size);
	}
	
	void* Memory::fill(void* dst, const int32 value, uint64 size) {
		return Platform::CMemory::fill(dst, value, size);
	}

	void* Memory::clear(void* dst, uint64 size) {
		return Platform::CMemory::fill(dst, 0, size);
	}
}
