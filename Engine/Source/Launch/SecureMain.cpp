#include <Launch/SecureMain.h>
#include <Engine/EngineBoot.h>
#include <Engine/EngineLoop.h>

namespace Neowise {
	bool GIsRestarting = true;
	extern CEngineLoop* GEngineLoop;

	namespace {
		CEngineBoot sBoot = {};
	}

	void CSecureMain::parseCmdLine(const wchar_t* lpCmdLine) {
		NW_PROFILE_FUNCTION();

		// TODO(krovee): Add a parser to manage command line arguments.

	}

    void CSecureMain::parseCmdLine(int32 argc, char **argv) {
		NW_PROFILE_FUNCTION();
    
		// TODO(krovee): Add a parser to manage command line arguments.
	}
    
	int32 CSecureMain::executeMain()
    {
        NW_PROFILE_FUNCTION();

		while (GIsRestarting) {
			GIsRestarting = false;

			DEngineBootInfo eBootInfo = {};
			eBootInfo.baseScenePath = "";

			struct ExitGuard {
				~ExitGuard() {
					sBoot.earlyShutdown();

					sBoot.lateShutdown();
				}
			} exitGuard = {};

			if (const auto v = sBoot.earlyInit(eBootInfo); v != E_ENGINE_BOOT_SUCCESS) {
				return int32(v);
			}

			if (const auto v = sBoot.lateInit(); v != E_ENGINE_BOOT_SUCCESS) {
				return int32(v);
			}

			GEngineLoop->run();

		}

		return GExitRequestCode;
    }
}
