#pragma once

#include <glad/glad.h> 

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Quaternion.h>
#include <assimp/vector3.h>
#include <assimp/matrix4x4.h>

#include "AnimatedMesh.h"
//#include <Animation\Joint.h>
#include "../Learnopengl/shader.h"
#include "../Learnopengl/model.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#define MAX_BONES 256
#define MAX_BONE_WEIGHTS 4

using namespace std;

struct BoneInfo
{
    /*id is index in finalBoneMatrices*/
    int id;

    /*offset matrix transforms vertex from model space to bone space*/
    glm::mat4 offset;

};

class AnimatedModel: public Model
{
public:
    vector<AnimatedMesh>    animatedMeshes;

    // constructor, expects a filepath to a 3D model.
    AnimatedModel(string const& path, bool gamma = false);

    // draws the model, and thus all its meshes
    void Draw(Shader& shader, bool needTexture) override;

    std::map<string, BoneInfo> GetOffsetMatMap();
    int& GetBoneCount();
    glm::mat2x3 GetBoundingBox() override;

    static inline glm::mat4 ConvertMatrixToGLMFormat(const aiMatrix4x4& from)
    {
        glm::mat4 to;
        //the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
        to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
        to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
        to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
        to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
        return to;
    }
    static inline glm::vec3 GetGLMVec(const aiVector3D& vec){
        return glm::vec3(vec.x, vec.y, vec.z);
    }
    static inline glm::quat GetGLMQuat(const aiQuaternion& pOrientation){   
        return glm::quat(pOrientation.w, pOrientation.x, pOrientation.y, pOrientation.z);
    }

private:
    std::map<string, BoneInfo> m_OffsetMatMap;
    int m_BoneCount = 0;

    void SetVertexBoneDataToDefault(AnimatedVertex& vertex);
    void ExtractBoneWeightForVertices(std::vector<AnimatedVertex>& vertices, aiMesh* mesh, const aiScene* scene);

    void SetVertexBoneData(AnimatedVertex& vertex, int boneID, float weight);

    void processNode(aiNode* node, const aiScene* scene) override;
    AnimatedMesh processAnimatedMesh(aiMesh* mesh, const aiScene* scene);
};
