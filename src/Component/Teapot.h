#pragma once

#include "Component.h"
#include "ActionBase.h"
#include "Interactable.h"
#include "PlayerInteraction.h"
#include "PuzzleChecker.h"
#include <cereal/types/vector.hpp>
#include "Leaf.h"
#include "Core/AudioManager.h"

class Leaf;

enum TeaType {
	JUMP,
	STRENTH,
	NONE_EFFECT
};

class Teapot : public Interactable {
public:									// Jump = green				// Strenth = orange			// ? = red
	Teapot(TeaType teaType, vector<glm::vec3> colors = {glm::vec3(0.0f,1.0f,0.0f), glm::vec3(1.0f,0.5f,0.0f), glm::vec3(1.0f,0.0f,0.0f) });

	Teapot();

	void SetUp() override;

	void Update() override;
	void Trigger(std::shared_ptr<CollisionResult> collResult) override;
	void Interact(std::shared_ptr<GameObject> player) override;

	virtual std::shared_ptr<Component> GetCopyComponent() override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			cereal::base_class<Interactable>(this),
			CEREAL_NVP(_colors),
			CEREAL_NVP(_teaType)
		);
	}

private:
	void SetTea(TeaType teaType);

	shared_ptr<MeshRenderer> _meshRenderer;
	std::shared_ptr<MeshRenderer> _cube = nullptr;

	vector<glm::vec3> _colors;
	TeaType _teaType;
};

CEREAL_REGISTER_TYPE(Teapot);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Interactable, Teapot);