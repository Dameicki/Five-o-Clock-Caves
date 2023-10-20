#include "BoundingSphere.h"

BoundingSphere::BoundingSphere()
{
	_centerOffset = glm::vec3(0.0f);
	_radius = 0.0f;
}

BoundingSphere::BoundingSphere( float radius): _radius(radius)
{
	_centerOffset = glm::vec3(0.0f);
}

void BoundingSphere::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	// wyświetlanie sfery w edytorze
	glm::mat4 centerTransform = glm::translate(m_gameObject->m_transform->GetTransformMat(), _centerOffset);
	ShaderSystem::GetInstance().DrawByGeometrySphere(centerTransform, 5, glm::vec3(1.0f), 30, _radius);

	string tmp = "[ Bounding Sphere " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		ImGui::InputFloat("Radius", (float*)&_radius);
		ImGui::InputFloat3("Center Offset", (float*)&_centerOffset, "%.3f");
	}

	//if (m_gameObject != nullptr)
	//{
	//	glm::mat4 centerTransform = glm::translate(m_gameObject->m_transform->GetTransformMat(), _centerOffset);
	//	ShaderSystem::GetInstance().DrawByGeometrySphere(centerTransform, 5, glm::vec3(1.0f), 30, _radius);
	//}
}

void BoundingSphere::SetParameters(glm::vec4 properties)
{
	_centerOffset = glm::vec3(properties.x, properties.y, properties.z);
	_radius = properties.w;
}

void BoundingSphere::SetRadius(float radius)
{
	_radius = radius;
}

void BoundingSphere::SetCenterOffset(glm::vec3 centerOffset)
{
	_centerOffset = centerOffset;
}

glm::vec3 BoundingSphere::GetCenterOffset()
{
	return _centerOffset;
}

float BoundingSphere::GetRadius()
{
	return _radius;
}
