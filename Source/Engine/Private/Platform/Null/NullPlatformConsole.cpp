#include <Platform/Null/NullPlatformConsole.h>

namespace Neowise::Platform::Null {
    const CUUID CConsole::ioClass = "NullConsole";
    CConsole GConsole;
    
    
    CConsole::CConsole() : CIOBase(ioClass)
    {
    }
    void CConsole::setTitleFmt(const char*, ...)
    {
    }
    void CConsole::setTitle(const char*)
    {
    }
    void CConsole::writeFmt(const char*, ...)
    {
    }
    void CConsole::write(const char*)
    {
    }
}
