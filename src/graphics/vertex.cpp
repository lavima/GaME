#include <glm/glm.hpp>

#include "../global.h"
#include "vertex.h"

namespace game::graphics {

    Vertex::Vertex() {}

    Vertex::Vertex(const glm::vec3& position, const glm::vec3& color) {
      this->position = position;
      this->color = color;
    }
            
    Vertex::Vertex(glm::vec3& position, glm::vec3& color) {
      this->position = position;
      this->color = color;
    }
            
    Vertex::Vertex(const Vertex& other) {
        this->position = other.position;
        this->color = other.color;
    }

    Vertex::~Vertex() {}

}
