#include <glm/glm.hpp>
#include <vector>
#include <glad/glad.h>
#include "../Shader/Shader.h"
#include "../Mesh/Mesh.hpp"

class Particle{
    private:
    float size = 0.01f;
    std::vector<float> vertices {
    -size,size,.0f,//top left
    -size,-size,.0f,// bottom left
    size,-size,.0f,//bottom right
    size,-size,.0f,//bottom right
    size,size,.0f,//top right
    -size,size,.0f//top left
    };    
    glm::vec3 color = glm::vec3(1.0f,.10f,1.0f);
    GLuint* vbo;
    Shader* shader = new Shader("Particle System/shaders/vertex.glsl" , "Particle System/shaders/fragment1.glsl");
    Mesh* mesh;
    

    public:
    Particle();
    void render();
    void setSize(float);
};

Particle::Particle(){

    vbo = new GLuint();
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(vertices),
        vertices.data(),
        GL_STATIC_DRAW
    );
}

void Particle::render(){
    shader->use();
    shader->setVec3("smokeColor" , color);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
            glVertexAttribPointer(0,                 // attribute 0 matches aPos in Vertex Shader
                                  3,                 // size
                                  GL_FLOAT,          // type
                                  GL_FALSE,          // normalized?
                                  3*sizeof(float), // stride - each vertex contain 2 vec3 (position, color)
                                  (void *)0          // array buffer offset
            );
            glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

