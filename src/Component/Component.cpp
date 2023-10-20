#include "Component.h"


Component::Component():enabled(true), type(0)
{
	delayStatus = 0;
	//enabled = true;
	//std::cout << "Component()" << std::endl;
}

void Component::SetGameObject(std::shared_ptr<GameObject> gameObject)
{
	m_gameObject = gameObject;
}

void Component::Load()
{
}

void Component::SetUp()
{
}

void Component::DrawToShadowMap(std::shared_ptr<Transform> transform)
{}

bool Component::GetEnabled()
{
	return enabled;
}

int Component::GetType()
{
	return type;
}

std::shared_ptr<GameObject> Component::GetOwner()
{
	return m_gameObject;
}

void Component::SetEnabled(bool newEnabled, bool byObject)
{
	if (byObject == false) // bezpo�rednie w��czenie lub wy��czenie komponentu
	{
		if (newEnabled != enabled) // czy stan si� zmieni�
		{
			enabled = newEnabled;
			if (enabled == true)
			{
				this->OnEnabled();
			}
			else
			{
				this->OnDisabled();
			}
		}
	}
	else // Zmiana stanu wywo�ana zmian� stanu rodzica
	{
		if (newEnabled == true && enabled == true) // je�li w��czam obiekt to w��czam jego aktywne komponenty
		{
			this->OnEnabled();
		}
		else if (newEnabled == false && enabled == true) // je�li wy��czamy obiekt to wy��czamy jego aktywne komponenty
		{
			this->OnDisabled();
		}
	}
	
}

void Component::Input()
{
}

void Component::Update()
{
}

void Component::Trigger(std::shared_ptr<CollisionResult> collResult)
{
}

void Component::Collision(std::shared_ptr<CollisionResult> collResult)
{
}

void Component::Draw(std::shared_ptr<Transform> transform)
{
}

void Component::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	//ImGui::
}

std::shared_ptr<Component> Component::GetCopyComponent()
{
	std::shared_ptr<Component> copyComponent = std::make_shared<Component>();
	copyComponent->enabled = this->enabled;
	return copyComponent;
}

void Component::OnEnabled()
{
}

void Component::OnDisabled()
{
}

//Zwraca False po zako�czeniu odliczania.  Repeat=true (powt�rzy cykl) Repeat=false (zako�czy cykl po 1 odliczeniu i b�dzie zwraca� true)
bool Component::Delay(float timer, bool repeat) {
	if (delayStatus==0) 
	{
		timeLeft = timer;
		delayStatus = 1;
		return true;
	}
	if (delayStatus==1)
	{
		timeLeft = timeLeft - TIME.GetDeltaTime();
		if (timeLeft <= 0) 
		{
			delayStatus = 2;
			timeLeft = NULL;
			if (repeat)
			{
				delayStatus = 0;
			}
			return false;
		}
		return true;
	}
	if (delayStatus == 3)
	{
		delayStatus = 0;
		return false;
	}
	return true;
}

void Component::ClearDelay()
{
	delayStatus = 3;
}

