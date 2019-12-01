//#include <GL/glew.h>
#include <glad/glad.h>
//#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <glm/gtx/string_cast.hpp>
#include <string.h>
#include <algorithm>
#include <stdlib.h>
#include "Geometry/Geometry.hpp" 
#include "Camera/Camera.hpp"
#include "Shader/Shader.h"
#include "3dObjects/Car.h"
#include "Material/Material.hpp"
#include "Mesh/Mesh.hpp"


/*
 * OGL01Shape3D.cpp: 3D Shapes
 */

//#include <GL/glut.h>  // GLUT, include glu.h and gl.h

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

Camera* camera = new Camera();
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

Mesh* createGrid()
{    
        std::vector<float> vertexArray{50.0f,.0f,-50.0f,
        .0f,1.0f,.0f,
        //.0f,1.0f,
        50.0f,.0f,50.0f,
        .0f,1.0f,.0f,
        //1.0f,1.0f,
        -50.0f,.0f,-50.0f,
        .0f,1.0f,.0f,
        //0.0f,.0f,
        50.0f,.0f,50.0f,
        .0f,1.0f,.0f,
        //1.0f,1.0f,
        -50.0f,.0f,50.0f,
        .0f,1.0f,.0f,
        //1.0f,.0f,
        -50.0f,.0f,-50.0f,
        .0f,1.0f,.0f,
        //.0f,.0f
        };
        
        char* path = "grass-texture-1.jpg";
        Geometry* gridGeo = new Geometry(&vertexArray, GL_TRIANGLES, false,NULL, NULL);
        Material* gridMat = new Material();
        gridMat->setColor(glm::vec3(0.2,0.564,0.1));
        Mesh* grid = new Mesh(gridGeo, gridMat);

        //gridGeo->setColor(glm::vec3(.021f,0.77f,.10f));
        return grid;

}


void render(Camera* camera, std::vector<Mesh*>* scene, Shader* shader){
     
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        Mesh* car = scene->data()[1]; 
        
        glm::mat4 *view = camera->getViewMatrix();
        glm::mat4 *proj = camera->getProjectionMatrix();

        shader->setMat4("view", *view);
        shader->setMat4("projection", *proj);
        shader->setVec3("lightPos", glm::vec3(0.0f, 30.0f, 0.0f));
        shader->setVec3("viewPos", camera->getPosition());
        shader->setVec3("lightColor", glm::vec3(1.0f, 1.0f, 204.0f / 255.0f));

        for (int i = 0; i <= scene->size() - 1; i++)
        {
            Mesh *element = scene->data()[i];
            
            element->render(shader);
            std::vector<Mesh*> children = element->getChildren();
            for(uint i=0 ; i < children.size() ; i++){
                children[i]->render(shader);
            }
        }

}


int main(int argc, char*argv[])
{
    
    // Initialize GLFW and OpenGL version
    glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
   // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create Window and rendering context using GLFW, resolution is 800x600
    GLFWwindow* window = glfwCreateWindow(1366,768 , "Comp371 - Lab 01", NULL, NULL);
    if (window == NULL)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
   
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    glfwSetCursorPosCallback(window, mouse_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Black background
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    
    // Compile and link shaders here ...
    Shader * mainShader= new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");
    Shader * lightShader = new Shader("shaders/lightVertex.glsl" , "shaders/lightFragment.glsl");


    //Create vertex array object
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
       

    //SetUp grid and car
    Mesh* grid = createGrid();
    Car * car  = new Car();
    
    std::vector<Mesh*> scene;    
    scene.push_back(grid);
    scene.push_back(car->getMesh());
    

    // Entering Main Loop
    while(!glfwWindowShouldClose(window))
    { 
        //setDepthMap(&scene, lightShader,  depthMapFBO , depthMap);
        
        render(camera, &scene, mainShader);
        
        // Detect inputs
        glfwPollEvents();

        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) && !(glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS))
        {
            float rotationX = camera->getPitch();
            camera->setPitch(rotationX + 0.4f);
        }

        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS) && !(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
        {

            float rotationX = camera->getPitch();
            camera->setPitch(rotationX - 0.4f);
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
        {
            float rotationY = camera->getYaw();
            camera->setYaw(rotationY - 0.4f);
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
        {

            float rotationY = camera->getYaw();
            camera->setYaw(rotationY + 0.4f);
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            glm::vec3 pos = camera->getPosition();
            camera->setPosition(pos - camera->getDirection() * 0.1f);
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            glm::vec3 pos = camera->getPosition();
            camera->setPosition(pos + camera->getDirection() * 0.1f);
        }

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            glm::vec3 currentPos = *car->getMesh()->getPosition();
            car->getMesh()->setPosition(currentPos + glm::vec3(0.0,0.1,0.));
        }

        if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
            glm::vec3 currentRot = *car->getMesh()->getRotation();
            car->getMesh()->setRotation(currentRot + glm::vec3(0.0,0.1,0.));
        }

        if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        {
            camera->setProjectionMatrix(glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 1.0f, 35.0f));
            camera->setViewMatrix(glm::lookAt(glm::vec3(.0f, 30.0f, .0f),
                                              glm::vec3(0.0f, 0.0f, 0.0f),
                                              glm::vec3(0.0f, .0f, 1.0f)));
        }

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        glfwSwapBuffers(window);
 
    }

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
        
        float yaw = camera->getYaw();
        float pitch =  camera->getPitch();
        camera->setYaw(yaw + xoffset);
        camera->setPitch(pitch + yoffset);

}
