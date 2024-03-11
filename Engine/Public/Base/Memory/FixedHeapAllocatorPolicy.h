#pragma once

#include <Base/Utilities.h>
#include "AllocatorPolicyBase.h"

namespace Neowise {
	/** 
	* Fixed-size heap allocator policy for e.g. frame data.
	*/
	class NW_API CFixedHeapAllocatorPolicy : public CAllocatorPolicyBase {
	public:

		inline CFixedHeapAllocatorPolicy() = default;
		virtual  ~CFixedHeapAllocatorPolicy() {
			destroy();
		}

		CFixedHeapAllocatorPolicy(const CFixedHeapAllocatorPolicy&) = delete;
		CFixedHeapAllocatorPolicy(CFixedHeapAllocatorPolicy&&);
		CFixedHeapAllocatorPolicy& operator=(const CFixedHeapAllocatorPolicy&) = delete;
		CFixedHeapAllocatorPolicy& operator=(CFixedHeapAllocatorPolicy&&);

		CFixedHeapAllocatorPolicy(uint64 capacity);

		void destroy() override;

		void* allocate(uint64 size) override;

		void free(void* p, uint64 size) override;
	private:
		void*	_data = nullptr;
		uint64	_capacity = 0;
	};
}
