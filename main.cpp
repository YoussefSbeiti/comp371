#include <GL/glew.h>
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <glm/gtx/string_cast.hpp>
#include "geometry.hpp"
#include <string.h>
#include "Camera.hpp"
/*
 * OGL01Shape3D.cpp: 3D Shapes
 */

#include <GL/glut.h>  // GLUT, include glu.h and gl.h

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

Camera* camera = new Camera();
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


const char* getVertexShaderSource()
{
    // Insert Shaders here ...
    // For now, you use a string for your shader code, in the assignment, shaders will be stored in .glsl files
                return 
                "#version 330 core\n"
                "layout (location = 0) in vec3 aPos;"
                "layout (location = 1) in vec3 aColor;"
                " out vec3 vertexColor;"
                //"uniform mat4 worldMatrix = mat4(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, .5, 0.0, 0.0, 0.0, .0, 1.0);"
                "uniform mat4 modelMatrix = mat4(1.0);"
                "uniform mat4 viewMatrix = mat4(1.0);"
                "uniform mat4 projectionMatrix = mat4(1.0);"
                ""
                ""
                "void main()"
                "{"
                "mat4 modelViewProjection = projectionMatrix * viewMatrix * modelMatrix;"
                "gl_Position = modelViewProjection* vec4(aPos.x, aPos.y, aPos.z, 1.0f);"
                "vertexColor = aColor;"
                "}";
}

const char* getFragmentShaderSource()
{
    return
    "#version 330 core\n"
    "in vec3 vertexColor;"
    "out vec4 FragColor;"
    "void main()"
    "{"
    "   FragColor = vec4(vertexColor.x, vertexColor.y, vertexColor.z, 1.0f) ;"
    "}";
}

int compileAndLinkShaders()
{
    // compile and link shader program
    // return shader program id
    // ------------------------------------


    // vertex shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderSource = getVertexShaderSource();
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // fragment shader
    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSource = getFragmentShaderSource();
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // link shaders
    int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    return shaderProgram;
}

geometry* createVBO(std::string type)
{    
     if(type == "grid"){
        std::vector<float> vertexArray;
        
        for(int x = -50; x<=50 ; x++){    
                vertexArray.push_back(float(x));
                vertexArray.push_back(0.0f);
                vertexArray.push_back(50.0f);
                vertexArray.push_back(1.0f);
                vertexArray.push_back(1.0f);
                vertexArray.push_back(1.0f);
                vertexArray.push_back(float(x));
                vertexArray.push_back(0.0f);               
                vertexArray.push_back(-50.0f);
                vertexArray.push_back(1.0f);
                vertexArray.push_back(1.0f);
                vertexArray.push_back(1.0f);
                
        }

        for(int x = -50; x<=50 ; x++){    
                vertexArray.push_back(50.0f); 
                vertexArray.push_back(0.0f);
                vertexArray.push_back(float(x));
                vertexArray.push_back(1.0f);
                vertexArray.push_back(1.0f);
                vertexArray.push_back(1.0f);
                vertexArray.push_back(-50.0f);
                vertexArray.push_back(0.0f);
                vertexArray.push_back(float(x));
                vertexArray.push_back(1.0f);
                vertexArray.push_back(1.0f);
                vertexArray.push_back(1.0f);
        }

        geometry* gridGeo = new geometry(&vertexArray, GL_LINES);
        return gridGeo;

    }

    if(type == "cube"){
        std::vector<float> vertexArr{
            1.0f,-1.0f,-1.0f, // triangle 1 : begin
            1.0f,0.0f,0.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,0.0f,0.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f,
           1.0f,0.0f,0.0f,  // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,0.0f,0.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            1.0f,-1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            1.0f,-1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            1.0f,-1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            1.0f,-1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            1.0f,-1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            1.0f,-1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            1.0f,-1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,0.0f,0.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,0.0f,0.0f,
            1.0f,-.5f, 1.0f,
            1.0f,0.0f,0.0f
        };

        geometry* cubeGeo = new geometry(&vertexArr , GL_TRIANGLES);

        return cubeGeo;

    }
}

void render(Camera* camera, std::vector<geometry*>* scene, int* shaderProgram, GLFWwindow* window, GLuint* modelMatrixLocation, GLuint* viewMatrixLocation, GLuint* projectionMatrixLocation){
    

        // Entering Main Loop
    while(!glfwWindowShouldClose(window))
    {
         // Each frame, reset color of each pixel to glClearColor
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(*shaderProgram);

        //glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &perspectiveMatrix[0][0]);

        for (int i = 0; i <= scene->size() - 1; i++)
        {

            geometry *element = scene->data()[i];
            glm::mat4 *matrix = element->getMatrix();
            glUniformMatrix4fv(*modelMatrixLocation, 1, GL_FALSE, &(*matrix)[0][0]);
            glUniformMatrix4fv(*viewMatrixLocation, 1, GL_FALSE, &(*camera->getViewMatrix())[0][0]);
            glUniformMatrix4fv(*projectionMatrixLocation, 1, GL_FALSE, &(*camera->getProjectionMatrix())[0][0]);
            glBindBuffer(GL_ARRAY_BUFFER, *element->getVbo());
            glVertexAttribPointer(0,        // attribute 0 matches aPos in Vertex Shader
                                  3,        // size
                                  GL_FLOAT, // type
                                  GL_FALSE, // normalized?
                                  6*sizeof(float),        // stride - each vertex contain 2 vec3 (position, color)
                                  (void *)0 // array buffer offset
            );
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1,        // attribute 0 matches aPos in Vertex Shader
                                  3,        // size
                                  GL_FLOAT, // type
                                  GL_FALSE, // normalized?
                                  6*sizeof(float),        // stride - each vertex contain 2 vec3 (position, color)
                                  (void *)(3*sizeof(float))// array buffer offset
            );
            glEnableVertexAttribArray(1);

            glDrawArrays(element->getDrawEnum(), 0, element->getPositions()->size() / 6);
        }

        // Detect inputs
        glfwPollEvents();
        
        

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) &&!(glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)) 
        {   
            glm::vec3 pos = camera->getPosition();
            camera->setPosition(pos+glm::vec3(0.0f,0.1f,0.0f));
        }
        
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)  &&!(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) ) 
        {   
             glm::vec3 pos = camera->getPosition();
             camera->setPosition(pos+glm::vec3(0.0f,-0.1f,0.0f));
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS &&!(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)) 
        {   
            glm::vec3 pos = camera->getPosition();
            camera->setPosition(pos+glm::vec3(-0.1f,0.0f,0.0f));
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS &&!(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
        {   
            glm::vec3 pos = camera->getPosition();
            camera->setPosition(pos+glm::vec3(0.1f,0.0f,0.0f));
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) 
        {   
           glm::vec3 pos = camera->getPosition();
            camera->setPosition(pos+glm::vec3(0.0f,0.0f,-0.1f));
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) 
        {   
            glm::vec3 pos = camera->getPosition();
            camera->setPosition(pos+glm::vec3(0.0f,0.0f,0.1f));
        }
        if(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {           
            float rotationX = camera->getPitch();
            camera->setPitch(rotationX + 0.4f);
        }
        
        if(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {           
            float rotationX = camera->getPitch();
            camera->setPitch(rotationX - 0.4f);
        }
        
        if(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {                                
            float rotationY = camera->getYaw();
            camera->setYaw(rotationY + 0.4f);

        }

        if(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {           
            float rotationY = camera->getYaw();
            camera->setYaw(rotationY - 0.4f);
        }
        // End frame
        glfwSwapBuffers(window);
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

        
}


int main(int argc, char*argv[])
{
    // Initialize GLFW and OpenGL version
    glfwInit();

#if defined(PLATFORM_OSX)	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#else
	// On windows, we set OpenGL version to 2.1, to support more hardware
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
   // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    // Create Window and rendering context using GLFW, resolution is 800x600
    GLFWwindow* window = glfwCreateWindow(1366,768 , "Comp371 - Lab 01", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to create GLEW" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetCursorPosCallback(window, mouse_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    
    // Compile and link shaders here ...
    int shaderProgram = compileAndLinkShaders();

    //Create vertex array object
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
    
    //SetUp car geometry
    geometry* mainBody = createVBO("cube");
    mainBody->setMatrix(glm::scale(glm::mat4(1.0f),glm::vec3(1.0f, 2.0f, 3.0f)));
    geometry* leftBackWheel = new geometry(mainBody->getVbo(), GL_TRIANGLES);
    geometry* rightBackWheel = new geometry(mainBody->getVbo(), GL_TRIANGLES);
    geometry* leftFrontWheel = new geometry(mainBody->getVbo(), GL_TRIANGLES);
    geometry* rightFrontlefWheel = new geometry(mainBody->getVbo(), GL_TRIANGLES);
    geometry*  roof = new geometry(mainBody->getVbo(), GL_TRIANGLES);
    roof->setMatrix(glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f,1.0f,2.0f)), glm::vec3(.0f,3.5f,0.0f)));
    roof->setPositions(mainBody->getPositions());
    geometry* trunk= new geometry(mainBody->getVbo(), GL_TRIANGLES);
    trunk->setMatrix(glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f,1.0f,2.0f)), glm::vec3(.0f,.0f,-2.25f)));
    trunk->setPositions(mainBody->getPositions());
    geometry* bonnet = new geometry(mainBody->getVbo(), GL_TRIANGLES);
    bonnet->setMatrix(glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f,1.0f,2.0f)), glm::vec3(.0f,.0f,2.25f)));
    bonnet->setPositions(mainBody->getPositions());

    //SetUp grid geometry
    geometry* gridGeo = createVBO("grid");

    //Put all cars parts in one vector for applying transformation on whole car
    std::vector<geometry*> car;
    car.push_back(trunk);
    car.push_back(bonnet);
    car.push_back(mainBody);
    car.push_back(roof);
    car.push_back(leftBackWheel);
    car.push_back(rightBackWheel);
    car.push_back(leftFrontWheel);
    car.push_back(rightFrontlefWheel);

    //SetUp axis
    //float();

    std::vector<geometry*> scene;
    scene.push_back(gridGeo);
    scene.push_back(mainBody);
    scene.push_back(bonnet);
    scene.push_back(trunk);
    scene.push_back(roof);
    
    GLuint modelMatrixLocation = glGetUniformLocation(shaderProgram, "modelMatrix");
    GLuint viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
    GLuint projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
       
    render(camera, &scene, &shaderProgram, window, &modelMatrixLocation, &viewMatrixLocation, &projectionMatrixLocation);
    
    // Shutdown GLFW
    glfwTerminate();
    
	return 0;
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }


        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        xoffset *= 0.1;
        yoffset *= 0.1;

        camera->setYaw(camera->getYaw() + xoffset);
        camera->setPitch(camera->getPitch() + xoffset);

}
