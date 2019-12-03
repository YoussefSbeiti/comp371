 #version 330 core
layout(location=0)in vec3 aPos;
layout(location=1)in vec3 aNormal;
layout(location=2)in vec2 aTexture;

out vec3 FragPos;
out vec3 Normal;
out vec2 Texture;
out vec4 FragPosLightSpace;

uniform mat4 localMatrix;
uniform mat4 worldMatrix;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 lightSpaceMatrix;

void main()
{
    vec3 viewTranslation = vec3(view[0][3] , view[1][3] , view[2][3]);
    
    view = mat4(1.0f,.0f,.0f,viewTranslation.x,
                .0f,1.0f,.0f,viewTranslation.y,
                .0f,.0f,1.0f,viewTranslation.z,
                .0f,.0f,.0f,1.0f
    )

    mat4 model = worldMatrix*localMatrix;
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;  
    
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
    gl_Position = projection * view * vec4(FragPos, 1.0);
    Texture =  aTexture;
}