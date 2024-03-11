#pragma once

#include "WindowsBase.h"
#include <Base/NumericTypes.h>
#include <Base/IOBase.h>

namespace Neowise::Platform::Windows {
	/**
	*
	*/
	class NW_API CConsole : public CIOBase {
	public:
		static const CUUID ioClass;

		CConsole();
		~CConsole();

		void setTitleFmt(const char* fmt, ...);
		void setTitle(const char* text);
		void writeFmt(const char* fmt, ...) override;
		void write(const char* text) override;
		void write(const char* text, uint64 len) override;
		void writeFmt(const wchar_t* fmt, ...) override;
		void write(const wchar_t* text) override;
		void write(const wchar_t* text, uint64 len) override;
		void* getHandle() const override;

	private:
		HANDLE _hConsoleOutput = nullptr;
		HWND   _hConsoleWindow = nullptr;
	};
}
