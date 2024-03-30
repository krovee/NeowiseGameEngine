#pragma once

#include "Engine/EngineEvents.h"
#include <Engine/BaseWindow.h>
#include <Input/InputDevice.h>
#include <Platform/Linux/LinuxBase.h>

namespace Neowise::Platform::Linux {
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

		static 			void updateKeysState(const CEventWindowInputKeyboard& e);
		static 			void updateKeysState(const CEventWindowInputMouseButton& e);
	private:
		CString						_title = {};
		static inline EToggleState	_keysStates[CInputDevice::kMaxToggleStates] = {};
		static inline EKeyMod		_keysModes[CInputDevice::kMaxToggleStates] = {};
		int32						_releasedKeys[8] = {};
		int32						_releasedKeysCount = {};
		bool						_dirty = false;
		_WindowID					_id 	= _WindowID(-1);
	};
}
