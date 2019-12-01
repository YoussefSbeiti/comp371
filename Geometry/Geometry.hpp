#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>
//#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream> 
#include <vector>
#include <string>

class Geometry{
    private: 
   
    std::vector<float> vertices; 
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
    Geometry(std::vector<float>* , GLenum, bool, std::vector<int>* indecies, char*  imagePath);
    Geometry(Geometry * geo);
    ~Geometry();

    void setVbo(GLuint*);
    GLuint* getVbo();

    GLuint* getEbo();

    void setDrawEnum(GLenum);
    GLenum getDrawEnum();

    void setVertices(std::vector<float>*);
    std::vector<float> * getVertices();

    std::vector<int> * getIndecies();

    void setColor(glm::vec3);
    glm::vec3 getColor();

    bool isIndexed();
    bool isTextured();

    GLuint * getTexture();
};

