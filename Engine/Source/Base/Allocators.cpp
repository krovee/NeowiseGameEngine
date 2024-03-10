#include <Base/Allocators.h>

#include <Platform/PlatformMemory.h>

namespace Neowise {
	static CFixedHeapAllocatorPolicy* sInitializeGlobalHeapAllocator() {

		auto p = Platform::CMemory::allocate(sizeof(CFixedHeapAllocatorPolicy));
		auto obj = reinterpret_cast<CFixedHeapAllocatorPolicy*>(p);
		construct_at(*obj, kDefaultGlobalHeapSize);

		return obj;
	}

	CFixedHeapAllocatorPolicy* GAlloc = sInitializeGlobalHeapAllocator();
}
