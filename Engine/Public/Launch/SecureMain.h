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
		struct ExtraData {
			void* pData;
		};

		void parseCmdLine(const wchar_t* lpCmdLine);
		int32 executeMain();

	private:
		CStaticVector<CStringView, kMaxCmdLineArgs> _args;
		ExtraData									_extraData = {};
	};
}
