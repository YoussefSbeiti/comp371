#include "Orientation.hpp"
/*
Orientation::Orientation(){
    up = glm::vec3(.0f,1.0f,.0f);
    right = glm::vec3(1.0f,.0f,.0f);
    direction = glm::vec3(.0f,.0f,1.0f);

}


void	Orientation::setRoll(float angle)
{
	this->roll = angle;
	this->right = glm::rotate(glm::vec3(1.0f,.0f,.0f), angle, glm::vec3(.0f,.0f,1.0f));
    this->up = glm::rotate(this->up , angle, this->direction);
}

float	Orientation::getRoll()
{
	return roll;
}

void	Orientation::setPitch(float angle)
{
	this->pitch = angle;
	this->direction = glm::rotate(this->direction, angle, this->right);
    this->up = glm::rotate(this->up, angle, this->right);
}

float	Orientation::getPitch()
{
	return pitch;
}

void	Orientation::setYaw(float angle)
{
	this->yaw =  angle;
	this->direction = glm::rotate(glm::vec3(.0f,.0f,1.0f), angle, glm::vec3(.0f,1.0f,.0f));
    this->right = glm::rotate(glm::vec3(1.0f,.0f,.0f) , angle, glm::vec3(.0f,1.0f,.0f));
}

float	Orientation::getYaw()
{
	return yaw;
}


glm::vec3 Orientation::getDirection(){
    return direction;
}

void Orientation::setDirection(glm::vec3 direction){
    this->direction = direction; 
}


glm::vec3 Orientation::getRight(){
    return right;
}

void Orientation::setRight(glm::vec3 right){
    this->right = right; 
}

glm::vec3 Orientation::getUp(){
    return up;
}

void Orientation::setUp(glm::vec3 up){
    this->up = up; 
}

void Orientation::updateDirection(){
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
}

void Orientation::updateOrientation(){
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction.y = sin(glm::radians(pitch));
	direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	direction = glm::normalize(direction);


	// Also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(direction, glm::vec3(.0f,1.0f,0.0f))); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, direction));
}*/


Orientation::Orientation(/* args */)
{
	up = glm::vec3(.0f,1.0f,.0f);
    right = glm::vec3(1.0f,.0f,.0f);
    direction = glm::vec3(.0f,.0f,1.0f);
	//updateOrientation();
}


void	Orientation::setRoll(float angle)
{
	this->roll = angle;
	updateOrientation();
}

float	Orientation::getRoll()
{
	return (this->roll);
}

void	Orientation::setPitch(float angle)
{
	this->pitch = angle;
	updateOrientation();
}

float	Orientation::getPitch()
{
	return (this->pitch);
}

void	Orientation::setYaw(float angle)
{
	this->yaw =  angle;
	updateOrientation();
}

float	Orientation::getYaw()
{
	return (this->yaw);
}

glm::vec3 Orientation::getDirection(){
    return direction;
}

void Orientation::setDirection(glm::vec3 direction){
    this->direction = direction; 
}


glm::vec3 Orientation::getRight(){
    return right;
}

void Orientation::setRight(glm::vec3 right){
    this->right = right; 
}

glm::vec3 Orientation::getUp(){
    return up;
}

void Orientation::setUp(glm::vec3 up){
    this->up = up; 
}

void Orientation::updateOrientation(){
	 direction.x = -sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	 direction.y = sin(glm::radians(pitch));
	 direction.z = cos(glm::radians(yaw)) * cos(glm::radians(pitch));

	 direction = glm::normalize(direction);
	 // Also re-calculate the Right and Up vector
	 right = glm::normalize(glm::cross(direction, glm::vec3(.0f,1.0f,0.0f))); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	 up = glm::normalize(glm::cross(right, direction));
}
 
