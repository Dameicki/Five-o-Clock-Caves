#pragma once

#include "Transform.h"
#include "Component.h"
#include "../Rendering/ShaderSystem.h"
#include "../Core/ResourceManager2.h"

class Component;

class SpriteRenderer : public Component
{
public:
	SpriteRenderer();
	SpriteRenderer(std::string path, int shaderID = 4);
	void Load() override;
	void SetUp() override;
	void Draw(std::shared_ptr<Transform> transform) override;

	void ImGuiAddToInspector(ImguiSystem* imguiSyste, int indexm) override;
	
	void SetTexture(std::string path);

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			CEREAL_NVP(m_texture),
			CEREAL_NVP(m_shaderID),
			CEREAL_NVP(m_texturePath)
		);
	}

private:
	unsigned int m_texture;
	int m_shaderID;
	std::string m_texturePath;

};

CEREAL_REGISTER_TYPE(SpriteRenderer);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, SpriteRenderer);