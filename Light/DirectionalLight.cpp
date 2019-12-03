#include "DirectionalLight.hpp"

void	DirectionalLight::sendToShader(Shader* shader)
{
	shader->use();
        shader->setVec3("dirLight.direction" , direction);
        shader->setVec3("dirLight.diffuse", diffuse);
        shader->setVec3("dirLight.specular", specular);
        shader->setVec3("dirLight.ambient", ambient);
}
