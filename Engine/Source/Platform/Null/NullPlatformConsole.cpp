#include <Platform/Null/NullPlatformConsole.h>

namespace Neowise::Platform::Null {
	const CUUID CConsole::ioClass = "NullConsole";

	CConsole::CConsole() : CIOBase(ioClass)
	{
	}
	void CConsole::setTitleFmt(const char* fmt, ...)
	{
	}
	void CConsole::setTitle(const char* text)
	{
	}
	void CConsole::writeFmt(const char* fmt, ...)
	{
	}
	void CConsole::write(const char* text)
	{
	}
}
