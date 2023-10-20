#include "AnimatedModel.h"


AnimatedModel::AnimatedModel(string const& path, bool gamma) : Model(gamma)
{
    //cout << "path = " << path << endl;
	loadModel(path);
}

void AnimatedModel::Draw(Shader& shader, bool needTexture)
{
    for (unsigned int i = 0; i < animatedMeshes.size(); i++)
        animatedMeshes[i].Draw(shader, needTexture);
}

std::map<string, BoneInfo> AnimatedModel::GetOffsetMatMap()
{
    return m_OffsetMatMap;
}

int& AnimatedModel::GetBoneCount()
{
    return m_BoneCount;
}

glm::mat2x3 AnimatedModel::GetBoundingBox()
{
    float min_x, max_x,
        min_y, max_y,
        min_z, max_z;
    min_x = max_x = animatedMeshes[0].vertices[0].Position.x;
    min_y = max_y = animatedMeshes[0].vertices[0].Position.y;
    min_z = max_z = animatedMeshes[0].vertices[0].Position.z;

    for (int i = 0; i < animatedMeshes.size(); i++)
    {
        for (int j = 0; j < animatedMeshes[i].vertices.size(); j++) {
            if (animatedMeshes[i].vertices[j].Position.x < min_x) min_x = animatedMeshes[i].vertices[j].Position.x;
            if (animatedMeshes[i].vertices[j].Position.x > max_x) max_x = animatedMeshes[i].vertices[j].Position.x;
            if (animatedMeshes[i].vertices[j].Position.y < min_y) min_y = animatedMeshes[i].vertices[j].Position.y;
            if (animatedMeshes[i].vertices[j].Position.y > max_y) max_y = animatedMeshes[i].vertices[j].Position.y;
            if (animatedMeshes[i].vertices[j].Position.z < min_z) min_z = animatedMeshes[i].vertices[j].Position.z;
            if (animatedMeshes[i].vertices[j].Position.z > max_z) max_z = animatedMeshes[i].vertices[j].Position.z;
        }
    }
    glm::vec3 size = glm::vec3(max_x - min_x, max_y - min_y, max_z - min_z);
    glm::vec3 center = glm::vec3((min_x + max_x) / 2, (min_y + max_y) / 2, (min_z + max_z) / 2);
    return glm::mat2x3(size, center);
}

//inline glm::mat4 AnimatedModel::ConvertMatrixToGLMFormat(const aiMatrix4x4& from)

//inline glm::vec3 AnimatedModel::GetGLMVec(const aiVector3D& vec)

//inline glm::quat AnimatedModel::GetGLMQuat(const aiQuaternion& pOrientation)



void AnimatedModel::SetVertexBoneDataToDefault(AnimatedVertex& vertex)
{
    for (int i = 0; i < MAX_BONE_WEIGHTS; i++)
    {
        vertex.BoneID[i] = -1;
        vertex.Weight[i] = 0.0f;
    }
}

void AnimatedModel::ExtractBoneWeightForVertices(std::vector<AnimatedVertex>& vertices, aiMesh* mesh, const aiScene* scene)
{
    auto& boneInfoMap = m_OffsetMatMap;
    int& boneCount = m_BoneCount;

    for (int boneIndex = 0; boneIndex < mesh->mNumBones; ++boneIndex)
    {
        int boneID = -1;
        std::string boneName = mesh->mBones[boneIndex]->mName.C_Str();
        if (boneInfoMap.find(boneName) == boneInfoMap.end())
        {
            BoneInfo newBoneInfo;
            newBoneInfo.id = boneCount;
            newBoneInfo.offset = ConvertMatrixToGLMFormat(mesh->mBones[boneIndex]->mOffsetMatrix);
            boneInfoMap[boneName] = newBoneInfo;
            boneID = boneCount;
            boneCount++;
        }
        else
        {
            boneID = boneInfoMap[boneName].id;
        }
        assert(boneID != -1);
        auto weights = mesh->mBones[boneIndex]->mWeights;
        int numWeights = mesh->mBones[boneIndex]->mNumWeights;

        for (int weightIndex = 0; weightIndex < numWeights; ++weightIndex)
        {
            int vertexId = weights[weightIndex].mVertexId;
            float weight = weights[weightIndex].mWeight;
            assert(vertexId <= vertices.size());
            SetVertexBoneData(vertices[vertexId], boneID, weight);
        }
    }
}

void AnimatedModel::SetVertexBoneData(AnimatedVertex& vertex, int boneID, float weight)
{
    for (int i = 0; i < MAX_BONE_WEIGHTS; ++i)
    {
        if (vertex.BoneID[i] < 0)
        {
            vertex.Weight[i] = weight;
            vertex.BoneID[i] = boneID;
            break;
        }
    }
}

void AnimatedModel::processNode(aiNode* node, const aiScene* scene)
{
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        animatedMeshes.push_back(processAnimatedMesh(mesh, scene));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

AnimatedMesh AnimatedModel::processAnimatedMesh(aiMesh* mesh, const aiScene* scene)
{
    // data to fill
    vector<AnimatedVertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        AnimatedVertex vertex;
        SetVertexBoneDataToDefault(vertex);

        // positions
        vertex.Position = GetGLMVec(mesh->mVertices[i]);
        // normals
        vertex.Normal = GetGLMVec(mesh->mNormals[i]);

        // texture coordinates
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
            //// tangent
            //vector.x = mesh->mTangents[i].x;
            //vector.y = mesh->mTangents[i].y;
            //vector.z = mesh->mTangents[i].z;
            //vertex.Tangent = vector;
            //// bitangent
            //vector.x = mesh->mBitangents[i].x;
            //vector.y = mesh->mBitangents[i].y;
            //vector.z = mesh->mBitangents[i].z;
            //vertex.Bitangent = vector;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "material.texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "material.texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "material.texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "material.texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    ExtractBoneWeightForVertices(vertices, mesh, scene);

    // return a mesh object created from the extracted mesh data
    return AnimatedMesh(vertices, indices, textures);
}


