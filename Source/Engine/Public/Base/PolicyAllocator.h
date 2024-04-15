#pragma once

#include <Base/Memory/AllocatorPolicyBase.h>
#include <Base/MemoryUtilities.h>
#include <Base/Utilities.h>

namespace Neowise {

    /** 
    * Wrapper class for any allocator policy.
    * [DEPRECATED]: Rite now not used, will be removed soon.
    */
    template<class Policy> 
    class NW_API CPolicyAllocator {
    public:
        inline CPolicyAllocator() = default;

        template<class...Args>
        inline CPolicyAllocator(Args&&...args) 
            : _pol{ forward<Args>(args)... }
        {}

        inline ~CPolicyAllocator() {
            _pol.destroy();
        }

        inline void* allocate(TUint64 size) {
            return _pol.allocate(size);
        }

        inline void free(void* p, TUint64 size) {
            if (!p || size == 0) 
                return;

            _pol.free(p, size);
        }

        inline void* reallocate(void* p, TUint64 oldSize, TUint64 newSize) {
            if (!p)
                return allocate(newSize);

            void* p2 = allocate(newSize);
            if (!p2)
                return nullptr;

            Memory::copy(p2, p, newSize);
            free(p, oldSize);

            return p2;
        }

        inline DAllocationInfo const& getInfo() const {
            return _pol.getInfo();
        }

        inline TUint64 getTotalAllocated() const {
            return _pol.getTotalAllocated();
        }

        inline TUint64 getCurrentAllocated() const {
            return _pol.getCurrentAllocated();
        }

    private:
        Policy _pol = {};
    };
}
