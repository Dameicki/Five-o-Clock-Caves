#pragma once

#include <glm/vec3.hpp>

#include "core/GameObject.h"
#include "Component.h"
#include "LightBase.h"

class GameObject; 
class Component;

class Level : public Component {
public:
	Level();

	std::shared_ptr<Component> GetCopyComponent() override;

	void SetUp()override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	void LightsOn();
	void LightsOff();

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this)
		);
	}


private:
	list<shared_ptr<LightBase>> _lights;
	
};
CEREAL_REGISTER_TYPE(Level);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, Level);