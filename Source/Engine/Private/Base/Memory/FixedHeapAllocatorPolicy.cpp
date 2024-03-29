#include <Base/Memory/FixedHeapAllocatorPolicy.h>
#include <Platform/PlatformMemory.h>
#include <Base/MemoryUtilities.h>
#include <Base/Templated.h>

namespace Neowise {

	CFixedHeapAllocatorPolicy::CFixedHeapAllocatorPolicy(CFixedHeapAllocatorPolicy&& o) {
		swap(_data, o._data);
		swap(_capacity, o._capacity);
		swap(_info, o._info);
	}

	CFixedHeapAllocatorPolicy& CFixedHeapAllocatorPolicy::operator=(CFixedHeapAllocatorPolicy&& r) {
		swap(_data, r._data);
		swap(_capacity, r._capacity);
		swap(_info, r._info);
		return *this;
	}
	
	CFixedHeapAllocatorPolicy::CFixedHeapAllocatorPolicy(uint64 capacity)
		: CAllocatorPolicyBase(), _data(Platform::CMemory::allocate(capacity)), _capacity(capacity)
	{}

	void CFixedHeapAllocatorPolicy::destroy() {
		if (_data) {
			Platform::CMemory::free(_data);
			_data = nullptr;
			_info.currentAllocated = 0;
			_capacity = 0;
		}
	}

	void* CFixedHeapAllocatorPolicy::allocate(uint64 size) {
		if (_info.currentAllocated < _capacity && size) {
			const uint64 i = _info.currentAllocated;
			onAllocate(size);
			return reinterpret_cast<void*>((uint8*)(_data) + i);
		}
		return nullptr;
	}

	void CFixedHeapAllocatorPolicy::free(void*, uint64 size) {
		if (size <= _capacity) {
			onFree(size);
			if (int64(_info.currentAllocated) < 0) {
				_info.currentAllocated = 0;
			}
		}
	}
}
