#pragma once

#include <Core/GameObject.h>
#include <Learnopengl/camera.h>

class CameraController : public Component
{
	friend class cereal::access;

	bool levelComplet;

	glm::vec3 forwardDirection;
	glm::vec3 sideDirection;
	std::shared_ptr<GameObject> player1, player2;
	glm::vec3 player1pos, player2pos, camDefaultPos, camDefaultRotation[3], camPos;
	CameraController() {};
public:
	CameraController(std::shared_ptr<GameObject> &p1, std::shared_ptr<GameObject> &p2);

	void SetUp() override;
	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;
	void Input() override;
	void Update() override;
	void Draw(std::shared_ptr<Transform> transform) override;

	void LevelComplet();
	void SetPosition(glm::vec3 newPosition);
	void SetLookDir(glm::vec3 newLookDir);

	void CameraEditorMove();
	void CameraMove();
	void CameraRotate();
	void setDefaultRotation();


	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(cereal::base_class<Component>(this),
			CEREAL_NVP(player1), 
			CEREAL_NVP(player2),
			CEREAL_NVP(player1pos),
			CEREAL_NVP(player2pos),
			CEREAL_NVP(camDefaultPos),
			CEREAL_NVP(camDefaultRotation)
		);
	}

};


CEREAL_REGISTER_TYPE(CameraController);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, CameraController);