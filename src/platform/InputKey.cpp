/*
 * file: InputKey.h
 * author: Lars Vidar Magnusson
 */

#include "../GaME.h"

KeyCode InputKey::GetCode() { return code; }
KeyState InputKey::GetState() { return state; }

void __InputKeyWritable::SetState(KeyState state) { this->state = state; }
