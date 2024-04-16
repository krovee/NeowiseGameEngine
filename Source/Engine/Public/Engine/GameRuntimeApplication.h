#pragma once

#include <Engine/Application.h>
#include <Input/InputSystem.h>
#include <Engine/BaseWindow.h>

namespace Neowise {
    /** 
    * Game's runtime instance of application object.
    */
    class NW_API CGameRuntimeApplication final : public CApplication {
    public:
    inline CGameRuntimeApplication(const CStringView& name) : CApplication(E_APPLICATION_TYPE_GAME_RUNTIME, name) 
        {}

        TBool initialize() override;
        void postInitialize() override;
        
        void onRenderFrame() override;
        void onUpdate() override;

        void preShutdown() override;
        void shutdown() override;

    private:
        const CKeyboardInputDevice& keyboard() const;
        const CMouseInputDevice& mouse() const;
        const CBaseWindow& getWindow() const;

    private:
        CKeyboardInputDevice		_kbdDevice = {};
        CMouseInputDevice			_msDevice = {};
        CInputSystem				_inputSystem = {};

        Scope<CBaseWindow>			_window = nullptr;
    };
}
