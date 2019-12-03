#version 330 core
in vec3 Normal;
in vec3 FragPos;
in vec2 Texture;
//in vec4 FragPosLightSpace;
out vec4 FragColor;

uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;
uniform vec3 objectColor;

//funiform sampler2D ourTexture;
uniform sampler2D shadowMap;

uniform bool isTextured;

struct Material{
    vec3 diffuse;
    vec3 ambient;
    vec3 specular;
    float shininess;
};
struct DirLight {
    vec3 direction;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;
	
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;       
};

//uniform int NUM_OF_POINTLIGHTS;

#define NUM_OF_POINTLIGHTS 1
#define NUM_OF_SPOTLIGHTS 10

uniform Material material;
uniform DirLight dirLight;
uniform PointLight pointLights[NUM_OF_POINTLIGHTS];
uniform SpotLight spotLights[NUM_OF_SPOTLIGHTS];

/*
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
}*/

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // combine results
    vec3 ambient = light.ambient * objectColor;
    vec3 diffuse = light.diffuse * diff * objectColor;
    vec3 specular = light.specular * spec * objectColor;
    return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * objectColor;
    vec3 diffuse  = light.diffuse  * diff *objectColor;
    vec3 specular = light.specular * spec * objectColor;
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
} 

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir){
    // ambient
    vec3 ambient = light.ambient * objectColor;
    
    // diffuse 
    vec3 lightDir = normalize(light.position - FragPos);
    float theta = dot(lightDir, normalize(-light.direction)); 

    if(theta > light.cutOff){
        // ambient
        vec3 ambient = light.ambient * objectColor;
        
        // diffuse 
        
        float diff = max(dot(normal, lightDir), 0.0);
        vec3 diffuse = light.diffuse * diff * objectColor;  
        
        // specular
        vec3 reflectDir = reflect(-lightDir, normal);  
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        vec3 specular = light.specular * spec * objectColor;  
        
        // attenuation
        float distance    = length(light.position - FragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

        ambient  *= attenuation; // remove attenuation from ambient, as otherwise at large distances the light would be darker inside than outside the spotlight due the ambient term in the else branche
        diffuse   *= attenuation;
        specular *= attenuation;   
            
        vec3 result = ambient + diffuse + specular;
        return result;
    }
    else{
        return vec3(.0f);
    }
}

void main()
{   
    // properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // phase 1: Directional lighting
    vec3 result = CalcDirLight(dirLight, norm, viewDir);
    
    // phase 2: Point lights
    //for(int i = 0; i < NUM_OF_POINTLIGHTS; i++)
        //result += CalcPointLight(pointLights[i], alnormalnorm, FragPos, viewDir);    
    //vec3 result  = vec3(0.0f);

    // phase 3: Spot light
    for(int i = 0; i < NUM_OF_SPOTLIGHTS; i++)
        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);    
    

    //float shadow = ShadowCalculation(FragPosLightSpace);                      
    //float shadow = 0.0f; 
    
   // if(isTextured){
     //   vec3 lighting = ambient  /*(1.0f-shadow)*/ + diffuse ;
       // vec4 result = vec4(lighting,1.0) * texture(ourTexture, Texture);
       // FragColor = vec4(result);
    //}

    //else{
        FragColor = vec4(result,1.0);
    //}
    
}