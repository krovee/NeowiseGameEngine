#pragma once

#include <Base/NumericTypes.h>
#include <Base/UUID.h>

namespace Neowise {
    /** 
    * Base class for any Input-Output class.
    */
    class NW_API CIOBase {
    public:
        virtual void* getHandle() const { return nullptr; }

        virtual void write(const char*) {}
        virtual void write(const char*, TUint64) {}
        virtual void writeFmt(const char*, ...) {}
        virtual void write(const wchar_t*) {}
        virtual void write(const wchar_t*, TUint64) {}
        virtual void writeFmt(const wchar_t*, ...) {}

    protected:
        inline CIOBase(CUUID ioid) : _ioid(ioid) {}

        CUUID _ioid = CUUID::INVALID;
    };
}
