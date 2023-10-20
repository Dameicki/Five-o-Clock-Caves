#version 330

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos; 
in vec4 FragPosLightSpace;

struct DirLight {
    bool enable;

    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    bool enable;

    vec3 position;  
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
	
    float constant;
    float linear;
    float quadratic;
}; 

struct SpotLight {
    bool enable;

	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;
};

struct Material {
    vec3      specular;
    vec3      color;
    float     shininess;
}; 

#define NR_POINT_LIGHTS 5
#define NR_SPOT_LIGHTS 7

uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLights[NR_SPOT_LIGHTS];
uniform DirLight dirLight;
//uniform SpotLight spotLight1;
//uniform SpotLight spotLight2;

uniform vec3 viewPos; 
uniform Material material;

uniform sampler2D shadowMap;
//uniform sampler2D texture_diffuse1;
//uniform vec3 ambientColor;
//uniform vec3 lightColor;
//uniform vec3 lightPos; 


// nagłówki funkcji
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
float ShadowCalculation(vec4 fragPosLightSpace);

void main()
{
	vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

	// Efekt światła kierunkowego
	vec3 result = CalcDirLight(dirLight, norm, viewDir);

	// Efekt światła punktowego
	//result += CalcPointLight(pointLight, norm, FragPos, viewDir); 
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);  

    for(int i = 0; i < NR_SPOT_LIGHTS; i++)
        result += CalcSpotLight(spotLights[i], norm, FragPos, viewDir);  
	// Efekt światła refretorowego
	//result += CalcSpotLight(spotLight1, norm, FragPos, viewDir); 
	//result += CalcSpotLight(spotLight2, norm, FragPos, viewDir); 

    // zmnieszenie ilości koloró (bajer)
    //int x = int(result.x * 16);
    //int y = int(result.y * 16);
    //int z = int(result.z * 16);
    //result = (vec3(x,y,z) + vec3(0.5, 0.5, 0.5)) /16;

    //result *= material.color;

	FragColor = vec4(result, 1.0);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    if(light.enable == true)
    {
        vec3 lightDir = normalize(-light.direction);

        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);

        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

        // combine results
        vec3 ambient = light.ambient * material.color;
        vec3 diffuse = light.diffuse * diff * material.color;
        vec3 specular = light.specular * spec * material.specular;

        vec3 shadow = ShadowCalculation(FragPosLightSpace) * (diffuse+specular);
        return (ambient + shadow);//diffuse + specular);
    }
    if(light.enable == false)
    {
        return vec3(0.0);
    }
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    if(light.enable == true)
    {
        vec3 lightDir = normalize(light.position - fragPos);

        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);

        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

        // attenuation
        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

        // combine results
        vec3 ambient = light.ambient * material.color;
        vec3 diffuse = light.diffuse * diff * material.color;
        vec3 specular = light.specular * spec * material.specular;
        ambient *= attenuation;
        diffuse *= attenuation;
        specular *= attenuation;

        vec3 shadow = ShadowCalculation(FragPosLightSpace) * (diffuse+specular);
        return (ambient + shadow);//diffuse + specular);
    }
    if(light.enable == false)
    {
        return vec3(0.0);
    }
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    if(light.enable == true)
    {
        vec3 lightDir = normalize(light.position - fragPos);

        // diffuse shading
        float diff = max(dot(normal, lightDir), 0.0);

        // specular shading
        vec3 reflectDir = reflect(-lightDir, normal);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
        
        // attenuation
        float distance = length(light.position - fragPos);
        float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));  

        // spotlight intensity
        float theta = dot(lightDir, normalize(-light.direction)); 
        float epsilon = light.cutOff - light.outerCutOff;
        float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
        
        // combine results
        vec3 ambient = light.ambient * material.color;
        vec3 diffuse = light.diffuse * diff * material.color;
        vec3 specular = light.specular * spec * material.specular;
        ambient *= attenuation * intensity;
        diffuse *= attenuation * intensity;
        specular *= attenuation * intensity;
        
        vec3 shadow = ShadowCalculation(FragPosLightSpace) * (diffuse+specular);
        return (ambient + shadow);//diffuse + specular);
    }
    if(light.enable == false)
    {
        return vec3(0.0);
    }
}

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
    // check whether current frag pos is in shadow
     float bias =  0.005; //max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);  
     float shadow = (currentDepth - bias) > closestDepth  ? 0.5 : 1.0;  
    return shadow;
}