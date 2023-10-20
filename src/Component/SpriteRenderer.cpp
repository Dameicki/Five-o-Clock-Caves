#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::SpriteRenderer(std::string path, int shaderID): m_texturePath(path), m_shaderID(shaderID)
{
}

void SpriteRenderer::Load()
{
	SetTexture(m_texturePath);
}

void SpriteRenderer::SetUp()
{
	glm::vec3 size = glm::vec3(1.0f);
	glm::vec3 center = glm::vec3(0.0f);
	size *= m_gameObject->m_transform->GetScale();
	float radius = glm::sqrt((size.x * size.x + size.z * size.z) + size.y * size.y); // Obrot billborda zrobiony w shaderze nieobraca go poprawnie wiec daje mu 2 razy wiekszy promień by nieznikał z ekranu za prędko
	m_gameObject->m_boundingSphere->SetParameters(glm::vec4(center, radius));
	m_gameObject->SetBSSetup(true);
}

void SpriteRenderer::Draw(std::shared_ptr<Transform> transform)
{
	ShaderSystem::GetInstance().DrawSprite(m_texture, transform->GetTransformMat(), m_shaderID);
}

void SpriteRenderer::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	bool enabledTMP = enabled;	// stan w³¹cznika
	ImGui::Checkbox("=== [ SpriteRenderer ] ===", &enabledTMP); // nawa jest tu

	static const char* items[]{ "default", "lightSource", "color", "box", "sprite" };

	ImGui::Combo("shader", &m_shaderID, items, IM_ARRAYSIZE(items));

	this->SetEnabled(enabledTMP);			// metoda która reaguje na stan w³¹cznika
}

void SpriteRenderer::SetTexture(std::string path)
{
	m_texture = RESOURCE.GetTexture(path);
}
