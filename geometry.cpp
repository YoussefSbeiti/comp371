#include "geometry.hpp"

geometry::geometry(std::vector<float>* positions, GLenum drawEnum){
    
    this->positions = *positions;
    this->drawEnum = drawEnum;
    vbo = new GLuint();
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        positions->size() * sizeof(positions),
        positions->data(),
        GL_STATIC_DRAW
    );

    this->vbo = vbo;
}

geometry::geometry(GLuint*vbo, GLenum drawEnum){
    this->drawEnum = drawEnum;
    this->vbo = vbo;
}

geometry::~geometry(){
    delete vbo;
    delete matrix;
    vbo = NULL;
    matrix = NULL;
}

void geometry::setVbo(GLuint* vbo){
    this->vbo = vbo;
}

GLuint* geometry::getVbo(){
    return vbo;
}

void geometry::setDrawEnum(GLenum drawEnum){
        this->drawEnum = drawEnum;
}

GLenum geometry::getDrawEnum(){
    return drawEnum;
}

void geometry::setPositions(std::vector<float> * positions){
    this->positions = *positions;
}

std::vector<float>* geometry::getPositions(){
    return &positions;
}

void geometry::setMatrix(glm::mat4 matrix){
    *this->matrix = matrix;
}

glm::mat4* geometry::getMatrix(){
    return matrix;
}