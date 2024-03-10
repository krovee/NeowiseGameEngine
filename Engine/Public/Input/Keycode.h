#pragma once

#include <Base/NumericTypes.h>

namespace Neowise {
	/** 
	* Input keys.
	*/
	enum EKey : uint8 {
		E_KEY_UNDEFINED,

		E_KEY_SPACE,
		E_KEY_ALT,
		E_KEY_CONTROL,
		E_KEY_SUPER,
		E_KEY_SHIFT,
		E_KEY_CAPSLOCK,
		E_KEY_TAB,
		E_KEY_ESCAPE,
		E_KEY_BACKSPACE,
		E_KEY_DEL,
		E_KEY_ENTER,

		E_KEY_FUNC1,
		E_KEY_FUNC2,
		E_KEY_FUNC3,
		E_KEY_FUNC4,
		E_KEY_FUNC5,
		E_KEY_FUNC6,
		E_KEY_FUNC7,
		E_KEY_FUNC8,
		E_KEY_FUNC9,
		E_KEY_FUNC10,

		E_KEY_ARROW_L,
		E_KEY_ARROW_R,
		E_KEY_ARROW_U,
		E_KEY_ARROW_D,

		E_KEY_A,
		E_KEY_B,
		E_KEY_C,
		E_KEY_D,
		E_KEY_E,
		E_KEY_F,
		E_KEY_G,
		E_KEY_H,
		E_KEY_I,
		E_KEY_J,
		E_KEY_K,
		E_KEY_L,
		E_KEY_M,
		E_KEY_N,
		E_KEY_O,
		E_KEY_P,
		E_KEY_Q,
		E_KEY_R,
		E_KEY_S,
		E_KEY_T,
		E_KEY_U,
		E_KEY_V,
		E_KEY_W,
		E_KEY_X,
		E_KEY_Y,
		E_KEY_Z,

		E_KEY_1,
		E_KEY_2,
		E_KEY_3,
		E_KEY_4,
		E_KEY_5,
		E_KEY_6,
		E_KEY_7,
		E_KEY_8,
		E_KEY_9,
		E_KEY_0,

		E_KEY_MINUS,
		E_KEY_EQUALS,
		E_KEY_SQUAREOPEN,
		E_KEY_SQUARECLOSE,
		E_KEY_SEMICOLON,
		E_KEY_QUOT,
		E_KEY_COMMA,
		E_KEY_DOT,
		E_KEY_SLASH,
		E_KEY_APOSTROPHE,
		E_KEY_BACKSLASH,

		E_KEY_MOUSE_BUTTON,
	};

	/** 
	* Modification keys for some primary ones.
	*/
	enum EKeyMod : uint8 {
		E_KEY_MOD_ANY,
		E_KEY_MOD_LEFT,
		E_KEY_MOD_RIGHT,
		E_KEY_MOD_MIDDLE,
		E_KEY_MOD_EXTRA1,
		E_KEY_MOD_EXTRA2,
	};
}
