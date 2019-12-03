#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream> 
#include <vector>
#include <string>
#include "../Shader/Shader.h"


class PointLight{

    public:
    
    glm::vec3  position = glm::vec3(.0f,.0f,.0f);
    
    //if spotlight
    glm::vec3 direction;
    float cutOff;
    float outerCutOff;

    glm::vec3 color = glm::vec3(1.0f,1.0f,.0f);

    float constant = 1.0f;
    float linear = 0.09f;
    float quadratic = 0.02f;

    glm::vec3 ambient = glm::vec3(0.05f, 0.05f, 0.05f);
    glm::vec3 diffuse = glm::vec3(0.8f, 0.8f, 0.8f);
    glm::vec3 specular = glm::vec3(0.1f, .1f, .1f);

    int lightId;
    
    PointLight();
    
    glm::vec3 getPosition();
    glm::vec3 getDirection();
    glm::vec3 getColor();
    float getIntensity();

    void setPosition(glm::vec3 pos);
    void setDirection(glm::vec3 rot);
    void setColor(glm::vec3 col);
    void setIntensity(float intensity);


    void sendToShader(Shader *);
    void sendAsSpotlight(Shader*);

    int active = 0;

};

