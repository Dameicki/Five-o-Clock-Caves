#pragma once

#define RESOURCE ResourceManager2::GetInstance()

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "../src/learnopengl/model.h"

#include "../Animation/AnimatedModel.h"
#include "../Animation/Animation.h"

#include "GameObject.h"

//class AnimatedModel;
//class Animation;

class ResourceManager2 
{
public:
	static ResourceManager2& GetInstance();
	shared_ptr<Model> GetModel(std::string path);
	shared_ptr<AnimatedModel> GetAnimatedModel(std::string path);
	unsigned int GetTexture(std::string path);
	shared_ptr<Animation> GetAnimation(string path, shared_ptr<AnimatedModel> model);

	void PrepereLoadScen(string scenePath, shared_ptr<GameObject> root);
	void LoadScen();

	std::vector<std::string> modelPathsList; // publiczna aby ³atwiej j¹ by³o wyœwietliæ w inspektorze
private:
	ResourceManager2();

	bool _loadNewScene = false;
	string _newScenePath;
	shared_ptr<GameObject> _root;

	void AddModel(std::string path);
	std::vector<std::shared_ptr<Model>> modelsList;

	void AddAnimatedModel(std::string path);
	std::vector<std::string> animatedModelPathsList;
	std::vector<std::shared_ptr<AnimatedModel>> animatedModelsList;

	void AddAnimation(std::string path, std::shared_ptr<AnimatedModel> model);
	std::vector<std::string> animationsPathsList;
	std::vector<std::shared_ptr<Animation>> animationsList;

	void AddTexture(std::string path);
	std::vector<std::string> texturePathList;
	std::vector<unsigned int> textureList;
};