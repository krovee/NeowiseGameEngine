#pragma once

#include <Base/Utilities.h>
#include <Base/Memory/AllocatorPolicyBase.h>

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

        CFixedHeapAllocatorPolicy(TUint64 capacity);

        void destroy() override;

        void* allocate(TUint64 size) override;

        void free(void* p, TUint64 size) override;
    private:
        void*	_data = nullptr;
        TUint64	_capacity = 0;
    };
}
