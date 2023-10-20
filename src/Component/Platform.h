#pragma once

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include "core/GameObject.h"
#include "ActionBase.h"
#include "Component.h"
#include <cereal/types/vector.hpp>

class GameObject; 
class Component;

class Platform : public ActionBase {
public:
	Platform();
	Platform(bool isActive, bool isUsable, std::vector<glm::vec4> travelVectors, 
			 std::vector<glm::vec4> travelPoints, bool repetable, bool returnsOnDeactivation,
			 bool loop);

	std::shared_ptr<Component> GetCopyComponent() override;


	void Start() override;
	void SetUp() override;
	void Run() override;
	void Return() override;
	void Move();
	void ActionStop() override;
	void ActionStart() override;

	void AddTravelVector(glm::vec4 vector);
	void ReplaceTravelVector(glm::vec4 vector, int id);
	void RemoveTravelVector(int i);

	void SetRepetable(bool state);
	void SetReturnOnDeactivation(bool state);
	void Reset();
	void GenerateTravelPoints();

	glm::vec3 GetTmpMovementVector();

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<ActionBase>(this),
			CEREAL_NVP(_travelVectors),
			CEREAL_NVP(_travelPoints),
			CEREAL_NVP(_tmpMovementVector),
			CEREAL_NVP(_repetable),
			CEREAL_NVP(_returnsOnDeactivation),
			CEREAL_NVP(_loop)
		);
	}

private:
	std::vector<glm::vec4> _travelVectors;
	std::vector<glm::vec4> _travelPoints;
	glm::vec3 _tmpMovementVector = glm::vec3(0.0f);
	int _actualLocation = 0;
	int _direction = 1;
	float _timer = 0.0f;

	bool _repetable = true;
	bool _returnsOnDeactivation = false;
	bool _loop = false;
	bool _reachedCheckpoint = false;
	bool _start = false;

	bool CloseVectors(glm::vec3 a, glm::vec3 b, float lenght = 0.01f);
	glm::vec3 Lerp(glm::vec3 a, glm::vec3 b, float t);

	glm::vec4 _tmpVec = glm::vec4(0.0f);
	int _tmpId = 0;
};

CEREAL_REGISTER_TYPE(Platform);
CEREAL_REGISTER_POLYMORPHIC_RELATION(ActionBase, Platform);