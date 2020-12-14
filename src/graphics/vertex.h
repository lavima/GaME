#pragma once

namespace game::graphics {
    
    struct GAME_API Vertex {
        
        glm::vec3 position;
        glm::vec3 color;

        Vertex();
        Vertex(const glm::vec3& position, const glm::vec3& color);
        Vertex(glm::vec3& position, glm::vec3& color);
        Vertex(const Vertex& other);
        ~Vertex();
    
    };
    
}
