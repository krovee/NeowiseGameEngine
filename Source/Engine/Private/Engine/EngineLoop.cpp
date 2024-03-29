#include <Engine/EngineLoop.h>
#include <Base/Clock.h>

#include <Engine/GameRuntimeApplication.h>

namespace Neowise {
	bool GIsExitRequested = false;
	bool GEditorFrameworkProvided = false;
	int32 GExitRequestCode = 0;
	CApplication* GApp = nullptr;
	STimeData GTime = {};

	CEngineLoop* CEngineLoop::instantiate() {
		NW_PROFILE_FUNCTION();

		if (!GEngineLoop) {
			void* p = GAlloc->allocate(sizeof(CEngineLoop));
			NW_ASSERT(p, "Failed to allocate GEngineLoop! (should never hit)");
			Memory::clear(p, sizeof(CEngineLoop));
			return reinterpret_cast<CEngineLoop*>(p);
		}
		return GEngineLoop;
	}

	EEngineLoop CEngineLoop::setupSystems() {
		NW_PROFILE_FUNCTION();

		if (isEditor()) {
			NW_PROFILE_SCOPE("Editor instantiation");
			// Startup editor instead of just game runtime.
			//auto p = GAlloc->allocate(sizeof(CEditorFrameworkApplication));
			//GApp = reinterpret_cast<CEditorFrameworkApplication*>(p);
			//construct_at(*GApp);
		}
		else {
			NW_PROFILE_SCOPE("Game runtime instantiation");

			// Startup game runtime.
			auto p = GAlloc->allocate(sizeof(CGameRuntimeApplication));
			GApp = reinterpret_cast<CGameRuntimeApplication*>(p);
			construct_at<CGameRuntimeApplication>(GApp, "Last Night");
		}

		NW_ASSERT(GApp, "Failed to create GApp!");

		if (!GApp->initialize()) {
			return E_ENGINE_LOOP_APP_INIT_FAIL;
		}

		return E_ENGINE_LOOP_SETUP_SUCCESS;	
	}

	void CEngineLoop::load() {
		NW_PROFILE_FUNCTION();

		GApp->postInitialize();
		
	}

	void CEngineLoop::run() {

		real currentTime = CClock::now().getSeconds();

		while (!isExitRequested()) {
			const real newTime = CClock::now().getSeconds();
			GTime.deltaTime = newTime - currentTime;
			GTime.time += GTime.deltaTime;
			currentTime = newTime;

			if (GTime.updateCount == 0) {
				
			}

			const real frameBeginTime = CClock::now().getMilliseconds();
			GApp->onRenderFrame();
			const real frameEndTime = CClock::now().getMilliseconds();
			GTime.frameTime = frameEndTime - frameBeginTime;
			GTime.frameRate = real(1000) / GTime.frameTime;
			++GTime.frameCount;

			const real updateBeginTime = CClock::now().getMilliseconds();
			GApp->onUpdate();
			const real updateEndTime = CClock::now().getMilliseconds();
			GTime.updateTime = updateEndTime - updateBeginTime;
			GTime.updateRate = real(1000) / GTime.updateTime;
			++GTime.updateCount;
		}

	}

	void CEngineLoop::releaseResources() {
		NW_PROFILE_FUNCTION();

		GApp->preShutdown();
	}

	void CEngineLoop::shutdown() {
		NW_PROFILE_FUNCTION();
		
		GApp->shutdown();
		GAlloc->free(this, sizeof(CEngineLoop));
	}

	void CEngineLoop::requestExit(int32 code) {
		GExitRequestCode = code;
		GIsExitRequested = true;
	}

}
