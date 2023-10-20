#include "Transform.h"

Transform::Transform(std::shared_ptr<Transform> parentTransform)
{
	//std::cout << "Transform::Transform(std::shared_ptr<Transform> parentTransform)" << std::endl;


	isDirty = true;

	m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	//m_rot = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);// coœ by³o nie tak
	SetRotation(0.0f, 0.0f, 0.0f);// nowy sposób ustawiania domyœlnej rotacji
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	m_transformMat = glm::mat4(); // Domyœlnie bêdzie to macierz jednostkowa

	// TEST
	//glm::mat4 m_transformMat = glm::mat4(1.0f);
	//m_transformMat = glm::translate(m_transformMat, glm::vec3(0.0f, -1.0f, 0.0f)); // translate it down so it's at the center of the scene
	//m_transformMat = glm::scale(m_transformMat, glm::vec3(0.03f, 0.03f, 0.03f));	// it's a bit too big for our scene, so scale it down

	parentTR = parentTransform;
}

Transform::Transform()
{
	//std::cout << "Transform::Transform()" << std::endl;

	isDirty = true;

	m_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	//m_rot = glm::quat(0.0f, 0.0f, 0.0f, 1.0f);// coœ by³o nie tak
	SetRotation(0.0f, 0.0f, 0.0f); // nowy sposób ustawiania domyœlnej rotacji
	m_scale = glm::vec3(1.0f, 1.0f, 1.0f);

	m_transformMat = glm::mat4(); // Domyœlnie bêdzie to macierz jednostkowa

	// TEST
	//glm::mat4 m_transformMat = glm::mat4(1.0f);
	//m_transformMat = glm::translate(m_transformMat, glm::vec3(1.0f, -1.0f, 0.0f)); // translate it down so it's at the center of the scene
	//m_transformMat = glm::scale(m_transformMat, glm::vec3(0.03f, 0.03f, 0.03f));	// it's a bit too big for our scene, so scale it down


	//parentTR = std::make_shared<Transform>(nullptr);
	//parentTR.reset();
	//std::cout << "Transform::Transform() === koniec" << std::endl;
}

void Transform::SetUp()
{
	isDirty = true;
	Update();
}

void Transform::Input()
{
}

void Transform::Update()
{
	//std::cout << "isDirty = " << isDirty << std::endl;
	//std::cout << GetPosition().x << std::endl;

	//if(GetPosition().x == 5 && isDirty==true ) std::cout << "jep x5" << std::endl;


	if (parentTR != nullptr)
	{
		//std::cout << "parentIsDirty = " << parentTR->isDirty << std::endl;
		isDirty = isDirty || parentTR->isDirty; // jeœli siê poruszy³ obiekt lub jego rodzic
	}
	//std::cout << "isDirty||parent = " << isDirty << std::endl;

	if (isDirty)
	{
		glm::mat4 P = glm::translate(glm::mat4(1.0f), m_pos);
		glm::mat4 R = glm::mat4_cast(m_rot);
		glm::mat4 S = glm::scale(glm::mat4(1.0f), m_scale);
		
		m_transformMat = P * R * S;

		if (parentTR != nullptr)
			m_transformMat = parentTR->m_transformMat * m_transformMat;
	}
}

void Transform::Draw(std::shared_ptr<Transform> transform)
{
}

void Transform::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	std::string tmp = "[ Transform " + std::to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		glm::vec3 position = m_pos;
		glm::vec3 rotation = m_rotV3;
		glm::vec3 scale = m_scale;

		ImGui::InputFloat3("position", (float*)&position, "%.3f");
		ImGui::InputFloat3("rotation", (float*)&rotation, "%.3f");
		ImGui::InputFloat3("scale", (float*)&scale, "%.3f");

		if (m_pos != position)
			SetPosition(position);
		if (m_rotV3 != rotation)
			SetRotation(rotation / 57.2957794874f);// 2pi /360
		if (m_scale != scale)
			SetScale(scale);
	}
}

void Transform::IsDirtyFalse()
{
	isDirty = false;
}

glm::mat4 Transform::GetTransformMat()
{
	return m_transformMat;
}

void Transform::SetPosition(glm::vec3 position)
{
	m_pos = position;
	isDirty = true;
}

void Transform::SetAxisPosition(float pos, int axis)
{
	switch (axis)
	{
	case 1:
		m_pos.x = pos;
		break;
	case 2:
		m_pos.y = pos;
		break;
	case 3:
		m_pos.z = pos;
		break;
	default:
		break;
	}
	isDirty = true;
}

void Transform::SetRotation(glm::quat rotation)
{
	m_rotV3 = glm::eulerAngles(rotation) * 57.2957794874f; // 2pi /360

	m_rot = rotation;
	isDirty = true;
}

void Transform::SetRotation(float x, float y, float z)
{
	m_rotV3 = glm::vec3(x, y, z);

	m_rot = glm::angleAxis(glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::angleAxis(glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::angleAxis(glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
	isDirty = true;
}


void Transform::SetScale(glm::vec3 scale)
{
	m_scale = scale;
	isDirty = true;
}

glm::vec3 Transform::GetPosition()
{
	return m_pos;
}

glm::vec3 Transform::GetGlobalPosition()
{
	return m_transformMat * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
}

glm::quat Transform::GetRotation()
{
	return m_rot;
}

glm::vec3 Transform::GetScale()
{
	return m_scale;
}

// ---------------------------- TYMCZASOWE
glm::vec3 Transform::GetRotationEulerDeg()
{
	return m_rotV3;
}
void Transform::AddPosition(glm::vec3 vector)
{
	m_pos += vector;
	isDirty = true;
}
bool Transform::GetIsDirty()
{
	return isDirty;
}
void Transform::UpdateTransformMat()
{
	glm::mat4 P = glm::translate(glm::mat4(1.0f), m_pos);
	glm::mat4 R = glm::mat4_cast(m_rot);
	glm::mat4 S = glm::scale(glm::mat4(1.0f), m_scale);

	m_transformMat = P * R * S;

	if (parentTR != nullptr)
		m_transformMat = parentTR->m_transformMat * m_transformMat;
}
void Transform::SetParentTR(std::shared_ptr<Transform> transform)
{
	parentTR = transform;
}
void Transform::AddAxisRotation(float rotation, int axis)
{
	switch (axis)
	{
	case 1:
		m_rotV3.x += rotation;
		if (m_rotV3.x > 360) m_rotV3.x -= 360;
		else if (m_rotV3.x < -360) m_rotV3.x += 360;
		break;
	case 2:
		m_rotV3.y += rotation;
		if (m_rotV3.y > 360) m_rotV3.y -= 360;
		else if (m_rotV3.y < -360) m_rotV3.y += 360;
		break;
	case 3:
		m_rotV3.z += rotation;
		if (m_rotV3.z > 360) m_rotV3.z -= 360;
		else if (m_rotV3.z < -360) m_rotV3.z += 360;
		break;
	default:
		break;
	}

	m_rot = glm::angleAxis(glm::radians(m_rotV3.x), glm::vec3(1.0f, 0.0f, 0.0f)) *
		glm::angleAxis(glm::radians(m_rotV3.y), glm::vec3(0.0f, 1.0f, 0.0f)) *
		glm::angleAxis(glm::radians(m_rotV3.z), glm::vec3(0.0f, 0.0f, 1.0f));
	isDirty = true;
}
// ---------------------------- TYMCZASOWE
