#pragma once

#include <Base/Common.h>

namespace Neowise::Platform::Linux {
    /** 
    * 
    */
    class NW_API CSystemClock {
    public:
        CSystemClock();

        TReal getAbsoluteTimeMs() const;
    };
    
    extern CSystemClock GSystemClock;
}
