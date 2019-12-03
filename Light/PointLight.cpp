#include "PointLight.hpp"

PointLight::PointLight()
{
	
}


glm::vec3 PointLight::getColor(){
    return color;
}


void PointLight::setColor(glm::vec3 col)
{
	this->color = col;
}


void PointLight::sendToShader(Shader* shader){
	shader->use();
	shader->setVec3(("pointLights[" + std::to_string(lightId) + "].position").c_str() , position);
	shader->setVec3(("pointLights[" + std::to_string(lightId) + "].diffuse").c_str(), diffuse);
	shader->setVec3(("pointLights[" + std::to_string(lightId) + "].specular").c_str(), specular);
	shader->setVec3(("pointLights[" + std::to_string(lightId) + "].ambient").c_str(), ambient);
	shader->setFloat(("pointLights[" + std::to_string(lightId) + "].constant").c_str(), constant);
	shader->setFloat(("pointLights[" + std::to_string(lightId) + "].linear").c_str(), linear);
	shader->setFloat(("pointLights[" + std::to_string(lightId) + "].quadratic").c_str(), quadratic);

}

void PointLight::sendAsSpotlight(Shader* shader){
	shader->use();
	shader->setVec3(("spotLights[" + std::to_string(lightId) + "].position").c_str() , position);
	
	if(active == 0){
		shader->setVec3(("spotLights[" + std::to_string(lightId) + "].diffuse").c_str(), glm::vec3(.0f));
		shader->setVec3(("spotLights[" + std::to_string(lightId) + "].specular").c_str(), glm::vec3(.0f));
		shader->setVec3(("spotLights[" + std::to_string(lightId) + "].ambient").c_str(), glm::vec3(.0f));
	}
	else{
		shader->setVec3(("spotLights[" + std::to_string(lightId) + "].diffuse").c_str(), diffuse);
		shader->setVec3(("spotLights[" + std::to_string(lightId) + "].specular").c_str(), specular);
		shader->setVec3(("spotLights[" + std::to_string(lightId) + "].ambient").c_str(), ambient);
	}
	
	shader->setFloat(("spotLights[" + std::to_string(lightId) + "].constant").c_str(), constant);
	shader->setFloat(("spotLights[" + std::to_string(lightId) + "].linear").c_str(), linear);
	shader->setFloat(("spotLights[" + std::to_string(lightId) + "].cutOff").c_str(),cutOff);
	shader->setFloat(("spotLights[" + std::to_string(lightId) + "].outerCutOff").c_str(), outerCutOff);
	shader->setVec3(("spotLights[" + std::to_string(lightId) + "].direction").c_str(), direction);


}
/*void PointLight::attachToMesh(Mesh*mesh){

}*/