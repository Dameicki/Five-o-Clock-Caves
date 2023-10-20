#include "DoorInteract.h"
#include "./ActionDoor.h"
#include "Level.h"
#include "AllPlayers.h"

DoorInteract::DoorInteract()
{
	type = DOOR_COMP;
}

DoorInteract::DoorInteract(glm::vec3 teleportDir): _teleportDir(teleportDir)
{
	type = DOOR_COMP;
}

void DoorInteract::OpenDoor()
{

	// teleportacja graczy
	_player->m_parent->m_transform->AddPosition(_teleportDir);

	// usuwanie powerUpow
	_player->m_parent->GetComponent<AllPlayers>(ALL_PLAYERS)->RemovePowers();

	// prze³¹czenie œwiate³ 
	m_gameObject->m_parent->GetComponent<Level>(LEVEL)->LightsOff();
	_targetLevel->LightsOn();
	m_gameObject->GetRootObject(m_gameObject)->GetComponent<Scene>(SCENE)->SetCurrentRoom(_targetLevel->GetOwner());
}

void DoorInteract::Update()
{
	if (!_usedLastFrame)
	{
		_usedLastFrame = false;
		if (_pressE == true) // czy ktoœ klikno³ przycisk interakcji
		{
			if (_playersIn == 2) // czy jest 2 graczy
			{
				shared_ptr<ActionDoor> actionDoor = m_gameObject->GetComponent<ActionDoor>(ACTION_DOOR);
				if (actionDoor == nullptr) // jeœli nie ma komponentu od blokowania drzwi
				{
					AUDIO.playEffect("res/audio/door.mp3", 0.25f);
					OpenDoor();
					_usedLastFrame = true;
					//Delay(2, false);
				}
				else if (actionDoor->GetLocked() == false) // jeœli komponent od blokowania drzwi ma _locked == false
				{
					AUDIO.playEffect("res/audio/door.mp3", 0.25f);
					OpenDoor();
					_usedLastFrame = true;
					//Delay(2, false);
				}
			}
		}
	}
	else _usedLastFrame = false;
	

	ChangeCubs();

	_pressE = false;
	_playersIn = 0;
}

void DoorInteract::SetUp()
{
	_cubes = m_gameObject->GetComponentsListInChildren<MeshRenderer>(MESH_RENDERER);
	_cubes.pop_front(); // usuwanie mesha drzwi z listy cubels
	_lastPlayerIn = 0;
}

void DoorInteract::Trigger(std::shared_ptr<CollisionResult> collResult)
{
	if (collResult->GetObjectA()->GetCollisionLayer() == CollisionLayer::PLAYER)
	{
		_playersIn++;
		//cout << "gracz przy drzwiach (_playersIn = " <<_playersIn<< ")" << endl;
	}
}

void DoorInteract::Interact(std::shared_ptr<GameObject> player)
{
	_player = player;
	_pressE = true;
}

std::shared_ptr<Component> DoorInteract::GetCopyComponent()
{
	std::shared_ptr<Component> copyComponent = std::make_shared<DoorInteract>(DoorInteract(_teleportDir));

	return copyComponent;
}

void DoorInteract::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	string tmp = "[ DoorInteract " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		bool enabledTMP = enabled;	// stan w³¹cznika												
		ImGui::Checkbox("enabled", &enabledTMP);

		ImGui::InputFloat3("teleportDir", (float*)&_teleportDir, "%.3f");
		if (_targetLevel != nullptr)
		{
			tmp = "taget level: " + _targetLevel->GetOwner()->m_name;
			ImGui::Text(tmp.c_str());
		}
		if (ImGui::Button("Set New Target Level"))
			_targetLevel = dynamic_pointer_cast<Level>(imguiSystem->GetSavedComponent());

		if (ImGui::Button(" Refresh Cube List  "))
			SetUp();

		for (auto& cube : _cubes)
		{
			ImGui::Text(cube->GetOwner()->m_name.c_str());
		}

		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan w³¹cznika
	}
}

void DoorInteract::ChangeCubs()
{
	if (_lastPlayerIn != _playersIn)
	{
		int i = 0;
		for (auto& cube : _cubes)
		{
			if (i < 2) // bo jest 2 graczy
			{
				if (i < _playersIn) // dla tylu kostek ilu jest graczy przy drzwiach
				{
					cube->SetColor(glm::vec3(1.0f)); // kostka siê œwieci
				}
				else
				{
					cube->SetColor(glm::vec3(0.2f)); // kostka siê nie œwieci
				}
			}
			i++;
		}
	}

	_lastPlayerIn = _playersIn;
}
