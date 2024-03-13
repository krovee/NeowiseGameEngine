#include <Base/MacroUtils.h>

#if NW_OS(WIN32)

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <Launch/SecureMain.h>

using namespace Neowise;

int32 wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int32 nShowCmd) {
	CSecureMain secMain;

	secMain.parseCmdLine(lpCmdLine);

	return secMain.executeMain();
}

#endif
