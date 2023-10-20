#version 440

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos; 
in vec4 FragPosLightSpace;

struct Material {
    sampler2D texture_diffuse1;
    vec3      specular;
    vec3      color;
    float     shininess;
}; 

uniform vec3 viewPos; 
uniform Material material;

void main()
{
    vec3 result = vec3(texture(material.texture_diffuse1, TexCoords));
    result *= material.color;

	FragColor = vec4(result, 1.0);
}
