#include "AnimatorComponent.h"

AnimatorComponent::AnimatorComponent()
{
	type = ANIMATOR;
}

AnimatorComponent::AnimatorComponent(std::string modelPath, std::vector<std::string> animationPaths, std::vector<float> speed_animations, int shaderID, int currentAnimations, glm::vec3 color, float shininess, glm::vec3 specular) :
	m_shaderID(shaderID), m_color(color), m_shininess(shininess), m_specular(specular), m_modelPath(modelPath), m_animationPaths(animationPaths), m_currentAnimations(currentAnimations), m_speed_animations(speed_animations)
{
	SetModel(modelPath);

	m_animations = vector<shared_ptr<Animation>>();
	for (auto path : animationPaths)
	{
		AddAnimation(path);
	}

	m_animator = make_shared<Animator>(Animator(m_animations[0]));
	type = ANIMATOR;
}

void AnimatorComponent::Load()
{
	SetModel(m_modelPath);

	m_animations = vector<shared_ptr<Animation>>();
	for (auto path : m_animationPaths)
	{
		AddAnimation(path);
	}

	m_animator = make_shared<Animator>(Animator(m_animations[0]));
	type = ANIMATOR;
}

void AnimatorComponent::SetUp()
{
	m_fakeLight = glm::vec3(0.5f);

	glm::mat2x3 boundingBox = m_model->GetBoundingBox();

	glm::vec3 size = glm::vec3(boundingBox[0][0], boundingBox[0][1], boundingBox[0][2]);
	glm::vec3 center = glm::vec3(boundingBox[1][0], boundingBox[1][1], boundingBox[1][2]);
	size *= m_gameObject->m_transform->GetScale();
	float radius = glm::sqrt((size.x * size.x + size.z * size.z) + size.y * size.y) / 2;
	m_gameObject->m_boundingSphere->SetParameters(glm::vec4(center, radius));
	m_gameObject->SetBSSetup(true);
}

void AnimatorComponent::Input()
{

}

void AnimatorComponent::Update()
{
	m_animator->UpdateAnimation(TIME.GetDeltaTime() * m_speed_animations[m_currentAnimations]);
}

void AnimatorComponent::Draw(std::shared_ptr<Transform> transform)
{
	Shader& shader = ShaderSystem::GetInstance().shaderObjects[m_shaderID].GetShader();
	shader.use();

	shader.setVec3("material.fakeLight", m_fakeLight);

	std::vector<glm::mat4> transforms = m_animator->GetPoseTransforms();
	for (int i = 0; i < transforms.size(); ++i)
		shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

	if (m_model != nullptr)
	{
		ShaderSystem::GetInstance().Draw(m_model, transform->GetTransformMat(), m_shaderID, m_color, m_shininess, m_specular);
	}
}

void AnimatorComponent::DrawToShadowMap(std::shared_ptr<Transform> transform)
{ 
	Shader& shader = ShaderSystem::GetInstance().shaderObjects[11].GetShader();
	shader.use();
	
	std::vector<glm::mat4> transforms = m_animator->GetPoseTransforms();
	for (int i = 0; i < transforms.size(); ++i)
		shader.setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);

	if (m_model != nullptr)
	{
		ShaderSystem::GetInstance().DrawToShadowMap(m_model, transform->GetTransformMat(), true);
	}
}

void AnimatorComponent::PlayAnimation(int animation)
{
	if(animation != m_currentAnimations)
	{
		m_currentAnimations = animation % m_animationPaths.size();
		m_animator->PlayAnimation(m_animations[m_currentAnimations]);
	}
}

void AnimatorComponent::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	string tmp = "[ AnimatorComponent " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		bool enabledTMP = enabled;	// stan w³¹cznika												
		ImGui::Checkbox("enabled", &enabledTMP);

		ImGui::ColorEdit3("specular", (float*)&m_specular);
		ImGui::ColorEdit3("color", (float*)&m_color);
		ImGui::ColorEdit3("fakeLight", (float*)&m_fakeLight);
		ImGui::InputFloat("shininess", (float*)&m_shininess);

		int animationClip = m_currentAnimations;
		ImGui::InputInt("currentAnimation", (int*)&animationClip);
		if (animationClip != m_currentAnimations)
		{
			m_currentAnimations = animationClip % m_animationPaths.size();
			m_animator->PlayAnimation(m_animations[m_currentAnimations]);
		}

		//static const char* items[]{ "default", "lightSource", "color", "box", "sprite", "sphere", "depth", "animated" };
		static const char* items[]{ "default", "lightSource", "color", "box", "sprite", "sphere", "depth", "animated", "world","button","debugQuad","depthAnimated", "colorFresnel","animatedFresnel" };

		ImGui::Combo("shader", &m_shaderID, items, IM_ARRAYSIZE(items));

		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan w³¹cznika
	}
}

void AnimatorComponent::SetModel(std::string path)
{
	m_model = RESOURCE.GetAnimatedModel(path);
}

void AnimatorComponent::AddAnimation(std::string path)
{
	m_animations.push_back(RESOURCE.GetAnimation(path, m_model));
}

void AnimatorComponent::SetPowerUPShader(int powerUp)
{
	switch (powerUp)
	{
	case 0:
		m_specular = glm::vec3(0.0f);
		m_shaderID = 7;
		break;

	case 1:
		m_specular = glm::vec3(0.0f,0.1f,0.0f);
		m_shaderID = 13;
		break;

	case 2:
		m_specular = glm::vec3(0.1f, 0.0f, 0.0f);
		m_shaderID = 13;
		break;

	default:
		m_specular = glm::vec3(0.0f);
		m_shaderID = 7;
		break;
	}
}
