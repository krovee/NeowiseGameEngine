#include <Engine/EngineLoop.h>
#include <Base/Clock.h>

#include <Engine/GameRuntimeApplication.h>

namespace Neowise {
    TBool GIsExitRequested = kFalse;
    TBool GEditorFrameworkProvided = kFalse;
    TInt32 GExitRequestCode = 0;
    CApplication* GApp = nullptr;
    STimeData* GTime = {};

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

            // Create game runtime.
            GApp = GAlloc->create<CGameRuntimeApplication>("Last Night");
        }

        NW_ASSERT(GApp, "Failed to create GApp!");

        GTime = GAlloc->create<STimeData>();

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

        TReal currentTime = CClock::now().getSeconds();

        while (!isExitRequested()) {
            const TReal newTime = CClock::now().getSeconds();
            GTime->deltaTime = newTime - currentTime;
            GTime->time += GTime->deltaTime;
            currentTime = newTime;

            if (GTime->updateCount == 0) {
                // ->>! This is first loop of the engine !<<-
            }

            const TReal frameBeginTime = CClock::now().getMilliseconds();
            GApp->onRenderFrame();
            const TReal frameEndTime = CClock::now().getMilliseconds();
            GTime->frameTime = frameEndTime - frameBeginTime;
            GTime->frameRate = TReal(1000) / GTime->frameTime;
            ++GTime->frameCount;

            const TReal updateBeginTime = CClock::now().getMilliseconds();
            GApp->onUpdate();
            const TReal updateEndTime = CClock::now().getMilliseconds();
            GTime->updateTime = updateEndTime - updateBeginTime;
            GTime->updateRate = TReal(1000) / GTime->updateTime;
            ++GTime->updateCount;
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

    void CEngineLoop::requestExit(TInt32 code) {
        GExitRequestCode = code;
        GIsExitRequested = kTrue;
    }

}
