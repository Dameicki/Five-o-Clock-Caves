#pragma once

#include "Component.h"
//#include "ActionBase.h"
#include "Interactable.h"
#include "DoorInteract.h"
#include "PlayerInteraction.h"
#include "Core/AudioManager.h"
//#include "PuzzleChecker.h"
#include <cereal/types/vector.hpp>

class DoorInteract;
class CameraController;

class GooldDoorInteract : public DoorInteract {
public:
	GooldDoorInteract();
	GooldDoorInteract(string nextLevelPath);
	
	void SetUp() override;
	void Update() override;

	void OpenDoor() override;

	std::shared_ptr<Component> GetCopyComponent() override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<Interactable>(this),
			CEREAL_NVP(_nextLevelPath)
			//CEREAL_NVP(_turnOffTime),
			//CEREAL_NVP(_puzzleCheck)
			);
	}

private:
	shared_ptr<CameraController> cameraController;
	string _nextLevelPath;
	bool doorOpen;
};

CEREAL_REGISTER_TYPE(GooldDoorInteract);
CEREAL_REGISTER_POLYMORPHIC_RELATION(DoorInteract, GooldDoorInteract);