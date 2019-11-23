//#include <GL/glew.h>
#include <glad/glad.h>
//#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <glm/gtx/string_cast.hpp>

#ifndef GEOMETRY
#define GEOMETRY
#include "geometry.hpp"
#endif

#include <string.h>
#include "Camera.hpp"
#include "shader.h"
#include "Car.h"
#include <algorithm>
#include <stdlib.h> 

/*
 * OGL01Shape3D.cpp: 3D Shapes
 */

//#include <GL/glut.h>  // GLUT, include glu.h and gl.h

void mouse_callback(GLFWwindow* window, double xpos, double ypos);

// settings
const unsigned int SCR_WIDTH = 1366;
const unsigned int SCR_HEIGHT = 768;

Car* car;
geometry* gridGeo;

Camera* camera = new Camera();
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

geometry* createGrid()
{    
        std::vector<float> vertexArray{50.0f,.0f,-50.0f,
        .0f,1.0f,.0f,
        .0f,1.0f,
        50.0f,.0f,50.0f,
        .0f,1.0f,.0f,
        1.0f,1.0f,
        -50.0f,.0f,-50.0f,
        .0f,1.0f,.0f,
        0.0f,.0f,
        50.0f,.0f,50.0f,
        .0f,1.0f,.0f,
        1.0f,1.0f,
        -50.0f,.0f,50.0f,
        .0f,1.0f,.0f,
        1.0f,.0f,
        -50.0f,.0f,-50.0f,
        .0f,1.0f,.0f,
        .0f,.0f
        };
        
        
        /*
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
        }*/

        char* path = "grass-texture-1.jpg";
        geometry* gridGeo = new geometry(&vertexArray, GL_TRIANGLES, false,NULL, path);
        gridGeo->setColor(glm::vec3(.021f,0.77f,.10f));
        return gridGeo;


}


/*
void rotateWheelX(){
    geometry * wheel1 = car->getChildren()[1];
            geometry * wheel2 = car->getChildren()[2];
            glm::mat4 *matWheel1 = wheel1->getMatrix(); 
            glm::mat4 *matWheel2 = wheel2->getMatrix();
            glm::vec3 currentRotation = *wheel1->getRotation();
            float rot = wheel1->getRotation()->x;
            wheel1->matAuto = false;
            wheel2->matAuto = false;
            
            glm::vec3 axis =  glm::cross(glm::vec3(glm::sin(currentRotation.y) , 0.0f , glm::cos(currentRotation.y)), glm::vec3(0.0f,1.0f,0.0f));
            std::cout<<glm::to_string(axis) << std::endl;
            *wheel1->getMatrix() = glm::rotate(*wheel1->getMatrix()  , 0.01f, axis);
            *wheel2->getMatrix() = glm::rotate(*wheel2->getMatrix() , 0.01f,axis);
            wheel1->getRotation()->x = rot + 0.01;



}
*/
/*
void rotateWheelY(){
     geometry * wheel1 = car->getChildren()[1];
            geometry * wheel2 = car->getChildren()[2];
            glm::mat4 *matWheel1 = wheel1->getMatrix(); 
            glm::mat4 *matWheel2 = wheel2->getMatrix();
            wheel1->matAuto = false;
            wheel2->matAuto = false;
            glm::vec3 rot1 = *car->getChildren()[1]->getRotation();
            glm::vec3 axis =  glm::cross(glm::vec3(glm::sin(curren.y) , 0.0f , glm::cos(currentRotation.y)), glm::vec3(0.0f,1.0f,0.0f))
            *wheel1->getMatrix() = glm::rotate(*matWheel1 , 0.01f  , glm::vec3(0.0f,1.0f,0.0f));
            *wheel2->getMatrix() = glm::rotate(*matWheel2 , 0.01f  , glm::vec3(0.0f,1.0f,0.0f));
            wheel1->setRotation(rot1 + glm::vec3(0.0f,0.01f,0.0f));
}*/

void render(Camera* camera, std::vector<geometry*>* scene, Shader* shader, GLFWwindow* window){
    

        // Entering Main Loop
    while(!glfwWindowShouldClose(window))
    {   
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->use();
        //glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, &perspectiveMatrix[0][0]);

        for (int i = 0; i <= scene->size() - 1; i++)
        {

            geometry *element = scene->data()[i];
            glm::mat4 *model = element->getMatrix();
            glm::mat4 *view = camera->getViewMatrix();
            glm::mat4 *proj = camera->getProjectionMatrix();
            shader->setMat4("model", *model);
            shader->setMat4("view", *view);
            shader->setMat4("projection", *proj);
            shader->setVec3("lightPos" , glm::vec3(0.0f,30.0f,0.0f));
            shader->setVec3("viewPos" , camera->getPosition());
            shader->setVec3("lightColor", glm::vec3(1.0f,1.0f,204.0f/255.0f));
            shader->setVec3("objectColor" , element->getColor());
            shader->setBool("isTextured", element->isTextured());
            
            if(element->isTextured()){
                

                glBindBuffer(GL_ARRAY_BUFFER, *element->getVbo());
                glVertexAttribPointer(0,        // attribute 0 matches aPos in Vertex Shader
                                    3,        // size
                                    GL_FLOAT, // type
                                    GL_FALSE, // normalized?
                                    8*sizeof(float),        // stride - each vertex contain 2 vec3 (position, color)
                                    (void *)0 // array buffer offset
                );
                glEnableVertexAttribArray(0);

                glVertexAttribPointer(1,        // attribute 0 matches aPos in Vertex Shader
                                    3,        // size
                                    GL_FLOAT, // type
                                    GL_FALSE, // normalized?
                                    8*sizeof(float),        // stride - each vertex contain 2 vec3 (position, color)
                                    (void *)(3*sizeof(float))// array buffer offset
                );
                glEnableVertexAttribArray(1);

                glBindTexture(GL_TEXTURE_2D, *element->getTexture());

                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
                glEnableVertexAttribArray(2);  

                
                if(element->isIndexed()){
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *element->getEbo());  
                    glDrawElements(element->getDrawEnum(), element->getIndecies()->size() , GL_UNSIGNED_INT, 0);
                }
                else{
                    glDrawArrays(element->getDrawEnum(), 0, element->getPositions()->size() / 8);
                }
            }
            else{
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

                
                if(element->isIndexed()){
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *element->getEbo());  
                    glDrawElements(element->getDrawEnum(), element->getIndecies()->size() , GL_UNSIGNED_INT, 0);
                }
                else{
                    glDrawArrays(element->getDrawEnum(), 0, element->getPositions()->size() / 6);
                }
            }

        }

        // Detect inputs
        glfwPollEvents();
        
        
        /*
         *Listen for input from keyboard  
         */
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) &&!(glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)) 
        {   
            float rotationX = camera->getPitch();
            camera->setPitch(rotationX + 0.4f);
        }
        
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS && !(glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS)  &&!(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) ) 
        {   
                      
            float rotationX = camera->getPitch();
            camera->setPitch(rotationX - 0.4f);
        }

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS &&!(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS)) 
        {   
             float rotationY = camera->getYaw();
            camera->setYaw(rotationY - 0.4f);
        }

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS &&!(glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS))
        {   
                                         
            float rotationY = camera->getYaw();
            camera->setYaw(rotationY + 0.4f);
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) 
        {   
           glm::vec3 pos = camera->getPosition();
            camera->setPosition(pos-camera->getDirection() *0.1f);
        }
        if (glfwGetKey(window, GLFW_KEY_RIGHT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) 
        {   
            glm::vec3 pos = camera->getPosition();
            camera->setPosition(pos+ camera->getDirection() *0.1f) ;
        }
    

        if(glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS )
        {   
            
            std::vector<geometry*>  children = car->getChildren();
            for(int i=0; i<children.size() ; i++){
                children[i]->setDrawEnum(GL_POINTS);
           
            //gridGeo->setDrawEnum(GL_TRIANGLES);
            }
            //glm::mat4 * wheelMat = car->getChildren()[1]->getMatrix();
            //glm::rotate(*wheelMat , glm::radians(45))
            //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
        } 
        // End frame
        glfwSwapBuffers(window);
        
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }

        
}


//std::vector<float> cylinderPositions {0,0.5,1,0,0,1,0.7071067690849304,0.5,0.7071067690849304,0.7071067690849304,0,0.7071067690849304,1,0.5,0,1,0,0,0.7071067690849304,0.5,-0.7071067690849304,0.7071067690849304,0,-0.7071067690849304,0,0.5,-1,0,0,-1,-0.7071067690849304,0.5,-0.7071067690849304,-0.7071067690849304,0,-0.7071067690849304,-1,0.5,-0,-1,0,-0,-0.7071067690849304,0.5,0.7071067690849304,-0.7071067690849304,0,0.7071067690849304,-0,0.5,1,-0,0,1,0,-0.5,1,0,0,1,0.7071067690849304,-0.5,0.7071067690849304,0.7071067690849304,0,0.7071067690849304,1,-0.5,0,1,0,0,0.7071067690849304,-0.5,-0.7071067690849304,0.7071067690849304,0,-0.7071067690849304,0,-0.5,-1,0,0,-1,-0.7071067690849304,-0.5,-0.7071067690849304,-0.7071067690849304,0,-0.7071067690849304,-1,-0.5,-0,-1,0,-0,-0.7071067690849304,-0.5,0.7071067690849304,-0.7071067690849304,0,0.7071067690849304,-0,-0.5,1,-0,0,1,0,0.5,0,0,1,0,0,0.5,0,0,1,0,0,0.5,0,0,1,0,0,0.5,0,0,1,0,0,0.5,0,0,1,0,0,0.5,0,0,1,0,0,0.5,0,0,1,0,0,0.5,0,0,1,0,0,0.5,1,0,1,0,0.7071067690849304,0.5,0.7071067690849304,0,1,0,1,0.5,0,0,1,0,0.7071067690849304,0.5,-0.7071067690849304,0,1,0,0,0.5,-1,0,1,0,-0.7071067690849304,0.5,-0.7071067690849304,0,1,0,-1,0.5,-0,0,1,0,-0.7071067690849304,0.5,0.7071067690849304,0,1,0,-0,0.5,1,0,1,0,0,-0.5,0,0,-1,0,0,-0.5,0,0,-1,0,0,-0.5,0,0,-1,0,0,-0.5,0,0,-1,0,0,-0.5,0,0,-1,0,0,-0.5,0,0,-1,0,0,-0.5,0,0,-1,0,0,-0.5,0,0,-1,0,0,-0.5,1,0,-1,0,0.7071067690849304,-0.5,0.7071067690849304,0,-1,0,1,-0.5,0,0,-1,0,0.7071067690849304,-0.5,-0.7071067690849304,0,-1,0,0,-0.5,-1,0,-1,0,-0.7071067690849304,-0.5,-0.7071067690849304,0,-1,0,-1,-0.5,-0,0,-1,0,-0.7071067690849304,-0.5,0.7071067690849304,0,-1,0,-0,-0.5,1,0,-1,0};
//std::vector<int> cylinderIndecies {0,9,1,9,10,1,1,10,2,10,11,2,2,11,3,11,12,3,3,12,4,12,13,4,4,13,5,13,14,5,5,14,6,14,15,6,6,15,7,15,16,7,7,16,8,16,17,8,26,27,18,27,28,19,28,29,20,29,30,21,30,31,22,31,32,23,32,33,24,33,34,25,44,43,35,45,44,36,46,45,37,47,46,38,48,47,39,49,48,40,50,49,41,51,50,42};
//std::vector<float> cylinderPositions {0,0.5,1,0.7071067690849304,0.5,0.7071067690849304,1,0.5,6.123234262925839,0.7071067690849304,0.5,-0.7071067690849304,1.2246468525851679,0.5,-1,-0.7071067690849304,0.5,-0.7071067690849304,-1,0.5,-1.8369701465288538,-0.7071067690849304,0.5,0.7071067690849304,-2.4492937051703357 ,0.5,1,0,-0.5,1,0.7071067690849304,-0.5,0.7071067690849304,1,-0.5,6.123234262925839,0.7071067690849304,-0.5,-0.7071067690849304,0,-0.5,-1,-0.7071067690849304,-0.5,-0.7071067690849304,-1,-0.5,-0,-0.7071067690849304,-0.5,0.7071067690849304,-0,-0.5,1,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,0,0,0.5,1,0.7071067690849304,0.5,0.7071067690849304,1,0.5,6.123234262925839,0.7071067690849304,0.5,-0.7071067690849304,0,0.5,-1,-0.7071067690849304,0.5,-0.7071067690849304,-1,0.5,-0,-0.7071067690849304,0.5,0.7071067690849304,-0,0.5,1,0,-0.5,0,0,-0.5,0,0,-0.5,0,0,-0.5,0,0,-0.5,0,0,-0.5,0,0,-0.5,0,0,-0.5,0,0,-0.5,1,0.7071067690849304,-0.5,0.7071067690849304,1,-0.5,6.123234262925839,0.7071067690849304,-0.5,-0.7071067690849304,0,-0.5,-1,-0.7071067690849304,-0.5,-0.7071067690849304,-1,-0.5,-0,-0.7071067690849304,-0.5,0.7071067690849304,-0,-0.5,1};

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
    Shader * shaderProgram = new Shader("shaders/vertex.glsl", "shaders/fragment.glsl");


    //Create vertex array object
    GLuint vertexArrayObject;
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);
       

    //SetUp grid and car
    gridGeo = createGrid();
    car  = new Car();
    //car->setPosition(*car->getPosition() + glm::vec3(0.0f,0.40f,0.0f));
    
    std::vector<geometry*> scene;    
    scene.push_back(gridGeo);
    car->addToScene(&scene);
           
    render(camera, &scene, shaderProgram, window);
    
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
