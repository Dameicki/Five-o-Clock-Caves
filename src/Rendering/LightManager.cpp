#include "LightManager.h"

LightManager::LightManager()
{
	curentPointLightN = 0;
	pointLights = std::vector<std::shared_ptr<LightBase>>();
	spotLights = std::vector<std::shared_ptr<LightBase>>();
}

LightManager& LightManager::GetInstance()
{
	static LightManager* instance = NULL;

	if (instance == NULL)
		instance = new LightManager();

	return *instance;
}

void LightManager::AddLight(std::shared_ptr<LightBase> light, LightType lightType)
{
	RefreshLight(lightType);

	//cout << "dodano swiatlo " << endl;

	switch (lightType)
	{
	case point:
		pointLights.push_back(light);
		pointLights[curentPointLightN]->SetID(curentPointLightN);
		curentPointLightN++;
		break;
	case spot:
		spotLights.push_back(light);
		//spotLights.back()->SetID(spotLights.size());
		light->SetID(spotLights.size());
		break;
	case dir:
		currentDirLight = light;
		break;
	default:
		break;

	}
	RefreshLight(lightType);

}

void LightManager::RemoveLight(std::shared_ptr<LightBase> light, LightType lightType)
{
	RefreshLight(lightType);

	//cout << "usunieto swiatlo " << endl;

	if (light->GetID() != -1) // czy œwiat³o jest w liœcie
	{
		switch (lightType)
		{
		case point:
			curentPointLightN--;
			pointLights[light->GetID()].swap(pointLights.back()); //[curentPointLightN]);
			pointLights.pop_back();
			break;
		case spot:
			spotLights[light->GetID()].swap(spotLights.back());
			spotLights.pop_back();
			break;
		case dir:
			currentDirLight = nullptr;
			break;
		default:
			break;
		}

		RefreshLight(lightType);
		light->SetID(-1);
	}
}

void LightManager::RemoveAllLights()
{
	curentPointLightN = 0;

	//pointLights = std::vector<std::shared_ptr<LightBase>>();
	//spotLights = std::vector<std::shared_ptr<LightBase>>();
	//currentDirLight = nullptr;

	pointLights.clear(); // lista œwiate³ punktowych
	spotLights.clear();
	currentDirLight = nullptr;

	RefreshLight(point);
	RefreshLight(spot);
	RefreshLight(dir);
}

void LightManager::RefreshLight(LightType lightType) 
{
	switch (lightType)
	{
	case point:
		for (int i = 0; i < pointLights.size(); i++)
		{
			pointLights[i]->SetID(i);
		}

		ShaderSystem::GetInstance().CheckNumberOfLights(lightType, pointLights.size()); 
		break;
	case spot:
		for (int i = 0; i < spotLights.size(); i++)
		{
			spotLights[i]->SetID(i);
		}

		ShaderSystem::GetInstance().CheckNumberOfLights(lightType, spotLights.size());
		break;
	case dir:
	
		if(currentDirLight == nullptr) 
			ShaderSystem::GetInstance().CheckNumberOfLights(lightType, -1);
		else
			ShaderSystem::GetInstance().CheckNumberOfLights(lightType, 0);

		break;
	default:
		
		break;
	}

}

void LightManager::ClearLights()
{
	pointLights.clear(); // lista œwiate³ punktowych
	spotLights.clear();
	currentDirLight = nullptr;
}

void LightManager::FrustumCulling()
{
	for (auto& light : pointLights)
	{
		visiblePointN += light->FrustumCulling();
	}
	for (auto& light : spotLights)
	{
		visibleSpotN += light->FrustumCulling();
	}
}
