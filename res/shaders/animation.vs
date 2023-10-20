#version 440 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 norm;
layout(location = 2) in vec2 tex;
layout(location = 3) in ivec4 boneIds; 
layout(location = 4) in vec4 weights;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

const int MAX_BONES = 200;
const int MAX_BONE_INFLUENCE = 4;
uniform mat4 finalBonesMatrices[MAX_BONES];

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos; 
out vec4 FragPosLightSpace;

void main()
{
    vec4 totalPosition = vec4(0.0);
    vec3 totalNormal = vec3(0.0);

    for(int i = 0 ; i < MAX_BONE_INFLUENCE ; i++)
    {
        if(boneIds[i] == -1) 
            continue;
        if(boneIds[i] >= MAX_BONES) 
        {
            totalPosition = vec4(pos,1.0);
            totalNormal = vec3(norm);
            break;
        }
        vec4 localPosition = finalBonesMatrices[boneIds[i]] * vec4(pos,1.0);
        totalPosition += localPosition * weights[i];
        vec3 localNormal = mat3(finalBonesMatrices[boneIds[i]]) * norm;
        totalNormal += localNormal;
    }
	
    mat4 viewModel = view * model;
    gl_Position =  projection * viewModel * totalPosition;
	TexCoords = tex;

    totalNormal = normalize(totalNormal);
    Normal = mat3(transpose(inverse(model))) * totalNormal;
    FragPos = vec3(model * totalPosition);
    FragPosLightSpace = lightSpaceMatrix * vec4(FragPos,1.0);
}