#pragma once

#include"../Shader/Shader.h"

class Material
{
private:
	glm::vec3 ambient;
	glm::vec3 diffuse ;
	glm::vec3 specular ;
	float shininess;
	glm::vec3 color ;


public:
	Material(
	glm::vec3 ambient = glm::vec3(.1f),
	glm::vec3 diffuse = glm::vec3(1.0f),
	glm::vec3 specular = glm::vec3(.3f),
	float shininess = 1.0,
	glm::vec3 color = glm::vec3(1.0f,1.0f,1.0f)
	)
	{
		this->ambient = ambient;
		this->diffuse = diffuse;
		this->specular = specular;
		this->shininess = shininess;
		this->color = color;
	}

	void setColor(glm::vec3 color){
		this->color = color; 
	}

	glm::vec3 getColor(){
		return color;
	}

	~Material(){}

	//Function
	void sendToShader(Shader*program)
	{
	
		program->setVec3("material.ambient", this->ambient);
		program->setVec3("material.diffuse",this->diffuse);
		program->setVec3("material.specular",this->specular);
		program->setFloat("material.shininess", this->shininess);
		program->setVec3("objectColor", this->color);
	}
};