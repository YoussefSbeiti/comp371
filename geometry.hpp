#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
//#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream> 
#include <vector>
#include <string>

class geometry{
    private: 
   glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3(0.0f);
    glm::vec3 scale = glm::vec3(1.0f,1.0f,1.0f);
    glm::mat4 * matrix = new glm::mat4(1.0f);
    std::vector<float> positions;
    std::vector<float> normals;
    std::vector<int> indecies;

    bool indexed = false;
    bool textured = false;
    GLuint * vbo;
    GLuint * ebo;
    GLuint texture;
    GLenum drawEnum = GL_TRIANGLES;
    glm::vec3 color = glm::vec3(1.0f);


    public:
    bool matAuto = true;
    geometry(std::vector<float>* , GLenum, bool, std::vector<int>* indecies, char*  imagePath);
    geometry(geometry * geo);
    ~geometry();

    void setVbo(GLuint*);
    GLuint* getVbo();


    GLuint* getEbo();

    void setDrawEnum(GLenum);
    GLenum getDrawEnum();

    void setPositions(std::vector<float>*);
    std::vector<float> * getPositions();

    std::vector<int> * getIndecies();

    void setMatrix(glm::mat4);
    glm::mat4* getMatrix();

    void setColor(glm::vec3);
    glm::vec3 getColor();

    bool isIndexed();
     bool isTextured();

    GLuint * getTexture();

    void setScale(glm::vec3);
    glm::vec3 * getScale();
    void setPosition(glm::vec3);
    glm::vec3 * getPosition();
    void setRotation(glm::vec3);
    glm::vec3 * getRotation();
    void updateMatrix();

};

