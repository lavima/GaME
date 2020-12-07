/*
 * file: InputKey.h
 * author: Lars Vidar Magnusson
 */

#pragma once

namespace game::platform {

    enum KeyCode {
        KEY_BACKSPACE,
        KEY_TAB,
        KEY_CAPSLOCK,
        KEY_ENTER,
        KEY_LEFT_SHIFT,
        KEY_RIGHT_SHIFT,
        KEY_LEFT_CTRL,
        KEY_LEFT_SUPER,
        KEY_LEFT_ALT,
        KEY_SPACE,
        KEY_RIGHT_ALT,
        KEY_RIGHT_SUPER,
        KEY_MENU,
        KEY_RIGHT_CTRL,
        KEY_GRAVEACCENT,
        KEY_DASH,
        KEY_EQUAL,
        KEY_LEFTBRACKET,
        KEY_RIGHTBRACKET,
        KEY_BACKSLASH,
        KEY_SEMICOLON,
        KEY_APOSTROPHE,
        KEY_COMMA,
        KEY_PERIOD,
        KEY_SLASH,
        KEY_1,
        KEY_2,
        KEY_3,
        KEY_4,
        KEY_5,
        KEY_6,
        KEY_7,
        KEY_8,
        KEY_9,
        KEY_0,
        KEY_Q,
        KEY_W,
        KEY_E,
        KEY_R,
        KEY_T,
        KEY_Y,
        KEY_U,
        KEY_I,
        KEY_O,
        KEY_P,
        KEY_A,
        KEY_S,
        KEY_D,
        KEY_F,
        KEY_G,
        KEY_H,
        KEY_J,
        KEY_K,
        KEY_L,
        KEY_Z,
        KEY_X,
        KEY_C,
        KEY_V,
        KEY_B,
        KEY_N,
        KEY_M
    };

    enum KeyState {
        KEY_PRESSED,
        KEY_RELEASED
    };

    class GAME_API InputKey {
    private:

        KeyCode code;

    protected:
        KeyState state;

    public:

        InputKey(KeyCode code);

        KeyCode GetCode();
        KeyState GetState();

    };

    class GAME_API InputKeyWritable : public InputKey {

    public:

        void SetState(KeyState state);

    };

}