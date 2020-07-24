/*
 * file: InputKey.h
 * author: Lars Vidar Magnusson
 */

#include "../GaME.h"

namespace game::platform {

    KeyCode InputKey::GetCode() { return code; }
    KeyState InputKey::GetState() { return state; }

    void InputKeyWritable::SetState(KeyState state) { this->state = state; }

}