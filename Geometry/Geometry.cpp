#include "Geometry.hpp"
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

Geometry::Geometry(std::vector<float>* vertices,   GLenum drawEnum, bool indexed, std::vector<int>* indecies = NULL,char* imagePath = NULL){
    
    this->vertices = *vertices;
    this->indexed = indexed;
    this->drawEnum = drawEnum;

    if(imagePath != NULL){
        std::cout <<  "textured" << std::endl;
        this->textured = true; 
        this->texture = loadTexture(imagePath);
    }

    if(indexed){
        std::cout <<  "indexed" << std::endl;
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
        vertices->size() * sizeof(vertices),
        vertices->data(),
        GL_STATIC_DRAW
    );
}

Geometry::Geometry(Geometry* geo){
    this->drawEnum = geo->getDrawEnum();
    this->vbo = geo->getVbo();
    this->vertices = *geo->getVertices();
    this->indexed = geo->isIndexed();
    if(indexed){
        this->ebo = geo->getVbo();
        this->indecies = *geo->getIndecies();
    }
}

Geometry::~Geometry(){
    delete vbo;
    //delete matrix;
    vbo = NULL;
    //matrix = NULL;
}

void Geometry::setVbo(GLuint* vbo){
    this->vbo = vbo;
}

GLuint* Geometry::getVbo(){
    return vbo;
}

void Geometry::setDrawEnum(GLenum drawEnum){
        this->drawEnum = drawEnum;
}

GLenum Geometry::getDrawEnum(){
    return drawEnum;
}

void Geometry::setVertices(std::vector<float> * vertices){
    this->vertices = *vertices;
}

std::vector<float>* Geometry::getVertices(){
    return &vertices;
}


std::vector<int>* Geometry::getIndecies(){
    return &indecies;
}

bool Geometry::isIndexed(){
    return indexed;
}


bool Geometry::isTextured(){
    return textured;
}

GLuint* Geometry::getEbo(){
    return ebo;
}

GLuint * Geometry::getTexture(){
    return &texture;
}




