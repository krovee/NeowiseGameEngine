#pragma once

#include <Engine/BaseWindow.h>
#include <Input/InputDevice.h>
#include <Engine/EngineEvents.h>

#include "WindowsBase.h"

namespace Neowise::Platform::Windows {
    /**
    *
    */
    class NW_API CBaseWindow : Neowise::CBaseWindow {
    public:
        struct defaultCreateTag {};

        CBaseWindow(defaultCreateTag);
        virtual ~CBaseWindow();

        void			update() override;
        TBool			isOpen() const override;
        void			setFullscreen(TBool enable = kTrue) override;
        void			setTitle(const CString& title) override;
        void			setMaximized(TBool enable = kTrue) override;
        void			suspend(TBool enable = kTrue) override;
        void*			getNativeHandle() const override;

        EToggleState*	getKeyboardKeys();
        EKeyMod*		getKeyboardKeysMod();
        void			addReleasedKey(EKey key);
        void			setPos(const Point2i& p);
        void			setSize(const FVec2& s);
    private:
        HWND			createWin32Window();
        static void		EventProcedure(HWND hWnd, const SWindowEventData& e);

        static void 	updateKeysState(const CEventWindowInputKeyboard& e);
        static void 	updateKeysState(const CEventWindowInputMouseButton& e);
    private:
        CString			_title = {};
        static inline EToggleState		_keysStates[CInputDevice::kMaxToggleStates] = {};
        static inline TInt32				_releasedKeys[8] = {};
        static inline TInt32				_releasedKeysCount = {};
        static inline EKeyMod			_keysModes[CInputDevice::kMaxToggleStates] = {};
        HWND			_hWnd = nullptr;
        void*			_opengl = nullptr;
    };
}
