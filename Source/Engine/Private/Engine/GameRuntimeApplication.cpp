#include <Engine/GameRuntimeApplication.h>
#include <Engine/EngineLoop.h>

#include <Engine/RenderThread.h>

namespace Neowise {
	TBool CGameRuntimeApplication::initialize() {
		NW_PROFILE_FUNCTION();

        _window = move(CBaseWindow::createDefault());
        NW_ASSERT(_window.get(), "Cannot create CBaseWindow object!");
        _inputSystem.addDevice(_kbdDevice);
        _inputSystem.addDevice(_msDevice);
        _inputSystem.update(_window.get());

        return kTrue;
    }

    void CGameRuntimeApplication::postInitialize() {
        NW_PROFILE_FUNCTION();

        // Initializes core of render thread (not the loading!)
        GRenderThread->initializeBasic(_window.get());

        // Spawn and run separate render thread, means all loading and
        // stuff should be delivered to render thread, or...>?
        // Maybe we should have another special loader-thread that will
        // do all loading stuff and notifying both render and main threads
        // about done work?
        CRenderThread::spawn();
    }

    void CGameRuntimeApplication::onRenderFrame() {
        if (GRenderThread->startFrameRecord()) {
            // Record GPU commands (make drawcalls)
            GRenderThread->endFrameRecord();
        }
    }

    void CGameRuntimeApplication::onUpdate() {

        if (keyboard().isKeysPressed({E_KEY_Q, E_KEY_CONTROL})) {
            GEngineLoop->requestExit();
        }
        
        if (GTime->updateCount % 1000 == 0) {
            static CString title = {};
            CStringBuilder sb(title);

            sb << "time: " << GTime->time << "s dt: " << GTime->deltaTime << " frmr: " << GTime->frameRate << "s upr: " << GTime->updateRate ;
            _window->setTitle(title);
            title.clear();
        }

        _window->update();
    }

    void CGameRuntimeApplication::preShutdown() {
        GRenderThread->waitResourcesIdle();

    }

    void CGameRuntimeApplication::shutdown() {
        NW_PROFILE_FUNCTION();
    }

    const CKeyboardInputDevice& CGameRuntimeApplication::keyboard() const {
        return _kbdDevice;
    }

    const CMouseInputDevice& CGameRuntimeApplication::mouse() const {
        return _msDevice;
    }

    const CBaseWindow& CGameRuntimeApplication::getWindow() const {
        return *_window;
    }

}
