#include "Scene.h"
#include "Component/AllPlayers.h"

Scene::Scene()
{
	_scenePath =  "..\\..\\res\\scenes\\Scene.xml" ;
	type = SCENE;
}

void Scene::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	ImGui::Text(" ");

	string tmp = "[ Scene " + to_string(index) + " ]";// nawa jest tu
	if (ImGui::CollapsingHeader(tmp.c_str()))
	{
		bool enabledTMP = enabled;	// stan włącznika												
		ImGui::Checkbox("enabled", &enabledTMP);

		// Zmiana sciezki
		char newName[128];
		strcpy(newName, _scenePath.c_str());
		ImGui::InputText("ScenePath", newName, 128); //IM_ARRAYSIZE(newObjectName)
		_scenePath = newName;

		if (ImGui::Button("Set Room1"))
		{
			_currentRoom = ENTITY.GetEntity("room1");
		}

		if (ImGui::Button("Set Dwarfs"))
		{
			_dwarfs = ENTITY.GetEntity("dwarfs");
		}

		this->SetEnabled(enabledTMP);			// metoda która reaguje na stan włącznika
	}
}

void Scene::SetCurrentRoom(std::shared_ptr<GameObject> room)
{
	_currentRoom = room;
}
