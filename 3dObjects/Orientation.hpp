#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/string_cast.hpp>
//#include <GL/glew.h>
//#include <GL/glu.h>
#include <iostream> 
#include <vector>
#include <string>

class Orientation{
    private:

    public:

    glm::vec3 up ;
    glm::vec3 right;
    glm::vec3 direction;

    float pitch = .0f;
    float yaw = .0f;
    float roll = .0f;

    Orientation();

    void setPitch(float);
    float getPitch();

    void setYaw(float);
    float getYaw();

    void setRoll(float);
    float getRoll();

    void updateDirection();

    glm::vec3 getDirection();
    void setDirection(glm::vec3);

    glm::vec3 getUp();
    void setUp(glm::vec3);

    glm::vec3 getRight();
    void setRight(glm::vec3);

    void updateOrientation();
};
