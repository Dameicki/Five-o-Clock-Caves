#pragma once

#include "../learnopengl/model.h"
#include "Transform.h"
#include "Component.h"
#include "../Rendering/ShaderSystem.h"
#include "../Core/ResourceManager2.h"
#include "../Animation/AnimatedModel.h"

class Component;

class AnimatedMeshRenderer : public Component
{
public:
	AnimatedMeshRenderer();
	AnimatedMeshRenderer(std::string path, int shaderID = 0 ,glm::vec3 color = glm::vec3(1.0f), float shininess = 32.0f, glm::vec3 specular = glm::vec3(0.1f));

	void Draw(std::shared_ptr<Transform> transform) override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	void SetModel(std::string path);
	
private:
	std::shared_ptr<AnimatedModel> m_model;
	glm::vec3 m_specular;
	glm::vec3 m_color;
	float m_shininess;
	int m_shaderID;
};