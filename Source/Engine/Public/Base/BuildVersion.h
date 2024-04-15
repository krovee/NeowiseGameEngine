#pragma once

#include <Base/NumericTypes.h>

namespace Neowise {
    /** 
    * Compile-time date-based version class.
    */
    class NW_API CBuildVersion {
    public:
        CBuildVersion();

        operator TUint() const;
        TUint64 get() const;
    private:
        TUint64 _number = {};
    };

    /**
    * Engine dynamic library build version, encoded 
    * with date and time of compilation start.
    */
    extern CBuildVersion buildVersion;
}
