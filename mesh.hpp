#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream> 
#include <vector>
#include <string>
#include "geometry.hpp"

class Mesh{

    public: 
    geometry * geo;
    std::vector<geometry*> children;
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f);
    glm::mat4 matrix = glm::mat4(1.0f);

    public:
    Mesh(geometry*);
    void addToScene(std::vector<geometry*> *);
    void setScale(glm::vec3);
    glm::vec3 * getScale();
    void setPosition(glm::vec3);
    glm::vec3 * getPosition();
    void setRotation(glm::vec3);
    glm::vec3 * getRotation();

    std::vector<geometry*> getChildren();

    void updateMatrix();


}


void Mesh::setScale(glm::vec3 vec){
   scale = vec;
   updateMatrix();
}

glm::vec3 * Mesh::getScale(){
    return &scale;
}

void Mesh::setPosition(glm::vec3 vec){
    position = vec;
}

glm::vec3 * Mesh::getPosition(){
    return &position;
}

void Mesh::setRotation(glm::vec3 vec){
    rotation = vec;
}

glm::vec3* Mesh::getRotation(){
    return &rotation;
}

void Mesh::updateMatrix(){
    glm::mat4 translateMat = glm::translate(glm::mat4(1.0f) , position);
    glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f) , scale);
    glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f) , rotation.x, glm::vec3(1.0f,.0f,.0f));
    glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f) , rotation.y, glm::vec3(.0f,1.0f,.0f));
    glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f) , rotation.z, glm::vec3(.0f,.0f,1.0f));
    matrix = translateMat * rotateX  * rotateY * rotateZ * scaleMat;
    for(int i= 0; i<children.size(); i++){
        glm::mat4* childMat = children[i]->getMatrix();
        *childMat = matrix * *childMat;
    }
}

std::vector<geometry*> Mesh::getChildren(){
    return children;
}

