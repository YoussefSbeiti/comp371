#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream> 
#include <vector>
#include <string>
#include "geometry.hpp"


std::vector<float> cylinderPositions {0,0.5,1,0,0,1,0.7071067690849304,0.5,0.7071067690849304,0.7071067690849304,0,0.7071067690849304,1,0.5,0,1,0,0,0.7071067690849304,0.5,-0.7071067690849304,0.7071067690849304,0,-0.7071067690849304,0,0.5,-1,0,0,-1,-0.7071067690849304,0.5,-0.7071067690849304,-0.7071067690849304,0,-0.7071067690849304,-1,0.5,-0,-1,0,-0,-0.7071067690849304,0.5,0.7071067690849304,-0.7071067690849304,0,0.7071067690849304,-0,0.5,1,-0,0,1,0,-0.5,1,0,0,1,0.7071067690849304,-0.5,0.7071067690849304,0.7071067690849304,0,0.7071067690849304,1,-0.5,0,1,0,0,0.7071067690849304,-0.5,-0.7071067690849304,0.7071067690849304,0,-0.7071067690849304,0,-0.5,-1,0,0,-1,-0.7071067690849304,-0.5,-0.7071067690849304,-0.7071067690849304,0,-0.7071067690849304,-1,-0.5,-0,-1,0,-0,-0.7071067690849304,-0.5,0.7071067690849304,-0.7071067690849304,0,0.7071067690849304,-0,-0.5,1,-0,0,1,0,0.5,0,0,1,0,0,0.5,0,0,1,0,0,0.5,0,0,1,0,0,0.5,0,0,1,0,0,0.5,0,0,1,0,0,0.5,0,0,1,0,0,0.5,0,0,1,0,0,0.5,0,0,1,0,0,0.5,1,0,1,0,0.7071067690849304,0.5,0.7071067690849304,0,1,0,1,0.5,0,0,1,0,0.7071067690849304,0.5,-0.7071067690849304,0,1,0,0,0.5,-1,0,1,0,-0.7071067690849304,0.5,-0.7071067690849304,0,1,0,-1,0.5,-0,0,1,0,-0.7071067690849304,0.5,0.7071067690849304,0,1,0,-0,0.5,1,0,1,0,0,-0.5,0,0,-1,0,0,-0.5,0,0,-1,0,0,-0.5,0,0,-1,0,0,-0.5,0,0,-1,0,0,-0.5,0,0,-1,0,0,-0.5,0,0,-1,0,0,-0.5,0,0,-1,0,0,-0.5,0,0,-1,0,0,-0.5,1,0,-1,0,0.7071067690849304,-0.5,0.7071067690849304,0,-1,0,1,-0.5,0,0,-1,0,0.7071067690849304,-0.5,-0.7071067690849304,0,-1,0,0,-0.5,-1,0,-1,0,-0.7071067690849304,-0.5,-0.7071067690849304,0,-1,0,-1,-0.5,-0,0,-1,0,-0.7071067690849304,-0.5,0.7071067690849304,0,-1,0,-0,-0.5,1,0,-1,0};
std::vector<int> cylinderIndecies {0,9,1,9,10,1,1,10,2,10,11,2,2,11,3,11,12,3,3,12,4,12,13,4,4,13,5,13,14,5,5,14,6,14,15,6,6,15,7,15,16,7,7,16,8,16,17,8,26,27,18,27,28,19,28,29,20,29,30,21,30,31,22,31,32,23,32,33,24,33,34,25,44,43,35,45,44,36,46,45,37,47,46,38,48,47,39,49,48,40,50,49,41,51,50,42};

std::vector<float> cubePositions {
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };


class Car{
    private: 
    std::vector<geometry*> children;
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f);
    glm::mat4 matrix = glm::mat4(1.0f);

    public:
    Car();
    void addToScene(std::vector<geometry*> *);
    void setScale(glm::vec3);
    glm::vec3 * getScale();
    void setPosition(glm::vec3);
    glm::vec3  getPosition();
    void setRotation(glm::vec3);
    glm::vec3 * getRotation();

    std::vector<geometry*> getChildren();

    void updateMatrix();
   
};

void Car::addToScene(std::vector<geometry*> * scene){
    for(int i= 0; i<children.size(); i++){
       scene->push_back(children[i]);
    }
}

Car::Car(){
    geometry* mainBody = new geometry(&cubePositions, GL_TRIANGLES, false, NULL, NULL);
    mainBody->setMatrix(glm::scale(glm::translate(glm::mat4(1.0f),glm::vec3(.0f, 1.0f, .0f)), glm::vec3(1.0f,2.0f,2.0f)));
    children.push_back(mainBody);
    geometry* leftBackWheel = new geometry(&cylinderPositions, GL_TRIANGLES , true, &cylinderIndecies,NULL);
    //leftBackWheel->setMatrix(glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f),glm::vec3(-.625f, 0.0f + 0.0f , 1.0f)), glm::radians(90.0f) , glm::vec3(0.0f,0.0f,1.0f)), glm::vec3(0.5f,.25f,.5f)));
    leftBackWheel->setScale(glm::vec3(0.5f,.25f,.5f));
    leftBackWheel->setRotation(glm::vec3(.0f,.0f,glm::radians(90.0f)));
    leftBackWheel->setPosition(glm::vec3(-.625f, 0.0f + 0.0f , 1.0f));
    children.push_back(leftBackWheel);
    geometry* rightBackWheel = new geometry(&cylinderPositions, GL_TRIANGLES , true, &cylinderIndecies,NULL);
    //rightBackWheel->setMatrix(glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f),glm::vec3(.625f, 0.0f + 0.0f , 1.0f)), glm::radians(90.0f) , glm::vec3(0.0f,0.0f,1.0f)), glm::vec3(0.5f,.25f,.5f)));
    rightBackWheel->setScale(glm::vec3(0.5f,.25f,.5f));
    rightBackWheel->setRotation(glm::vec3(.0f,.0f,glm::radians(90.0f)));
    rightBackWheel->setPosition(glm::vec3(.625f, 0.0f + 0.0f , 1.0f));
    children.push_back(rightBackWheel);
    geometry* leftFrontWheel = new geometry(&cylinderPositions, GL_TRIANGLES , true, &cylinderIndecies,NULL);
    //leftFrontWheel->setMatrix(glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f),glm::vec3(-.625f, 0.0f + 0.0f , -1.0f)), glm::radians(90.0f) , glm::vec3(0.0f,0.0f,1.0f)), glm::vec3(0.5f,.25f,.5f)));
    leftFrontWheel->setScale(glm::vec3(0.5f,.25f,.5f));
    leftFrontWheel->setRotation(glm::vec3(.0f,.0f,glm::radians(90.0f)));
    leftFrontWheel->setPosition(glm::vec3(-.625f, 0.0f + 0.0f , -1.0f));
    children.push_back(leftFrontWheel);
    geometry* rightFrontWheel = new geometry(&cylinderPositions, GL_TRIANGLES , true, &cylinderIndecies,NULL);
    //rightFrontWheel->setMatrix(glm::scale(glm::rotate(glm::translate(glm::mat4(1.0f),glm::vec3(.625f, 0.0f + 0.0f , -1.0f)), glm::radians(90.0f) , glm::vec3(0.0f,0.0f,1.0f)), glm::vec3(0.5f,.25f,.5f)));
    rightFrontWheel->setScale(glm::vec3(0.5f,.25f,.5f));
    rightFrontWheel->setRotation(glm::vec3(.0f,.0f,glm::radians(90.0f)));
    rightFrontWheel->setPosition(glm::vec3(.625f, 0.0f + 0.0f , -1.0f));
    children.push_back(rightFrontWheel);
    geometry*  roof = new geometry(mainBody);
    roof->setMatrix(glm::scale(glm::translate(glm::mat4(1.0f),glm::vec3(.0f, 2.0f + 0.5f , .0f)), glm::vec3(1.0f,1.0f,1.5f)));
    children.push_back(roof);
    geometry* trunk= new geometry(mainBody);
    trunk->setMatrix(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(.0f,.5f,1.25f)), glm::vec3(1.0f,1.0f,1.5f)));
    children.push_back(trunk);
    geometry* bonnet = new geometry(mainBody);
    bonnet->setMatrix(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(.0f,.5f,-1.25f)), glm::vec3(1.0f,1.0f,1.5f)));
    children.push_back(bonnet);
}

void Car::setScale(glm::vec3 vec){
   scale = vec;
   updateMatrix();
}

glm::vec3 * Car::getScale(){
    return &scale;
}

void Car::setPosition(glm::vec3 vec){
    position = vec;
    updateMatrix();
}

glm::vec3  Car::getPosition(){
    return position;
}

void Car::setRotation(glm::vec3 vec){
    rotation = vec;
    updateMatrix();
}

glm::vec3* Car::getRotation(){
    return &rotation;
}

void Car::updateMatrix(){
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

std::vector<geometry*> Car::getChildren(){
    return children;
}


