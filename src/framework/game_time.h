/*
File: GameTime.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::framework {

    struct GAME_API GameTime {
    public:

        double time_since_start;
        double time_since_previous;

    };

}