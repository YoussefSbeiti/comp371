#version 330 core
layout (location = 0) in vec3 aPos;
layout(location=1)in vec3 aNormal;
layout(location=2)in vec2 aTexture;

uniform mat4 lightSpaceMatrix;
uniform mat4 worldMatrix;
uniform mat4 localMatrix;

void main()
{
    mat4 model = worldMatrix * localMatrix; 
    gl_Position = lightSpaceMatrix * model * vec4(aPos, 1.0);
}