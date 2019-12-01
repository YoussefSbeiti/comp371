#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec2 Texture;
in vec4 FragPosLightSpace;
out vec4 FragColor;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

//funiform sampler2D ourTexture;
//uniform sampler2D shadowMap;

uniform bool isTextured;

struct Material{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    vec3 shininess;
};

struct Light{
    vec3 ambient ;
    vec3 specular ;
    vec3 diffuse;
};

uniform Material material;
uniform Light light;

float ShadowCalculation(vec4 fragPosLightSpace)
{
    // perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    // check whether current frag pos is in shadow
    // float shadow = currentDepth - bias > closestDepth  ? 1.0 : 0.0;
    // PCF
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth  ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;
    
    // keep the shadow at 0.0 when outside the far_plane region of the light's frustum.
    //if(projCoords.z > 1.0)
      //  shadow = 0.0;
        
    return shadow;
}


void main()
{   
    
    // ambient
    vec3 ambient =  material.ambient * lightColor;
  	
    // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * material.diffuse * lightColor;
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1.0);
    vec3 specular = material.specular * lightColor * spec; 

    float shadow = ShadowCalculation(FragPosLightSpace);                      
    //float shadow = 0.0f; 
    
   // if(isTextured){
     //   vec3 lighting = ambient  /*(1.0f-shadow)*/ + diffuse ;
       // vec4 result = vec4(lighting,1.0) * texture(ourTexture, Texture);
       // FragColor = vec4(result);
    //}

    //else{
        float shadowMultiplier = 1.0 - shadow;
        vec3 result = (ambient +  shadowMultiplier* (diffuse + specular)) * objectColor;
        FragColor = vec4(result,1.0);
    //}
    
}