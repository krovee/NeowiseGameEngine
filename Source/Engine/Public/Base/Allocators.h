#pragma once

#include <Base/PolicyAllocator.h>

#include <Base/Memory/FixedStackAllocatorPolicy.h>
#include <Base/Memory/FixedHeapAllocatorPolicy.h>

/* 
* [04.02.2024][krovee]
* THIS FILE IS NOT USED AT ALL RITE NOW AND SHOULD BE REMOVED SOON.
*/

namespace Neowise {
    
    /** 
    * Fixed size static (stack) allocator, based on CFixedStackAllocatorPolicy<N>
    * allocator policy. Used specifically for small fast allocations where needed(required).
    */
    template<TUint64 N>
    using CFixedStackAllocator = CPolicyAllocator<CFixedStackAllocatorPolicy<N>>;

    /** 
    * Fixed size static (heap) allocator, based on CFixedHeapAllocatorPolicy 
    * allocator policy. Used for big allocations, but forced to reuse space.
    */
    using CFixedHeapAllocator = CPolicyAllocator<CFixedHeapAllocatorPolicy>;

    constexpr TUint64 kDefaultGlobalHeapSize = 128.0_mb;

}
