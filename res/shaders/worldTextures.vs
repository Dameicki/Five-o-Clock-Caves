#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos; 
out vec4 FragPosLightSpace;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos = vec3(model * vec4(aPos, 1.0));
        
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Normal = normalize(Normal);

    if( abs(Normal.z) > 0.8) 
        TexCoords = vec2(FragPos.x, FragPos.y) * 0.2;
    else if(abs(Normal.x) > 0.8) 
        TexCoords = vec2(FragPos.z, FragPos.y) * 0.2;
    else
        TexCoords = vec2(FragPos.x, FragPos.z) * 0.2;

    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos,1.0);

}