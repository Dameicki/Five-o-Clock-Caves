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
	if (byObject == false) // bezpoœrednie w³¹czenie lub wy³¹czenie komponentu
	{
		if (newEnabled != enabled) // czy stan siê zmieni³
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
	else // Zmiana stanu wywo³ana zmian¹ stanu rodzica
	{
		if (newEnabled == true && enabled == true) // jeœli w³¹czam obiekt to w³¹czam jego aktywne komponenty
		{
			this->OnEnabled();
		}
		else if (newEnabled == false && enabled == true) // jeœli wy³¹czamy obiekt to wy³¹czamy jego aktywne komponenty
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

//Zwraca False po zakoñczeniu odliczania.  Repeat=true (powtórzy cykl) Repeat=false (zakoñczy cykl po 1 odliczeniu i bêdzie zwracaæ true)
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

