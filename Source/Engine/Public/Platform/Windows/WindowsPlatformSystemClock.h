#pragma once

#include <Base/Common.h>

namespace Neowise::Platform::Windows {
    /**
    *
    */
    class NW_API CSystemClock {
    public:
        CSystemClock();

        TReal getAbsoluteTimeMs() const;

    private:
        TInt64 _startTime = {};
        TReal  _frequency = {};
    };

    extern CSystemClock GSystemClock;
}
