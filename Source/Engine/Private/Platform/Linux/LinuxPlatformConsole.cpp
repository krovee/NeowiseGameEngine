#include <Platform/Linux/LinuxPlatformConsole.h>

#include <Engine/EngineGlobals.h>
#include <Base/StringUtils.h>

#include <stdarg.h>
#include <Platform/Linux/LinuxBase.h>

namespace Neowise::Platform::Linux {
    const CUUID CConsole::ioClass = "LinuxConsole";
    CConsole GConsole;

    CConsole::CConsole() : CIOBase(ioClass) 
    {}
    
    void CConsole::setTitleFmt(const char*, ...) {
        NW_OPT_ASSERT(kFalse, "[LINUXNOTIMPLEMENTED]: Failed to set title on linux terminal!");
    }

    void CConsole::setTitle(const char*) {
        NW_OPT_ASSERT(kFalse, "[LINUXNOTIMPLEMENTED]: Failed to set title on linux terminal!");
    }

    void CConsole::writeFmt(const wchar_t *, ...) {
        NW_OPT_ASSERT(kFalse, "[LINUXNOTIMPLEMENTED]: Failed to write wide-character text on linux terminal!");
    }

    void CConsole::write(const wchar_t *) {
        NW_OPT_ASSERT(kFalse, "[LINUXNOTIMPLEMENTED]: Failed to write wide-character text on linux terminal!");
    }

    void CConsole::writeFmt(const char *fmt, ...) {
        NW_NONSHIP_CODE(
        va_list ap;
        va_start(ap, fmt);
        char buf[256]{};
        CStringUtils::format(buf, 256, fmt, ap);
        _ConsoleWrite(buf);
        va_end(ap);
        )
    }

    void CConsole::write(const char *text) {
        NW_NONSHIP_CODE(
        _ConsoleWrite(text);
        )
    }

    void CConsole::write(const char *text, uint) {
        NW_NONSHIP_CODE(
        _ConsoleWrite(text);
        )
    }

    void CConsole::write(const wchar_t *, uint) {
        NW_OPT_ASSERT(kFalse, "[LINUXNOTIMPLEMENTED]: Failed to write wide-character text on linux terminal!");
    }

}
