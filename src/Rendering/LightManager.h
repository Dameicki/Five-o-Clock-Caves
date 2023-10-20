#pragma once
#define LIGHTS LightManager::GetInstance()

#include <memory>
#include <vector>

#include "../Component/LightBase.h"

class LightBase;

enum LightType
{
	point,
	spot,
	dir
};

class LightManager
{
public:
	//ShaderSystem(const ShaderSystem&) = delete; // usuno�em konstruktor kopiuj�cy
	LightManager();

	static LightManager& GetInstance();

	void AddLight(std::shared_ptr<LightBase> light, LightType lightType);
	void RemoveLight(std::shared_ptr<LightBase> light, LightType lightType);

	void RemoveAllLights();

	void RefreshLight(LightType lightType);

	void ClearLights();

	void FrustumCulling();

	int visiblePointN = 0;
	int visibleSpotN = 0;

	std::vector<std::shared_ptr<LightBase>> pointLights; // lista �wiate� punktowych
	std::vector<std::shared_ptr<LightBase>> spotLights; // lista �wiate� punktowych
private:
	int curentPointLightN; // ilo�� �wiate� punktowych w li�cie
	std::shared_ptr<LightBase> currentDirLight;
	
};
