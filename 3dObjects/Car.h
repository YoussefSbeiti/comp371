#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream> 
#include <vector>
#include <string>
#include "../Mesh/Mesh.hpp"
#include "Orientation.hpp"
#include "../Light/PointLight.hpp"
#include "../Camera/Camera.hpp"
#include "../Shader/Shader.h"


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
    
    glm::vec3 position;

    glm::vec3 color = glm::vec3(0.f,1.000f,0.1f);

    Material * carMat = new Material(glm::vec3(0.1f), glm::vec3(0.5f) , glm::vec3(0.5f), 2.0f, color);

    static int carID;
    //glm::quatLookAt(mesh->getPosition() , )

    public:
    Car();

    PointLight* headLight1 = new PointLight();
    //PointLight* headLight2 = new PointLight();
    PointLight* tailLight1 = new PointLight();
    //PointLight* tailLight2 = new PointLight();

    Orientation* orientation;

    Camera* attachedCam = NULL;

    Mesh* getMesh();

    void moveForward(float);

    void moveRight();

    void rotateFrontWheels();

    void spinWheels();
    
    glm::vec3 getPosition();
    void setPosition(glm::vec3);

    void attachCamera(Camera *);

    void attachHeadlight();
    void attachTailLights();

    void updateHeadlightPositions();
    void updateTaillightPositions();

    void setColor(glm::vec3);

    void setRotation(float);

    void render(Shader*);

    int activeLight = 1;


};

Car::Car(){
    orientation = new Orientation();
    Geometry* mainBodyGeo = new Geometry(&cubePositions, GL_TRIANGLES, false, NULL, NULL);
    Mesh * mainBody = new Mesh(mainBodyGeo , carMat); 
    mesh = mainBody;
    //position = mainBody->getPosition();

    //mainBody->setLocalMatrix(glm::scale(glm::translate(glm::mat4(1.0f),glm::vec3(.0f, 1.0f, .0f)), glm::vec3(1.0f,2.0f,2.0f)));
    //mainBody->add(mainBody);
    mainBody->setPosition(glm::vec3(.0f,2.0f,.0f));
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
    rightFrontWheel->setPosition(glm::vec3(.625f, -0.5f , -1.0f));
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
    //bonnet->setScale(glm::vec3())
    //bonnet->setLocalMatrix(glm::scale(glm::translate(glm::mat4(1.0f), glm::vec3(.0f,.5f,-1.25f)), glm::vec3(1.0f,1.0f,1.0f)));
    mainBody->add(bonnet);

    attachHeadlight();
    attachTailLights();
    //headLight1->position = glm::vec3(.35f,.0f,0.5f);
    //headLight2->position = glm::vec3(-.35f,.0f,0.5f);
}



Mesh* Car::getMesh(){
    return mesh;
}

void Car::moveForward(float speed){
   spinWheels();
   glm::vec3 displacement = speed* orientation->getDirection();
    setPosition(*mesh->getPosition() + displacement);
    //std::cout << glm::to_string(orientation->getDirection()) <<std::endl;

    //headLight1->position += displacement;
    if(attachedCam != NULL){  
        attachedCam->setPosition(attachedCam->getPosition() + displacement);
    }
}

void Car::setPosition(glm::vec3 vec){
    mesh->setPosition(vec);
    updateHeadlightPositions();
    updateTaillightPositions();
}

void Car::rotateFrontWheels(){
    Mesh* leftFrontWheel = mesh->getChildren().data()[2];
    leftFrontWheel->setRotationOrder(YXZ);
    Mesh* rightFrontWheel = mesh->getChildren().data()[3];
    rightFrontWheel->setRotationOrder(YXZ);
    glm::vec3 currentRot1= *leftFrontWheel->getRotation();
    glm::vec3 currentRot2= *rightFrontWheel->getRotation();
    if(currentRot1.y >= 1.0f){
        leftFrontWheel->setRotation(currentRot1 + glm::vec3(.1f,0.0f,.0f));
    }
    else
    {
        leftFrontWheel->setRotation(currentRot1 + glm::vec3(.1f,0.05f,.0f));

    }
    std::cout << currentRot2.y <<std::endl;
    if(currentRot2.y >= 1.0f){
        rightFrontWheel->setRotation(currentRot2 + glm::vec3(.1f,0.0f,.0f));
    }
    else
    {
        rightFrontWheel->setRotation(currentRot2 + glm::vec3(.1f,0.05f,.0f));
    }
    
}

void Car::spinWheels(){

    Mesh* leftFrontWheel = mesh->getChildren().data()[2];
    Mesh* rightFrontWheel = mesh->getChildren().data()[3];
    Mesh* leftBackWheel = mesh->getChildren().data()[0];
    Mesh* rightBackWheel = mesh->getChildren().data()[1];


    glm::vec3 currentRot= *leftFrontWheel->getRotation();

    leftFrontWheel->setRotation(currentRot + glm::vec3(.01f,0.0f,.0f));
    rightFrontWheel->setRotation(currentRot + glm::vec3(.01f,0.0f,.0f));
    leftBackWheel->setRotation(currentRot + glm::vec3(.01f,0.0f,.0f));
    rightBackWheel->setRotation(currentRot + glm::vec3(.01f,0.0f,.0f));
}

void Car::attachCamera(Camera* cam){
    cam->attachToCar(true);
    attachedCam = cam;

    cam->setPosition(*mesh->getPosition() + glm::vec3(.0f,5.0f,.0f));
    cam->setYaw(orientation->getYaw());
    cam->setPitch(orientation->getPitch());
}

void Car::attachHeadlight(){
    Mesh * bonnet = mesh->getChildren().data()[6];
    Mesh * trunk = mesh->getChildren().data()[5];

    headLight1->direction = orientation->direction;
    headLight1->cutOff = glm::radians(15.0f);
    headLight1->outerCutOff = glm::radians(15.0f);

    headLight1->position = glm::vec3(0.f,.0f,-0.45f);
    glm::vec4 pos4 = glm::vec4(headLight1->position.x , headLight1->position.y, headLight1->position.z, 1.0f );
    glm::vec4 newVec = bonnet->getWorldMatrix() * bonnet->getLocalMatrix() * pos4;
    headLight1->position = glm::vec3(newVec.x , newVec.y, newVec.z);
}


void Car::attachTailLights(){
    Mesh * trunk = mesh->getChildren().data()[5];

    //headLight1->direction = -orientation->direction;
    tailLight1->cutOff = glm::radians(15.0f);
    tailLight1->outerCutOff = glm::radians(15.0f);

    tailLight1->position = glm::vec3(0.f,.0f,-0.45f);
    glm::vec4 pos4 = glm::vec4(tailLight1->position.x , tailLight1->position.y, tailLight1->position.z, 1.0f );
    glm::vec4 newVec = trunk->getWorldMatrix() * trunk->getLocalMatrix() * pos4;
    tailLight1->position = glm::vec3(newVec.x , newVec.y, newVec.z);
}

void Car::updateHeadlightPositions(){
    Mesh * bonnet = mesh->getChildren().data()[6];
    headLight1->position = glm::vec3(0.f,.0f,-0.45f);
    glm::vec4 pos4 = glm::vec4(headLight1->position.x , headLight1->position.y, headLight1->position.z, 1.0f );
    glm::vec4 newVec = bonnet->getWorldMatrix() * bonnet->getLocalMatrix() * pos4;
    headLight1->position = glm::vec3(newVec.x , newVec.y, newVec.z);
}


void Car::updateTaillightPositions(){
    Mesh * trunk = mesh->getChildren().data()[5];
    tailLight1->position = glm::vec3(0.f,.0f,0.45f);
    glm::vec4 pos4 = glm::vec4(tailLight1->position.x ,tailLight1->position.y, tailLight1->position.z, 1.0f );
    glm::vec4 newVec = trunk->getWorldMatrix() * trunk->getLocalMatrix() * pos4;
    tailLight1->position = glm::vec3(newVec.x , newVec.y, newVec.z);
}



void Car::setColor(glm::vec3 vec){
    carMat->setColor(vec);
}

void Car::setRotation(float angle){
    mesh->setRotation(glm::vec3(.0f,angle,.0f));
    orientation->direction = glm::rotateY(orientation->direction, angle);
    //orientation->setYaw(angle);
    //orientation->updateOrientation();
    headLight1->direction = -orientation->direction;
    tailLight1->direction = orientation->direction;
    updateTaillightPositions();
    updateHeadlightPositions();

}

void Car::render(Shader* shader){
     if(activeLight == 1){
        headLight1->active= 1;
        headLight1->sendAsSpotlight(shader);
        tailLight1->active = 0;
        tailLight1->sendAsSpotlight(shader);
     }
     else{
        headLight1->active= 0;
        headLight1->sendAsSpotlight(shader);
        tailLight1->active = 1;
        tailLight1->sendAsSpotlight(shader);
     }
     mesh->render(shader);
     std::vector<Mesh *> children = mesh->getChildren();
     for (uint i = 0; i < children.size(); i++)
     {
         children[i]->render(shader);
     }
}
