#include "Light.hpp"

Light::Light()
{
	
}

float	Light::getIntensity()
{
	return (this->intensity);
}

glm::vec3 Light::getPosition(){
    return position;
}

glm::vec3 Light::getDirection(){
    return direction;
}

glm::vec3 Light::getColor(){
    return color;
}

void	Light::setPosition(glm::vec3 pos)
{
	this->position = pos;
}

void    Light::setDirection(glm::vec3 rot)
{
	this->direction = rot;
}

void	Light::setColor(glm::vec3 col)
{
	this->color = col;
}

void	Light::setIntensity(float intensity)
{
	this->intensity = intensity;
}

void sendToShader(Shader* Shader){
	//shader->set
}