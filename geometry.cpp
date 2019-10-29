#include "geometry.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


int loadTexture(char* imagepath)
{
  unsigned int texture;
glGenTextures(1, &texture);
glBindTexture(GL_TEXTURE_2D, texture);
// set the texture wrapping/filtering options (on the currently bound texture object)
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load and generate the texture
int width, height, nrChannels;
unsigned char *data = stbi_load(imagepath, &width, &height, &nrChannels, 0);
if (data)
{
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}
else
{
    std::cout << "Failed to load texture" << std::endl;
}
stbi_image_free(data);

return texture;
}

geometry::geometry(std::vector<float>* positions,   GLenum drawEnum, bool indexed, std::vector<int>* indecies = NULL,char* imagePath = NULL){
    
    this->positions = *positions;
    this->indexed = indexed;
    this->drawEnum = drawEnum;

    if(imagePath != NULL){
        std::cout <<  "textured" << std::endl;
        this->textured = true; 
        this->texture = loadTexture(imagePath);
    }

    if(indexed){
        this->indecies = *indecies;
        ebo = new GLuint();
        glGenBuffers(1, ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER , *ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indecies->size()* sizeof(indecies),
        indecies->data(),
        GL_STATIC_DRAW); 
    }
    
    

    vbo = new GLuint();
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        positions->size() * sizeof(positions),
        positions->data(),
        GL_STATIC_DRAW
    );

}

geometry::geometry(geometry* geo){
    this->drawEnum = geo->getDrawEnum();
    this->vbo = geo->getVbo();
    this->positions = *geo->getPositions();
    this->indexed = geo->isIndexed();
    if(indexed){
        this->ebo = geo->getVbo();
        this->indecies = *geo->getIndecies();
    }
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


std::vector<int>* geometry::getIndecies(){
    return &indecies;
}

void geometry::setMatrix(glm::mat4 matrix){
    *this->matrix = matrix;
}

glm::mat4* geometry::getMatrix(){
    return matrix;
}

void geometry::setColor(glm::vec3 vec){
    color = vec;
}

glm::vec3 geometry::getColor(){
    return color;
}

bool geometry::isIndexed(){
    return indexed;
}


bool geometry::isTextured(){
    return textured;
}

GLuint* geometry::getEbo(){
    return ebo;
}

GLuint * geometry::getTexture(){
    return &texture;
}


void geometry::setScale(glm::vec3 vec){
   scale = vec;
   updateMatrix();
}

glm::vec3 * geometry::getScale(){
    return &scale;
}

void geometry::setPosition(glm::vec3 vec){
    position = vec;
    updateMatrix();
}

glm::vec3 * geometry::getPosition(){
    return &position;
}

void geometry::setRotation(glm::vec3 vec){
    rotation = vec;
    updateMatrix();
}

glm::vec3* geometry::getRotation(){
    return &rotation;
}

void geometry::updateMatrix(){
  //  if(matAuto){
        glm::mat4 translateMat = glm::translate(glm::mat4(1.0f) , position);
        glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f) , scale);
        glm::mat4 rotateX = glm::rotate(glm::mat4(1.0f) , rotation.x, glm::vec3(1.0f,.0f,.0f));
        glm::mat4 rotateY = glm::rotate(glm::mat4(1.0f) , rotation.y, glm::vec3(.0f,1.0f,.0f) );
        glm::mat4 rotateZ = glm::rotate(glm::mat4(1.0f) , rotation.z, glm::vec3(.0f,.0f,1.0f));
        *matrix = translateMat * rotateX  * rotateY * rotateZ * scaleMat;
//    }
}


