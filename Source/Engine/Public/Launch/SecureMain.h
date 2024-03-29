#pragma once

#include <Base/Common.h>

namespace Neowise {
	/** 
	* Safe entry point for an engine. Here all starts.
	*/
	class NW_API CSecureMain {
	public:
		constexpr CSecureMain() = default;

		enum { kMaxCmdLineArgs = 16 };

		void parseCmdLine(const wchar_t *lpCmdLine);
		void parseCmdLine(int32 argc, char **argv);
		int32 executeMain();

	private:
		CStaticVector<CStringView, kMaxCmdLineArgs> _args;
	};
}
