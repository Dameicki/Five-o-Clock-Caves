#pragma once

#include "../learnopengl/model.h"
#include "Transform.h"
#include "Component.h"
#include "../Rendering/ShaderSystem.h"
#include "../Core/ResourceManager2.h"

class Component;

class MeshRenderer : public Component
{
public:
	MeshRenderer();
	MeshRenderer(std::string path, int shaderID = 2 ,glm::vec3 color = glm::vec3(1.0f), float shininess = 32.0f, glm::vec3 specular = glm::vec3(0.1f));

	void Load() override;
	void SetUp() override; // Setapuje parametry bounding spherow
	void Input() override;
	void Update() override;
	void Draw(std::shared_ptr<Transform> transform) override;

	void DrawToShadowMap(std::shared_ptr<Transform> transform) override;

	std::shared_ptr<Component> GetCopyComponent() override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	void SetModel(std::string path);

	void SetColor(glm::vec3 newColor);

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(cereal::base_class<Component>(this),
			CEREAL_NVP(m_modelPath),
			CEREAL_NVP(m_specular), 
			CEREAL_NVP(m_color), 
			CEREAL_NVP(m_shininess), 
			CEREAL_NVP(m_shaderID)
		);

	}

private:
	std::shared_ptr<Model> m_model;
	glm::vec3 m_specular;
	glm::vec3 m_color;
	std::string m_modelPath;
	float m_shininess;
	int m_shaderID;
	bool aniamted;

};

CEREAL_REGISTER_TYPE(MeshRenderer);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, MeshRenderer);