#include "GooldDoorInteract.h"
#include "CameraController.h"

GooldDoorInteract::GooldDoorInteract()
{
	type = DOOR_COMP;
	_nextLevelPath = "res\\scenes\\Scene.xml";
}

GooldDoorInteract::GooldDoorInteract(string nextLevelPath) : _nextLevelPath(nextLevelPath)
{
	type = DOOR_COMP;
}

void GooldDoorInteract::SetUp()
{
	list<shared_ptr<CameraController>> tmp = GameObject::GetRootObject(m_gameObject)->GetComponentsListInChildren<CameraController>(CAMERA_CONTROLLER);
	for (auto& camera : tmp)
	{
		cameraController = camera;
	}

	doorOpen = false;

	DoorInteract::SetUp();
}

void GooldDoorInteract::Update()
{
	if (doorOpen == false)
	{
		DoorInteract::Update();
	}
	else
	{
		//Delay(5000.0f, false);
		if (!Delay(7.0f, false))
		{
			RESOURCE.PrepereLoadScen(_nextLevelPath, GameObject::GetRootObject(m_gameObject));
		}
	}
}

void GooldDoorInteract::OpenDoor()
{
	//cout << "Otworzyles zlote drzwi" <<endl;
	//cout << "GameObject::GetRootObject(m_gameObject)->m_name = " << GameObject::GetRootObject(m_gameObject)->m_name << endl;

	doorOpen = true;
	cameraController->LevelComplet();
}

std::shared_ptr<Component> GooldDoorInteract::GetCopyComponent()
{
	std::shared_ptr<Component> copyComponent = std::make_shared<GooldDoorInteract>(GooldDoorInteract(_nextLevelPath));

	return copyComponent;
}

void GooldDoorInteract::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	string tmp = "[ GooldDoorInteract " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		bool enabledTMP = enabled;	// stan w³¹cznika												
		ImGui::Checkbox("enabled", &enabledTMP);

		// zmiana œcierzki
		//int n = _nextLevelPath.length();
		char newName[128];
		strcpy(newName, _nextLevelPath.c_str());
		ImGui::InputText("Name", newName, 35); //IM_ARRAYSIZE(newObjectName)
		_nextLevelPath = newName;

		ImGui::Text(cameraController->GetOwner()->m_name.c_str());

		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan w³¹cznika
	}
}
