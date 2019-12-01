#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream> 
#include <vector>
#include <string>
#include "../Mesh/Mesh.hpp"


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
    Mesh * mesh;

    public:
    Car();

    Mesh* getMesh();
    
   
};

Car::Car(){
    Material * carMat = new Material(glm::vec3(0.1f), glm::vec3(0.5f) , glm::vec3(0.5f), 2.0f, glm::vec3(0.f,1.000f,0.1f) );
    Geometry* mainBodyGeo = new Geometry(&cubePositions, GL_TRIANGLES, false, NULL, NULL);
    Mesh * mainBody = new Mesh(mainBodyGeo , carMat); 
    //mainBody->setLocalMatrix(glm::scale(glm::translate(glm::mat4(1.0f),glm::vec3(.0f, 1.0f, .0f)), glm::vec3(1.0f,2.0f,2.0f)));
    //mainBody->add(mainBody);
    mainBody->setPosition(glm::vec3(.0f,1.5f,.0f));
    mainBody->setScale(glm::vec3(1.0,2.0,2.0));
    Geometry* leftBackWheelGeo = new Geometry(&cylinderPositions, GL_TRIANGLES , true, &cylinderIndecies,NULL);
    Mesh* leftBackWheel = new Mesh(leftBackWheelGeo , carMat);
    leftBackWheel->setScale(glm::vec3(0.5f,.25f,.5f));
    leftBackWheel->setRotation(glm::vec3(.0f,.0f,glm::radians(90.0f)));
    leftBackWheel->setPosition(glm::vec3(-.625f, - 0.5f , 1.0f));
    mainBody->add(leftBackWheel);
    Geometry* rightBackWheelGeo = new Geometry(&cylinderPositions, GL_TRIANGLES , true, &cylinderIndecies,NULL);
    Mesh * rightBackWheel = new Mesh(rightBackWheelGeo, carMat);
    rightBackWheel->setScale(glm::vec3(0.5f,.25f,.5f));
    rightBackWheel->setRotation(glm::vec3(.0f,.0f,glm::radians(90.0f)));
    rightBackWheel->setPosition(glm::vec3(.625f, -0.5f , 1.0f));
    mainBody->add(rightBackWheel);
    Geometry* leftFrontWheelGeo = new Geometry(&cylinderPositions, GL_TRIANGLES , true, &cylinderIndecies,NULL);
    Mesh* leftFrontWheel = new Mesh(leftFrontWheelGeo , carMat);
    leftFrontWheel->setScale(glm::vec3(0.5f,.25f,.5f));
    leftFrontWheel->setRotation(glm::vec3(.0f,.0f,glm::radians(90.0f)));
    leftFrontWheel->setPosition(glm::vec3(-.625f, - 0.5f , -1.0f));
    mainBody->add(leftFrontWheel);
    Geometry* rightFrontWheelGeo = new Geometry(&cylinderPositions, GL_TRIANGLES , true, &cylinderIndecies,NULL);
    Mesh* rightFrontWheel = new Mesh(rightFrontWheelGeo , carMat);
    rightFrontWheel->setScale(glm::vec3(0.5f,.25f,.5f));
    rightFrontWheel->setRotation(glm::vec3(.0f,.0f,glm::radians(90.0f)));
    rightFrontWheel->setPosition(glm::vec3(.625f, -.5f , -1.0f));
    mainBody->add(rightFrontWheel);
    Geometry*  roofGeo =  new Geometry(&cubePositions, GL_TRIANGLES, false, NULL, NULL);
    Mesh* roof = new Mesh(roofGeo , carMat);
    //roof->setLocalMatrix(glm::scale(glm::translate(glm::mat4(1.0f),glm::vec3(.0f, 2.0f + 0.5f , .0f)), glm::vec3(1.0f,1.0f,1.0f)));
    roof->setPosition(glm::vec3(.0f,1.0f,.0f));
    mainBody->add(roof);
    Geometry* trunkGeo= new Geometry(&cubePositions, GL_TRIANGLES, false, NULL, NULL);
    Mesh* trunk = new Mesh(trunkGeo , carMat);
    trunk->setPosition(glm::vec3(.0f,.0f,1.0f));
    //trunk->setLocalMatrix(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(.0f,.5f,1.25f)), glm::vec3(1.0f,1.0f,1.0f)));
    mainBody->add(trunk);
    Geometry* bonnetGeo = new Geometry(&cubePositions, GL_TRIANGLES, false, NULL, NULL);
    Mesh* bonnet = new Mesh(bonnetGeo , carMat);
    bonnet->setPosition(glm::vec3(.0f,.0f,-1.0f));
    //bonnet->setLocalMatrix(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(.0f,.5f,-1.25f)), glm::vec3(1.0f,1.0f,1.0f)));
    mainBody->add(bonnet);

    mesh = mainBody;
}

Mesh* Car::getMesh(){
    return mesh;
}
