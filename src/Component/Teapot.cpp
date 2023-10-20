#include "Teapot.h"
#include "PlayerController.h"

Teapot::Teapot()
{
	type = TEAPOT;
	_teaType = NONE_EFFECT;
	_colors = vector<glm::vec3>();
}

Teapot::Teapot(TeaType teaType, vector<glm::vec3> colors) : _colors(colors), _teaType(teaType)
{
	type = TEAPOT;
}

void Teapot::SetUp()
{
	_meshRenderer = m_gameObject->GetComponent<MeshRenderer>(MESH_RENDERER);

	list<shared_ptr<MeshRenderer>> cubes = m_gameObject->GetComponentsListInChildren<MeshRenderer>(MESH_RENDERER);
	cubes.pop_front(); // usuwanie mesha czajnika z listy cubels

	for (auto& cube : cubes)// ostatni mesh renderer będzie cubem
	{						// ostatni mesh renderer będzie cubem
		_cube = cube; 		// ostatni mesh renderer będzie cubem
	}
}


void Teapot::Update()
{
	if (_cube != nullptr) _cube->SetColor(glm::vec3(0.2f));
}

void Teapot::Trigger(std::shared_ptr<CollisionResult> collResult)
{
	// ZMIANA KOLORU I MOCY CZAJNIKA
	if (collResult->GetObjectA()->GetCollisionLayer() == LEAF)
	{
		//cout << "A: Zebatka w poblizu" << endl;
		collResult->GetObjectA()->GetOwner()->SetEnabled(false);
		SetTea(collResult->GetObjectA()->GetOwner()->GetComponent<Leaf>(LEAF_COMP)->GetTeaType());
	}
	else if (collResult->GetObjectB()->GetCollisionLayer() == LEAF) // ZMIANA KOLORU I MOCY CZAJNIKA
	{
		//cout << "B: Zebatka w poblizu" << endl;
		collResult->GetObjectB()->GetOwner()->SetEnabled(false);
		SetTea(collResult->GetObjectB()->GetOwner()->GetComponent<Leaf>(LEAF_COMP)->GetTeaType());
	}

	// Podświetlanie cuba pod czajnikiem
	if (collResult->GetObjectA()->GetCollisionLayer() == PLAYER) 
	{
		if (_teaType == NONE_EFFECT)// jeśli nie ma mocy w czajniku
		{
			// Sprawdzanie czy gracz trzyma liść
			shared_ptr<PlayerInteraction> playerInteraction = collResult->GetObjectA()->GetOwner()->GetComponent<PlayerInteraction>(PLAYER_INTERACTION);
			if (playerInteraction->GetInteractableObject() != nullptr)
			{
				if (playerInteraction->GetInteractableObject()->GetType() == LEAF_COMP)
				{
					if (_cube != nullptr)
					{
						_cube->SetColor(glm::vec3(1.0f));
					}
				}
			}
		}
		else 
		{
			if (_cube != nullptr)
			{
				_cube->SetColor(glm::vec3(1.0f));
			}
		}
		
	}
}


void Teapot::Interact(std::shared_ptr<GameObject> player)
{
	// DAWANIE POWERUPA
	switch (_teaType)
	{
	case JUMP:
		player->GetComponent<PlayerController>(PLAYER_CONTROLLER)->SetJumps(2);
		AUDIO.playEffect("res/audio/tea.ogg", 0.25f);
		break;
	case STRENTH:
		player->GetComponent<PlayerController>(PLAYER_CONTROLLER)->SetPushForce(100);
		AUDIO.playEffect("res/audio/tea.ogg", 0.25f);
		break;
	case NONE_EFFECT:
		player->GetComponent<PlayerController>(PLAYER_CONTROLLER)->SetPowerUP(0);
		break;
	default:
		break;
	}
}

std::shared_ptr<Component> Teapot::GetCopyComponent()
{
	std::shared_ptr<Component> copyComponent = std::make_shared<Teapot>(Teapot(_teaType,_colors));
	return copyComponent;
}


void Teapot::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	string tmp = "[ Teapot " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		bool enabledTMP = enabled;	// stan włącznika												
		ImGui::Checkbox("enabled", &enabledTMP);

		for (int i = 0; i < _colors.size(); i++)
		{
			tmp = "color" + i;
			ImGui::ColorEdit3(tmp.c_str(), (float*)&_colors[i]);
		}

		if (ImGui::Button("RemovePower"))
		{
			_teaType = NONE_EFFECT;
			_meshRenderer->SetColor(glm::vec3(0.8f));
		}

		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan włącznika
	}
}

void Teapot::SetTea(TeaType teaType)
{
	_teaType = teaType;
	AUDIO.playEffect("res/audio/prepareTea.ogg", 0.25f, 2.0f);
	switch (teaType)
	{
	case JUMP:
		_meshRenderer->SetColor(_colors[0]);
		break;
	case STRENTH:
		_meshRenderer->SetColor(_colors[1]);
		break;
	default:
		break;
	}
}
