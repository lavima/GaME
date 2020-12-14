#pragma once

namespace game::graphics {

    struct GAME_API ModelViewProjection {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;

        ModelViewProjection();
        ModelViewProjection(glm::mat4& model, glm::mat4& view, glm::mat4 projection);
    };

}
