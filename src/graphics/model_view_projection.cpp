#include <glm/glm.hpp>

#include "../global.h"
#include "model_view_projection.h"

namespace game::graphics {
    ModelViewProjection::ModelViewProjection() {}
    ModelViewProjection::ModelViewProjection(glm::mat4& model, glm::mat4& view, glm::mat4 projection) {
        this->model = model;
        this->view = view;
        this->projection = projection;
    }
}
