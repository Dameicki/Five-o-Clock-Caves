#include "MeshRenderer.h"

MeshRenderer::MeshRenderer()
{
	//m_model = std::make_shared<Model>(nullptr);
	type = MESH_RENDERER;
}

MeshRenderer::MeshRenderer(std::string path, int shaderID, glm::vec3 color, float shininess, glm::vec3 specular):
	m_shaderID(shaderID), m_color(color), m_shininess(shininess), m_specular(specular), m_modelPath(path)
{
	type = MESH_RENDERER;
	SetModel(path);
}

//MeshRenderer::MeshRenderer(std::string path, glm::vec3 color, float shininess, glm::vec3 specular)
//{
//	m_color= color;
//	m_shininess=shininess;
//	m_specular = specular;
//
//	SetModel(path);
//}

void MeshRenderer::Load()
{
	SetModel(m_modelPath);
}

void MeshRenderer::SetUp()
{
	type = MESH_RENDERER;

	glm::mat2x3 boundingBox = m_model->GetBoundingBox();
	
	glm::vec3 size = glm::vec3(boundingBox[0][0], boundingBox[0][1], boundingBox[0][2]);
	glm::vec3 center = glm::vec3(boundingBox[1][0], boundingBox[1][1], boundingBox[1][2]);
	size *= m_gameObject->m_transform->GetScale();
	float radius = glm::sqrt((size.x * size.x + size.z * size.z) + size.y * size.y)/2;
	m_gameObject->m_boundingSphere->SetParameters(glm::vec4(center, radius));
	m_gameObject->SetBSSetup(true);
}

void MeshRenderer::Input()
{
}

void MeshRenderer::Update()
{
	
}

void MeshRenderer::Draw(std::shared_ptr<Transform> transform)
{
	if (m_model != nullptr)
	{

		ShaderSystem::GetInstance().Draw(m_model, transform->GetTransformMat(), m_shaderID, m_color, m_shininess, m_specular);
	}
}

void MeshRenderer::DrawToShadowMap(std::shared_ptr<Transform> transform)
{
	if (m_model != nullptr)
	{
		ShaderSystem::GetInstance().DrawToShadowMap(m_model, transform->GetTransformMat(), false);
	}

}

std::shared_ptr<Component> MeshRenderer::GetCopyComponent()
{
	std::shared_ptr<Component> copyComponent = std::make_shared<MeshRenderer>(m_modelPath, m_shaderID, m_color, m_shininess, m_specular);
	//copyComponent->enabled = this->enabled;
	return copyComponent;
}

void MeshRenderer::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	string tmp = "[ MeshRenderer " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{																								
		bool enabledTMP = enabled;	// stan w³¹cznika												
		ImGui::Checkbox("enabled", &enabledTMP); 													
																										
		ImGui::ColorEdit3("specular", (float*)&m_specular);											
		ImGui::ColorEdit3("color", (float*)&m_color);												
		ImGui::InputFloat("shininess", (float*)&m_shininess);										
				
		static const char* items[]{ "default", "lightSource", "color", "box", "sprite", "sphere", "depth", "animated", 
			"world","button","debugQuad","depthAnimated", "colorFresnel","animatedFresnel","defaultNoLights" };
		ImGui::ListBox("shader", &m_shaderID, items, IM_ARRAYSIZE(items));



		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan w³¹cznika

		if (ImGui::BeginMenu("model"))
		{
			for (auto& modelPath : RESOURCE.modelPathsList)
			{
				bool greenColor = false;
				if (m_modelPath == modelPath)		 // zmian koloru wybranego modelu
				{
					ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.8f, 0.1f, 1.0f });
					greenColor = true;
				}

				if (ImGui::Button(modelPath.c_str()))
				{
					SetModel(modelPath);
					m_modelPath = modelPath;
				}

				if (greenColor)  ImGui::PopStyleColor();
			}

			ImGui::EndMenu();
		}
	}
}

void MeshRenderer::SetModel(std::string path)
{
	m_model = RESOURCE.GetModel(path);
}

void MeshRenderer::SetColor(glm::vec3 newColor)
{
	m_color = newColor;
}
