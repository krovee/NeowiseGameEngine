#include <Platform/Windows/WindowsPlatformConsole.h>

#if NW_OS(WIN32)

#include <stdarg.h>
#include <stdio.h>

namespace Neowise::Platform::Windows {
	const CUUID CConsole::ioClass = "WindowsConsole";
	CConsole GConsole;
    
#if NW_OS(WIN32)
#	define _vsprintf vsprintf_s
#	define _vswprintf vswprintf_s
#else 
#	define _vsprintf vsprintf
#	define _vswprintf 
#endif

	CConsole::CConsole() : CIOBase(ioClass) {
		NW_NONSHIP_CODE(
		allocConsole();
		_hConsoleOutput = getStdOutHandle();
		_hConsoleWindow = getConsoleWindow();
		)
	}

	CConsole::~CConsole() {
		NW_NONSHIP_CODE(
		freeConsole();
		)
	}

	void CConsole::setTitle(const char* text) {
		NW_NONSHIP_CODE(
		setWindowTextA(_hConsoleWindow, text);
		)
	}

	void CConsole::setTitleFmt(const char* fmt, ...) {
		NW_NONSHIP_CODE(
		va_list ap;
		va_start(ap, fmt);
		char buf[256]{};
		_vsprintf(buf, fmt, ap);
		setWindowTextA(_hConsoleWindow, buf);
		va_end(ap);
		)
	}

	void CConsole::writeFmt(const wchar_t* fmt, ...) {
		NW_NONSHIP_CODE(
		va_list ap;
		va_start(ap, fmt);
		wchar_t buf[256]{};
		_vswprintf(buf, fmt, ap);
		writeConsoleW(_hConsoleOutput, buf);
		va_end(ap);
		)
	}

	void CConsole::write(const wchar_t* text) {
		NW_NONSHIP_CODE(
		writeConsoleW(_hConsoleOutput, text);
		)
	}

	void CConsole::write(const wchar_t* text, uint64 len) {
		NW_NONSHIP_CODE(
		writeConsoleW(_hConsoleOutput, text, len);
		)
	}

	void* CConsole::getHandle() const {
		return _hConsoleOutput;
	}

	void CConsole::writeFmt(const char* fmt, ...) {
		NW_NONSHIP_CODE(
		va_list ap;
		va_start(ap, fmt);
		char buf[256]{};
		_vsprintf(buf, fmt, ap);
		writeConsoleA(_hConsoleOutput, buf);
		va_end(ap);
		)
	}

	void CConsole::write(const char* text) {
		NW_NONSHIP_CODE(
		writeConsoleA(_hConsoleOutput, text);
		)
	}

	void CConsole::write(const char* text, uint64 len) {
		NW_NONSHIP_CODE(
		writeConsoleA(_hConsoleOutput, text, len);
		)
	}
}

#endif
