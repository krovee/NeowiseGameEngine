#pragma once

#include "WindowsBase.h"
#include <Base/NumericTypes.h>

namespace Neowise::Platform::Windows {
    /** 
    * 
    */
    class NW_API CMemory {
    public:
        static void* allocate(TUint64 size);
        static void  free(void* p);
        static void* copy(void* dst, void* src, TUint64 size);
        static void* fill(void* dst, TInt32 value, TUint64 size);
        static TUint64 counts(const char* s);
        static TUint64 counts(const wchar_t* ws);
        static bool compare(const void* p1, const void* p2, TUint64 len);
    };
}
