#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream> 
#include <vector>
#include <string>
#include "../Shader/Shader.h"


class Light{

    private:
    
    glm::vec3 position = glm::vec3(.0f,.0f,.0f);
    glm::vec3 direction = glm::vec3 (.0f,.0f,.0f);

    glm::vec3 color = glm::vec3(1.0f,1.0f,.0f);
    float intensity = 1.0;

    public:
    
    Light();

    glm::vec3 getPosition();
    glm::vec3 getDirection();
    glm::vec3 getColor();
    float getIntensity();

    void setPosition(glm::vec3 pos);
    void setDirection(glm::vec3 rot);
    void setColor(glm::vec3 col);
    void setIntensity(float intensity);


    void sendToShader(Shader *);
};

