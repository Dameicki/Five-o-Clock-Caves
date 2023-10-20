#pragma once

#include "../learnopengl/model.h"
#include "Transform.h"
#include "Component.h"
#include "../Rendering/ShaderSystem.h"
#include "../Core/ResourceManager2.h"
#include "../Animation/Animator.h"

class Component;

class AnimatorComponent : public Component
{
public:
	AnimatorComponent();
	AnimatorComponent(std::string modelPath, std::vector<std::string> animationPaths, std::vector<float> speed_animations, int shaderID = 7, int currentAnimations = 0, glm::vec3 color = glm::vec3(1.0f), float shininess = 32.0f, glm::vec3 specular = glm::vec3(0.1f));

	void Load() override;
	void SetUp() override; // Setapuje parametry bounding spherow
	void Input() override;
	void Update() override;
	void Draw(std::shared_ptr<Transform> transform) override;

	void DrawToShadowMap(std::shared_ptr<Transform> transform) override;

	void PlayAnimation(int animation);

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	void SetModel(std::string path);

	void AddAnimation(std::string path);

	void SetPowerUPShader(int powerUp);

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(cereal::base_class<Component>(this),
			CEREAL_NVP(m_modelPath),
			CEREAL_NVP(m_specular),
			CEREAL_NVP(m_color),
			CEREAL_NVP(m_shininess),
			CEREAL_NVP(m_shaderID),
			CEREAL_NVP(m_animationPaths),
			CEREAL_NVP(m_speed_animations),
			CEREAL_NVP(m_currentAnimations)
			);
	}

private:
	std::shared_ptr<Animator> m_animator;

	std::shared_ptr<AnimatedModel> m_model;
	std::vector<shared_ptr<Animation>> m_animations;


	std::string m_modelPath;
	std::vector<std::string> m_animationPaths;
	std::vector<float> m_speed_animations;

	int m_currentAnimations;

	glm::vec3 m_specular;
	glm::vec3 m_color;
	glm::vec3 m_fakeLight;
	float m_shininess;
	int m_shaderID;
};

CEREAL_REGISTER_TYPE(AnimatorComponent);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, AnimatorComponent);