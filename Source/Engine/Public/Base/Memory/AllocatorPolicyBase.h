#pragma once

#include <Base/Utilities.h>

namespace Neowise {
    /** 
    * Data class for allocator statistics.
    * Should be useful for simple visualization of memory usage.
    */
    struct DAllocationInfo {
        TUint64 totalAllocated;
        TUint64 currentAllocated;

        constexpr TUint64 getCached() {
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
        virtual void* allocate(TUint64) { return nullptr; }
        virtual void  free(void*, TUint64) {}

        template<class T, class...Args>
        T* create(Args&&...args) {
            T* p = reinterpret_cast<T*>(allocate(sizeof(T)));
            construct_at<T>(p, forward<Args>(args)...);
            return p;
        }

        DAllocationInfo const& getInfo() const;
        TUint64 getTotalAllocated() const;
        TUint64 getCurrentAllocated() const;
    protected:
        void onAllocate(TUint64 size);
        void onFree(TUint64 size);

        DAllocationInfo _info = {};
    };

    template<class T, class...Args>
    inline T* allocateObject(CAllocatorPolicyBase* alloc, Args&&...args) {
        auto p = reinterpret_cast<T*>(alloc->allocate(sizeof(T)));
        construct_at<T>(p, forward<Args>(args)...);
        return p;
    }

}
