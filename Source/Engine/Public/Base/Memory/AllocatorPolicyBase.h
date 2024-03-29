#pragma once

#include <Base/Utilities.h>

namespace Neowise {
	/** 
	* Data class for allocator statistics.
	* Should be useful for simple visualization of memory usage.
	*/
	struct DAllocationInfo {
		uint64 totalAllocated;
		uint64 currentAllocated;

		constexpr uint64 getCached() {
			return totalAllocated - currentAllocated;
		}
	};

	/** 
	* Base class for any allocator policy.
	*/
	class NW_API CAllocatorPolicyBase {
	public:
		CAllocatorPolicyBase() = default;
		CAllocatorPolicyBase(const DAllocationInfo& info);

		virtual void  destroy() {}
		virtual void* allocate(uint64) { return nullptr; }
		virtual void  free(void*, uint64) {}

		DAllocationInfo const& getInfo() const;
		uint64 getTotalAllocated() const;
		uint64 getCurrentAllocated() const;
	protected:
		void onAllocate(uint64 size);
		void onFree(uint64 size);

		DAllocationInfo _info = {};
	};

	template<class T, class...Args>
	inline T* allocateObject(CAllocatorPolicyBase* alloc, Args&&...args) {
		auto p = reinterpret_cast<T*>(alloc->allocate(sizeof(T)));
		construct_at<T>(p, forward<Args>(args)...);
		return p;
	}

}
