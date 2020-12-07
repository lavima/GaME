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

        Font* Load(const std::string& name, int size);

    };

}