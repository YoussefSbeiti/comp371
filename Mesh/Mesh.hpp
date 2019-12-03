#pragma once
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream> 
#include <vector>
#include <string>
#include "../Geometry/Geometry.hpp"
#include "../Material/Material.hpp"
//#include "Orientation.hpp"

enum rotationOrder{XYZ , XZY, YXZ, YZX, ZYX , ZXY};

class Mesh{

    private:
    Geometry * geometry;
    Material* material;
    
    
    rotationOrder rotOrder;
    

    std::vector<Mesh*> children;
    Mesh* parent;

    glm::vec3 *position = new glm::vec3(0.0f);
    glm::vec3 *rotation = new glm::vec3(0.0f);
    glm::vec3 *scale = new glm::vec3(1.0f,1.0f,1.0f);
    glm::mat4 localMatrix = glm::mat4(1.0f);
    glm::mat4 worldMatrix = glm::mat4(1.0f);
    
    public:
    //Orientation* orientation;

    
    Mesh(Geometry*  , Material*);
    
    void addToScene(std::vector<Mesh*> *);

    void setParent(Mesh*);
    Mesh* getParent();

    void setScale(glm::vec3);
    glm::vec3 * getScale();
    
    void setPosition(glm::vec3);
    glm::vec3 * getPosition();
    
    void setRotation(glm::vec3);
    glm::vec3 *  getRotation();

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);

    void setRotationOrder(rotationOrder);
    
    glm::mat4 getLocalMatrix();
    void setLocalMatrix(glm::mat4);
    glm::mat4 getWorldMatrix();
    void setWorldMatrix(glm::mat4);
    std::vector<Mesh*> getChildren();

    void add(Mesh*);

    void updateMatrix();

    void render(Shader*);

    Geometry* getGeometry();
    Material* getMaterial();
};
