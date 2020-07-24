/*
File: FontLoader.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::platform {

    class GAME_API Font {

    };

    class FontLoader {

    public:

        Font* Load(const string& name, int size);

    };

}