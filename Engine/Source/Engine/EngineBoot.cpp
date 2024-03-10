#include <Engine/EngineBoot.h>
#include <Engine/EngineLoop.h>

#include <Engine/RenderThread.h>

namespace Neowise {
	CStringView		GBaseScenePath = "Unknown";
	CEngineLoop*	GEngineLoop = nullptr;

	EEngineBoot CEngineBoot::earlyInit(DEngineBootInfo const& info) {
		NW_PROFILE_FUNCTION();
		
		GBaseScenePath = info.baseScenePath;
		NW_OPT_ASSERT(!GBaseScenePath.empty(), "No base scene path was provided!");

		GEngineLoop = CEngineLoop::instantiate();
		if (!GEngineLoop || isExitRequested()) {
			return E_ENGINE_BOOT_ERROR_CANT_INSTANTIATE_LOOP;
		}


		return E_ENGINE_BOOT_SUCCESS;
	}

	EEngineBoot CEngineBoot::lateInit() {
		NW_PROFILE_FUNCTION();

		if (const auto e = GEngineLoop->setupSystems(); e != E_ENGINE_LOOP_SETUP_SUCCESS) {
			return E_ENGINE_BOOT_ERROR_SETUP_SYSTEMS;
		}

		const auto rtInitialized = RT_Initialize();
		NW_ASSERT(rtInitialized, "Failed to initialize render thread! See above messages for more info..");

		GEngineLoop->load();

		return E_ENGINE_BOOT_SUCCESS;
	}

	void CEngineBoot::earlyShutdown() {
		NW_PROFILE_FUNCTION();
		NW_ASSERT(GEngineLoop, "GEngineLoop was NULL.");

		GEngineLoop->releaseResources();
	}

	void CEngineBoot::lateShutdown() {
		NW_PROFILE_FUNCTION();
		NW_ASSERT(GEngineLoop, "GEngineLoop was NULL.");

		const auto rtShutdowned = RT_Shutdown();
		NW_ASSERT(rtShutdowned, "Failed to shutdown render thread! See more info in messages above..");
		
		GEngineLoop->shutdown();
	}
}
