#include "ResourceManager2.h"


ResourceManager2::ResourceManager2()
{

}

void ResourceManager2::AddModel(std::string path)
{
	modelPathsList.push_back(path);
	modelsList.push_back(std::make_shared<Model>(Model(path)));
}

void ResourceManager2::AddAnimatedModel(std::string path)
{
	animatedModelPathsList.push_back(path);
	animatedModelsList.push_back(std::make_shared<AnimatedModel>(AnimatedModel(path)));
}

ResourceManager2& ResourceManager2::GetInstance()
{
	static ResourceManager2* instance = NULL;

	if (instance == NULL)
		instance = new ResourceManager2();

	return *instance;
}

void ResourceManager2::AddAnimation(std::string path, std::shared_ptr<AnimatedModel> model)
{
	animationsPathsList.push_back(path);
	animationsList.push_back(std::make_shared<Animation>(Animation(path, model)));
}

void ResourceManager2::AddTexture(std::string path)
{
	texturePathList.push_back(path);
	textureList.push_back(Model::LoadTexture(path));
}

shared_ptr<Model> ResourceManager2::GetModel(std::string path)
{
	for(int i=0;i<modelPathsList.size();i++)
	{
		if (modelPathsList[i] == path)	return modelsList[i];
	}
	AddModel(path);
	return modelsList[modelsList.size() - 1];
}

shared_ptr<AnimatedModel> ResourceManager2::GetAnimatedModel(std::string path)
{
	for (int i = 0; i < animatedModelPathsList.size(); i++)
	{
		if (animatedModelPathsList[i] == path)	return animatedModelsList[i];
	}
	AddAnimatedModel(path);
	return animatedModelsList[animatedModelsList.size() - 1];
}

unsigned int ResourceManager2::GetTexture(std::string path)
{
	for (int i = 0; i < texturePathList.size(); i++)
	{
		if (texturePathList[i] == path) return textureList[i];
	}
	AddTexture(path);
	return textureList[textureList.size() - 1];
}

shared_ptr<Animation> ResourceManager2::GetAnimation(string path, shared_ptr<AnimatedModel> model)
{
	for (int i = 0; i < animationsPathsList.size(); i++)
	{
		if (animationsPathsList[i] == path) return animationsList[i];
	}
	AddAnimation(path, model);
	return animationsList[animationsList.size() - 1];
}

void ResourceManager2::PrepereLoadScen(string scenePath, shared_ptr<GameObject> root)
{
	_newScenePath = scenePath;
	_root = root;
	_loadNewScene = true;	
}

void ResourceManager2::LoadScen()
{
	if (_loadNewScene)
	{
		_root->DestroyAllChild();

		LIGHTS.RemoveAllLights();

		//_root = std::make_shared<GameObject>(GameObject("root"));

		_root->Deserialize(_newScenePath);
		CAMERA.SetUp(glm::vec3(-13.5f, 60.0f, 13.5f));
		_root->Load();




		_root->SetUp();
		FRUSTUM.SetUp();

		_loadNewScene = false;
	}
}


