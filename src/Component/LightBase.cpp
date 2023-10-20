#include "LightBase.h"

LightBase::LightBase()
{
	id = -1;
	//cout << "=== 1 LightBase()" << endl;
}

LightBase::LightBase(LightType lightType): lightType(lightType), id(-1)
{
	id = -1;
	//cout << "=== 2 LightBase()" << endl;
}

LightBase::LightBase(LightType type, glm::vec3 color) : lightType(type), m_color(color)
{
	id = -1;
	//cout << "=== 3 LightBase()" << endl;
}

int LightBase::GetID()
{
	return id;
}

void LightBase::SetID(int newID)
{
	id = newID;
}

void LightBase::SetUp()
{
	//SetEnabled(true, true); // w³¹czy tylko aktywne komponnty
	//if(enabled == true)
	LIGHTS.AddLight(shared_from_this(), lightType);
	switch (lightType)
	{
	case point:
		type = POINT_LIGHT;
		break;
	case spot:
		type = SPOT_LIGHT;
		break;
	case dir:
		type = DIR_LIGHT;
		break;
	default:
		break;
	}
}

void LightBase::Input()
{
}

void LightBase::Update()
{
}

void LightBase::Draw(std::shared_ptr<Transform> transform)
{
}

bool LightBase::FrustumCulling()
{
	//visible = FRUSTUM.CheckSphereIntersection(m_gameObject->m_transform->GetGlobalPosition() + m_gameObject->m_boundingSphere->GetCenterOffset(), m_gameObject->m_boundingSphere->GetRadius());
	visible = FRUSTUM.CheckSphereIntersection(m_gameObject->m_transform->GetGlobalPosition() + m_gameObject->m_boundingSphere->GetCenterOffset(), 1);
	return visible;
}

void LightBase::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
}

void LightBase::OnEnabled()
{
	LIGHTS.AddLight(shared_from_this(), lightType);
}

void LightBase::OnDisabled()
{
	LIGHTS.RemoveLight(shared_from_this(), lightType);
}
