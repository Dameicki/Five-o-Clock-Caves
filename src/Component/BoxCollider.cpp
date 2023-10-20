#include "BoxCollider.h"

BoxCollider::BoxCollider(glm::vec3 centerOffset, glm::vec3 size, bool isStatic, bool isTrigger, CollisionLayer collisionLayer):
						_centerOffset(centerOffset), _size(size), _isStatic(isStatic), _isTrigger(isTrigger), _collisionLayer(collisionLayer)
{
	type = BOX_COLLIDER;
}

void BoxCollider::SetUp()
{
	if (_isStatic) {
		if (!_isTrigger)
		{
			_color = glm::vec3(1.0f, 1.0f, 0.0f);
		}
		else
		{
			_color = glm::vec3(0.0f, 0.0f, 1.0f);
		}
		COLLISION.AddStaticObject(shared_from_this());
	}
	else COLLISION.AddDynamicObject(shared_from_this());
}

void BoxCollider::Input()
{
}

void BoxCollider::Update()
{
	if (m_gameObject->m_transform->GetIsDirty()==true)
	{
		//std::cout << m_gameObject->m_name << std::endl;
		_centerPosition = m_gameObject->m_transform->GetGlobalPosition() + _centerOffset;
		_centerTransform = glm::translate(glm::mat4(1.0f), _centerPosition);
	}
}

void BoxCollider::Draw(std::shared_ptr<Transform> transform)
{
	ShaderSystem::GetInstance().DrawByGeometry(_centerTransform, 3, _color, 10, _size);
}

void BoxCollider::OnEnabled()
{
	SetUp();
}

void BoxCollider::OnDisabled()
{
	COLLISION.RemoveCollider(shared_from_this(),!_isStatic);
}

std::shared_ptr<Component> BoxCollider::GetCopyComponent()
{
	std::shared_ptr<Component> copyComponent = std::make_shared<BoxCollider>(BoxCollider(_centerOffset, _size, _isStatic, _isTrigger, _collisionLayer));
	//copyComponent->enabled = this->enabled;
	return copyComponent;
}

void BoxCollider::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	string tmp = "[ BoxCollider " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		bool enabledTMP = enabled;	// stan włącznika
		ImGui::Checkbox("enabled", &enabledTMP);

		tmp = "Static" + to_string(index);
		ImGui::Checkbox(tmp.c_str(), &_isStatic);
		tmp = "Trigger" + to_string(index);
		ImGui::Checkbox(tmp.c_str(), &_isTrigger);
		tmp = "Center" + to_string(index);
		ImGui::InputFloat3(tmp.c_str(), (float*)&_centerOffset, "%.3f");
		tmp = "Size" + to_string(index);
		ImGui::InputFloat3(tmp.c_str(), (float*)&_size, "%.3f");
		tmp = "Layer" + to_string(index);
		ImGui::InputInt(tmp.c_str(), (int*)&_collisionLayer);

		tmp = "Refresh" + to_string(index);
		if (ImGui::Button(tmp.c_str()))
		{
			//std::cout << m_gameObject->m_name << std::endl;
			_centerPosition = m_gameObject->m_transform->GetGlobalPosition() + _centerOffset;
			_centerTransform = glm::translate(glm::mat4(1.0f), _centerPosition);
		}

		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan włącznika
	}

	ShaderSystem::GetInstance().DrawByGeometry(_centerTransform, 3, glm::vec3(1.0f, 1.0f, 1.0f), 10, _size+glm::vec3(0.2f));
}

glm::vec3 BoxCollider::GetCenterPos()
{
	return _centerPosition;
}

glm::vec3 BoxCollider::GetSize()
{
	return _size;
}

bool BoxCollider::GetIsTrigger()
{
	return _isTrigger;
}

CollisionLayer BoxCollider::GetCollisionLayer()
{
	return _collisionLayer;
}

void BoxCollider::SetColor(glm::vec3 color)
{
	_color = color;
}

void BoxCollider::SetIsStatic(bool state)
{
	_isStatic = state;
}

void BoxCollider::SetIsTrigger(bool state)
{
	_isTrigger = state;
}

void BoxCollider::SetCollisionLayer(CollisionLayer layer)
{
	_collisionLayer = layer;
}

void BoxCollider::UpdateCollider()
{
	m_gameObject->m_transform->UpdateTransformMat();
	_centerPosition = m_gameObject->m_transform->GetGlobalPosition() + _centerOffset;
	_centerTransform = glm::translate(m_gameObject->m_transform->GetTransformMat(), _centerOffset);
}

void BoxCollider::CallCollision(std::shared_ptr<CollisionResult> collisionResult)
{
	m_gameObject->Collision(collisionResult);
	Update();
	//m_gameObject->m_transform->IsDirtyFalse();
}

void BoxCollider::CallTrigger(std::shared_ptr<CollisionResult> collisionResult)
{
	m_gameObject->Trigger(collisionResult);
}
