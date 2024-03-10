#pragma once

#include <Engine/BaseWindow.h>
#include <Input/InputDevice.h>

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
		bool			isOpen() const override;
		void			setFullscreen(bool enable = true) override;
		void			setTitle(const CString& title) override;
		void			setMaximized(bool enable = true) override;
		void			suspend(bool enable = true) override;
		void*			getNativeHandle() const override;

		EToggleState*	getKeyboardKeys();
		EKeyMod*		getKeyboardKeysMod();
		void			addReleasedKey(EKey key);
		void			setPos(const Point2i& p);
		void			setSize(const FVec2& s);
	private:
		HWND			createWin32Window();
		static void		EventProcedure(HWND hWnd, const SWindowEventData& e);

	private:
		CString			_title = {};
		EToggleState	_keysStates[CInputDevice::kMaxToggleStates] = {};
		int32			_releasedKeys[8] = {};
		int32			_releasedKeysCount = {};
		EKeyMod			_keysModes[CInputDevice::kMaxToggleStates] = {};
		HWND			_hWnd = nullptr;
		void*			_opengl = nullptr;
	};
}
