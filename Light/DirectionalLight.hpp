#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream> 
#include <vector>
#include <string>
#include "../Shader/Shader.h"

class DirectionalLight{
    public:
    glm::vec3 direction = glm::vec3 (.0f,-1.0f,.0f);

    glm::vec3 color = glm::vec3(1.0f,1.0f,.0f);

    glm::vec3 ambient = glm::vec3(0.2f, 0.2f, 0.2f);
    glm::vec3 diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
    glm::vec3 specular = glm::vec3(0.1f, .1f, .1f);

    void sendToShader(Shader*);

};