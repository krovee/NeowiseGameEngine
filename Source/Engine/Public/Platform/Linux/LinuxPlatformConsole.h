#pragma once

#include <Base/NumericTypes.h>
#include <Base/IOBase.h>

namespace Neowise::Platform::Linux {
    /** 
    * 
    */
    class NW_API CConsole : public CIOBase {
    public:
        static const CUUID ioClass;

        CConsole();

        void setTitleFmt(const char* fmt, ...);
        void setTitle(const char* text);
        void writeFmt(const char* fmt, ...) 	override;
        void write(const char* text) 			override;
        void write(const char* text, TUint len) 	override;
        void writeFmt(const wchar_t* fmt, ...) 	override;
        void write(const wchar_t* text) 		override;
        void write(const wchar_t* text, TUint len)override;

        void* getHandle() const override { return (void*)0xbadb07; }
    };

    extern CConsole GConsole;
}
