#pragma once

#include <Base/NumericTypes.h>
#include <Base/IOBase.h>

namespace Neowise::Platform::Null {
	/** 
	* 
	*/
	class NW_API CConsole : public CIOBase {
	public:
		static const CUUID ioClass;

		CConsole();

		void setTitleFmt(const char* fmt, ...);
		void setTitle(const char* text);
		void writeFmt(const char* fmt, ...) override;
		void write(const char* text) override;
	};

	extern CConsole GConsole;
}
