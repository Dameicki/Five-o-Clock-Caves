#pragma once

#include "Component.h"
#include "Interactable.h"
#include "PlayerInteraction.h"
#include "Level.h"
#include "Core/AudioManager.h"

#include <cereal/types/vector.hpp>

class DoorInteract : public Interactable {
public:
	DoorInteract();
	DoorInteract(glm::vec3 teleportDir);

	virtual void OpenDoor();

	virtual void Update() override;

	virtual void SetUp() override;

	void Trigger(std::shared_ptr<CollisionResult> collResult) override;
	void Interact(std::shared_ptr<GameObject> player) override;

	virtual std::shared_ptr<Component> GetCopyComponent() override;

	virtual void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{

		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<Interactable>(this),
			CEREAL_NVP(_teleportDir),
			CEREAL_NVP(_targetLevel)
			);
	}

private:
	void ChangeCubs();

	glm::vec3 _teleportDir = glm::vec3(0.0f);

	bool save = false;

	int _playersIn = 0;
	int _lastPlayerIn = 0;
	bool _pressE = false;
	std::shared_ptr<GameObject> _player;
	std::shared_ptr<Level> _targetLevel;

	list<shared_ptr<MeshRenderer>> _cubes;

	bool _usedLastFrame = false;
};

CEREAL_REGISTER_TYPE(DoorInteract);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interactable, DoorInteract);