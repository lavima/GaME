/*
File: Entity.h
Author: Lars Vidar Magnusson
*/

#pragma once

namespace game::framework {

    class GAME_API Entity {
    private:

        string name_;

        //unordered_map<string, unique_ptr<Component>> components_;

        Entity(const string& name);

    public:

        static Entity* Create(const string& name);

        void Initialize();
        void Update(GameTime& gameTime);

    };

}