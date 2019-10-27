#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glu.h>
#include <iostream> 
#include <vector>
#include <string>

class geometry{
    private: 
    glm::mat4* matrix = new glm::mat4(1.0f);
    std::vector<float> positions;
    GLuint * vbo;
    GLenum drawEnum = GL_TRIANGLES;

    public:
    geometry(std::vector<float>* ,GLenum);
    geometry(GLuint*, GLenum);
    ~geometry();

    void setVbo(GLuint*);
    GLuint* getVbo();

    void setDrawEnum(GLenum);
    GLenum getDrawEnum();

    void setPositions(std::vector<float>*);
    std::vector<float> * getPositions();

    void setMatrix(glm::mat4);
    glm::mat4* getMatrix();
};

