#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec2 Texture;
out vec4 FragColor;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;
uniform sampler2D ourTexture;
uniform bool isTextured;

void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    
    // specular
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;  
    if(isTextured){
    vec3 lighting = (ambient + diffuse + specular);
    vec4 result = vec4(lighting.x,lighting.y,lighting.z,1.0) * texture(ourTexture, Texture);
    FragColor = vec4(result);
    }
    else{
        vec3 result = (ambient + diffuse + specular) * objectColor;
        FragColor = vec4(result,1.0);
    }
    
}