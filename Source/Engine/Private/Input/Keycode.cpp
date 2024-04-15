#include <Input/Keycode.h>

namespace Neowise {
    CStringView getEKeyStr(const EKey key) {
        switch (key) {
            default:
            case E_KEY_UNDEFINED: return "<KEY_UNDEFINED>";
            
            case E_KEY_SPACE: return "<KEY_SPACE>";
            case E_KEY_ALT: return "<KEY_ALT>";
            case E_KEY_CONTROL: return "<KEY_CONTROL>";
            case E_KEY_SUPER: return "<KEY_SUPER>";
            case E_KEY_SHIFT: return "<KEY_SHIFT>";
            case E_KEY_CAPSLOCK: return "<KEY_CAPSLOCK>";
            case E_KEY_TAB: return "<KEY_TAB>";
            case E_KEY_ESCAPE: return "<KEY_ESCAPE>";
            case E_KEY_BACKSPACE: return "<KEY_BACKSPACE>";
            case E_KEY_DEL: return "<KEY_DEL>";
            case E_KEY_ENTER: return "<KEY_ENTER>";
            case E_KEY_FUNC1: return "<KEY_FUNC1>";
            case E_KEY_FUNC2: return "<KEY_FUNC2>";
            case E_KEY_FUNC3: return "<KEY_FUNC3>";
            case E_KEY_FUNC4: return "<KEY_FUNC4>";
            case E_KEY_FUNC5: return "<KEY_FUNC5>";
            case E_KEY_FUNC6: return "<KEY_FUNC6>";
            case E_KEY_FUNC7: return "<KEY_FUNC7>";
            case E_KEY_FUNC8: return "<KEY_FUNC8>";
            case E_KEY_FUNC9: return "<KEY_FUNC9>";
            case E_KEY_FUNC10: return "<KEY_FUNC10>";
            case E_KEY_ARROW_L: return "<KEY_ARROW_L>";
            case E_KEY_ARROW_R: return "<KEY_ARROW_R>";
            case E_KEY_ARROW_U: return "<KEY_ARROW_U>";
            case E_KEY_ARROW_D: return "<KEY_ARROW_D>";
            case E_KEY_A: return "<KEY_A>";
            case E_KEY_B: return "<KEY_B>";
            case E_KEY_C: return "<KEY_C>";
            case E_KEY_D: return "<KEY_D>";
            case E_KEY_E: return "<KEY_E>";
            case E_KEY_F: return "<KEY_F>";
            case E_KEY_G: return "<KEY_G>";
            case E_KEY_H: return "<KEY_H>";
            case E_KEY_I: return "<KEY_I>";
            case E_KEY_J: return "<KEY_J>";
            case E_KEY_K: return "<KEY_K>";
            case E_KEY_L: return "<KEY_L>";
            case E_KEY_M: return "<KEY_M>";
            case E_KEY_N: return "<KEY_N>";
            case E_KEY_O: return "<KEY_O>";
            case E_KEY_P: return "<KEY_P>";
            case E_KEY_Q: return "<KEY_Q>";
            case E_KEY_R: return "<KEY_R>";
            case E_KEY_S: return "<KEY_S>";
            case E_KEY_T: return "<KEY_T>";
            case E_KEY_U: return "<KEY_U>";
            case E_KEY_V: return "<KEY_V>";
            case E_KEY_W: return "<KEY_W>";
            case E_KEY_X: return "<KEY_X>";
            case E_KEY_Y: return "<KEY_Y>";
            case E_KEY_Z: return "<KEY_Z>";
            case E_KEY_1: return "<KEY_1>";
            case E_KEY_2: return "<KEY_2>";
            case E_KEY_3: return "<KEY_3>";
            case E_KEY_4: return "<KEY_4>";
            case E_KEY_5: return "<KEY_5>";
            case E_KEY_6: return "<KEY_6>";
            case E_KEY_7: return "<KEY_7>";
            case E_KEY_8: return "<KEY_8>";
            case E_KEY_9: return "<KEY_9>";
            case E_KEY_0: return "<KEY_0>";
            case E_KEY_MINUS: return "<KEY_MINUS>";
            case E_KEY_EQUALS: return "<KEY_EQUALS>";
            case E_KEY_SQUAREOPEN: return "<KEY_SQUAREOPEN>";
            case E_KEY_SQUARECLOSE: return "<KEY_SQUARECLOSE>";
            case E_KEY_SEMICOLON: return "<KEY_SEMICOLON>";
            case E_KEY_QUOT: return "<KEY_QUOT>";
            case E_KEY_COMMA: return "<KEY_COMMA>";
            case E_KEY_DOT: return "<KEY_DOT>";
            case E_KEY_SLASH: return "<KEY_SLASH>";
            case E_KEY_APOSTROPHE: return "<KEY_APOSTROPHE>";
            case E_KEY_BACKSLASH: return "<KEY_BACKSLASH>";
            case E_KEY_MOUSE_BUTTON: return "<KEY_MOUSE_BUTTON>";
        }
    }

    CStringView getEKeyModStr(const EKeyMod mod) {
        switch (mod) {
            default:
                case E_KEY_MOD_ANY: return "<KEY_MOD_ANY>";
                case E_KEY_MOD_LEFT: return "<KEY_MOD_LEFT>";
                case E_KEY_MOD_RIGHT: return "<KEY_MOD_RIGHT>";
                case E_KEY_MOD_MIDDLE: return "<KEY_MOD_MIDDLE>";
                case E_KEY_MOD_EXTRA1: return "<KEY_MOD_EXTRA1>";
                case E_KEY_MOD_EXTRA2: return "<KEY_MOD_EXTRA2>";
        };
    }
}
