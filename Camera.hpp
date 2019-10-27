#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream> 
#include <vector>
#include <string>

class Camera
{
private:
    /* data */
    float pitch = .0f;
    float yaw = .0f;
    float roll = .0f;
    float fov = glm::radians(45.0f);

    glm::mat4 projectionMatrix = glm::perspective(fov,1.0f,0.1f,100.0f);;
    glm::mat4 viewMatrix = glm::mat4(1.0);

    glm::vec3 position = glm::vec3(.0f);
    glm::vec3 direction = glm::vec3(.0f,.0f,1.0f);
    glm::vec3 up = glm::vec3(.0f,1.0f,.0f);
    glm::vec3 right = glm::vec3(-1.0f,.0f,.0f);

public:
    Camera(/* args */);
    ~Camera();
    
    void setPitch(float);
    float getPitch();

    void setYaw(float);
    float getYaw();

    void setRoll(float);
    float getRoll();
    
    void setFov(float);
    float getFov();

    void setViewMatrix(glm::mat4);
    glm::mat4* getViewMatrix();

    void setProjectionMatrix(glm::mat4);
    glm::mat4* getProjectionMatrix();

    void setPosition(glm::vec3);
    glm::vec3 getPosition();

    glm::vec3 getDirection();
    void setDirection(glm::vec3);

    glm::vec3 getUp();
    void setUp(glm::vec3);

    glm::vec3 getRight();
    void setRight(glm::vec3);

    void updateMatrix();
};
