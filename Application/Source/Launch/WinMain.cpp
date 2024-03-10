
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include <Base/Export.h>
#include <Base/NumericTypes.h>
#include <Launch/SecureMain.h>

using namespace Neowise;

int32 wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int32 nShowCmd) {
	CSecureMain secMain;

	secMain.parseCmdLine(lpCmdLine);

	return secMain.executeMain();
}
