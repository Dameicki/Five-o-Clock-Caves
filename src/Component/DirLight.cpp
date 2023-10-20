#include "DirLight.h"

DirLight::DirLight(glm::vec3 direction, 
    glm::vec3 color,  glm::vec3 ambient,
    glm::vec3 specular)
{
    m_direction = direction;
    m_color = color;
    m_ambient = ambient;
    m_specular = specular;
    lightType = dir;

}

DirLight::DirLight()
{
    m_direction = glm::vec3(0.0f, -1.0f, 0.0f);
    m_color = glm::vec3(0.0f);
    m_ambient = glm::vec3(0.02f);
    m_specular = glm::vec3(1.0f);
    lightType = dir;
}

void DirLight::Input()
{
    
}

void DirLight::Update()
{
    glm::mat4 lightSpaceMatrix = glm::ortho(-20.0f, 20.0f, -20.0f, 20.0f, -10.0f, 100.0f) * 
        glm::lookAt(m_gameObject->m_transform->GetGlobalPosition(),
            m_gameObject->m_transform->GetGlobalPosition() + m_direction, 
            glm::vec3(0.0f, 1.0f, 0.0f));

    ShaderSystem::GetInstance().UniformDirLight(m_direction, m_color, m_specular, m_ambient, enabled, lightSpaceMatrix);

}

void DirLight::Draw(std::shared_ptr<Transform> transform)
{
}

void DirLight::SetUp()
{
    if (enabled)
        LightBase::SetUp();
}

std::shared_ptr<Component> DirLight::GetCopyComponent()
{
    std::shared_ptr<Component> copyComponent = std::make_shared<DirLight>(DirLight(m_direction, m_color, m_ambient, m_specular));
    return copyComponent;
}

void DirLight::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");		// Odstêp

	string tmp = "[ Directional Light " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		bool enabledTMP = enabled;	// stan w³¹cznika
		ImGui::Checkbox("enabled", &enabledTMP);

		ImGui::ColorEdit3("light color", (float*)&m_color);			// parametry kmponentu
		ImGui::ColorEdit3("light specular", (float*)&m_specular);	// parametry kmponentu
		ImGui::DragFloat3("direction", (float*)&m_direction, .01f, -1.0f, 1.0f );	// parametry kmponentu
		
		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan w³¹cznika
	}

}
