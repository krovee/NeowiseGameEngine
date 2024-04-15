#include "Input/Keycode.h"
#include <Engine/EngineBoot.h>
#include <Engine/EngineLoop.h>
#include <Engine/Events/Bus.h>
#include <Engine/EngineEvents.h>

#include <Engine/RenderThread.h>

namespace Neowise {
    CStringView		GBaseScenePath = "";
    CEngineLoop*	GEngineLoop = nullptr;

    EEngineBoot CEngineBoot::earlyInit(DEngineBootInfo const& info) {
        NW_PROFILE_FUNCTION();
        
        GEventBus = reinterpret_cast<CEventBus*>(GAlloc->allocate(sizeof(CEventBus)));
        construct_at(*GEventBus);

        GEngineLoop = CEngineLoop::instantiate();
        if (!GEngineLoop || isExitRequested()) {
            return E_ENGINE_BOOT_ERROR_CANT_INSTANTIATE_LOOP;
        }

        GEventBus->subscribe<CEventWindowClose>([](const CEventWindowClose&){
            GEngineLoop->requestExit(0);
        });

        GEventBus->subscribe<CEventWindowGotFocus>([](const CEventWindowGotFocus&){
            GDiag << "Window got focused!\n";
        });

        GEventBus->subscribe<CEventWindowLostFocus>([](const CEventWindowLostFocus&){
            GDiag << "Window lost focus..\n";
        });

        GEventBus->subscribe<CEventWindowSuspended>([](const CEventWindowSuspended&){
            GDiag << "Window suspended..ZzZzZzzz\n";
        });

        GEventBus->subscribe<CEventWindowMoved>([](const CEventWindowMoved& e){
            GDiag << "Window pos(" << e.getX() << ", " << e.getY() << ")\n";
        });

        GEventBus->subscribe<CEventWindowResized>([](const CEventWindowResized& e){
            GDiag << "Window(" << e.getWidth() << ", " << e.getHeight() << ")\n";
        });

        GEventBus->subscribe<CEventWindowInputKeyboard>([](const CEventWindowInputKeyboard& e){
            GDiag << "Key: " << EKey(e.getKey()) << "(" << e.isPressed() << ")\n";
        });

        GEventBus->subscribe<CEventWindowInputMouseButton>([](const CEventWindowInputMouseButton& e){
            GDiag << "Mouse: " << EMouseButton(e.getButton()) << "(" << e.isPressed() << ")\n";
        });


        GBaseScenePath = info.baseScenePath;
        NW_OPT_ASSERT(!GBaseScenePath.empty(), "No base scene path was provided!");

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
