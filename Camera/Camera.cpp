#include "Camera.hpp"

Camera::Camera(/* args */)
{
	updateMatrix();
}

Camera::~Camera()
{
	
}

void	Camera::setRoll(float angle)
{
	this->roll = angle;
	updateMatrix();
}

float	Camera::getRoll()
{
	return (this->roll);
}

void	Camera::setPitch(float angle)
{
	this->pitch = angle;
	updateMatrix();
}

float	Camera::getPitch()
{
	return (this->pitch);
}

void	Camera::setYaw(float angle)
{
	this->yaw =  angle;
	updateMatrix();
}

float	Camera::getYaw()
{
	return (this->yaw);
}

void	Camera::setFov(float fov)
{
	this->fov = fov;
}

float	Camera::getFov()
{
	return (this->fov);
}

glm::vec3 Camera::getDirection(){
    return direction;
}

void Camera::setDirection(glm::vec3 direction){
    this->direction = direction; 
}


glm::vec3 Camera::getRight(){
    return right;
}

void Camera::setRight(glm::vec3 right){
    this->right = right; 
}

glm::vec3 Camera::getUp(){
    return up;
}

void Camera::setUp(glm::vec3 up){
    this->up = up; 
}

void Camera::updateMatrix(){
	 direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	 direction.y = sin(glm::radians(pitch));
	 direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	 direction = glm::normalize(direction);
	 // Also re-calculate the Right and Up vector
	 right = glm::normalize(glm::cross(direction, glm::vec3(.0f,1.0f,0.0f))); // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	 up = glm::normalize(glm::cross(right, direction));
	 viewMatrix = glm::lookAt(position, position + direction, up);
}

glm::mat4* Camera::getViewMatrix(){
	return &viewMatrix;
} 

void Camera::setViewMatrix(glm::mat4 mat){
	viewMatrix = mat;
}

void Camera::setProjectionMatrix(glm::mat4 mat){
	projectionMatrix = mat;
}

glm::mat4* Camera::getProjectionMatrix(){
	return &projectionMatrix;
} 

void Camera::setPosition(glm::vec3 pos){
	position = pos;
	updateMatrix();
}

glm::vec3 Camera::getPosition(){
	return position;
}