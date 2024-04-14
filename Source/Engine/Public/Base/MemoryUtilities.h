#pragma once

#include <Base/NumericTypes.h>

namespace Neowise {
    /** 
    * Common memory functions to operate over memory.
    */
    struct NW_API Memory {
        /**
        * Copy bytes from 'src' to 'dst' for 'size'.
        */
        static void* copy(void* dst, const void* src, TUint64 size);
        
        /**
        * Fill 'dst' buffer with 'value' for 'size'.
        */
        static void* fill(void* dst, const TInt32 value, TUint64 size);
        
        /** 
        * Fill 'dst' buffer with zeros for 'size'.
        */
        static void* clear(void* dst, TUint64 size);
    };
}
