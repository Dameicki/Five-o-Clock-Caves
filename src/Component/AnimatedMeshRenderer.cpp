#include "AnimatedMeshRenderer.h"

AnimatedMeshRenderer::AnimatedMeshRenderer()
{
	m_model = std::make_shared<AnimatedModel>(nullptr);
}

AnimatedMeshRenderer::AnimatedMeshRenderer(std::string path, int shaderID, glm::vec3 color, float shininess, glm::vec3 specular) :
	m_shaderID(shaderID), m_color(color), m_shininess(shininess), m_specular(specular)
{
	SetModel(path);
}

void AnimatedMeshRenderer::Draw(std::shared_ptr<Transform> transform)
{
	if (m_model != nullptr)
	{
		//ShaderSystem::GetInstance().DrawAnimated(m_model, transform->GetTransformMat(), m_shaderID, m_color, m_shininess, m_specular); // TO DO shader system musi ogarniaæ rysowanie animowanego modelu
	}
}

void AnimatedMeshRenderer::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	bool enabledTMP = enabled;	// stan w³¹cznika
	ImGui::Checkbox("=== [ AnimatedMeshRenderer ] ===", &enabledTMP); // nawa jest tu

	ImGui::ColorEdit3("specular", (float*)&m_specular);
	ImGui::ColorEdit3("color", (float*)&m_color);
	//ImGui::SliderFloat3("color", (float*)&m_color, 0.0f, 1.0f);
	//ImGui::SliderFloat3("specular", (float*)&m_specular, 0.0f, 1.0f);
	ImGui::InputFloat("shininess", (float*)&m_shininess);

	static const char* items[]{ "default", "lightSource", "color", "box", "sprite", "animation"};

	ImGui::Combo("shader", &m_shaderID, items, IM_ARRAYSIZE(items));

	this->SetEnabled(enabledTMP);			// metoda która reaguje na stan w³¹cznika

}

void AnimatedMeshRenderer::SetModel(std::string path)
{
	//m_model = RESOURCE.GetModel(path);
	m_model = std::make_shared<AnimatedModel>(AnimatedModel(path));
}
