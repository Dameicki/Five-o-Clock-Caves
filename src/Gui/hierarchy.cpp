#include "hierarchy.h"

Hierarchy::Hierarchy()
{
	newObjectName = new char[128]{"name"};
	scenePath = new char[128]{ "..\\..\\res\\scenes\\lvl1.xml" };
}

void Hierarchy::StartDraw(std::shared_ptr<GameObject> rootObject, std::shared_ptr<GameObject> selectedObject, ImguiSystem* imguiSystem)
{
	ImGui::Begin("Hierarchy");
	ImGui::InputText("scene Path", scenePath, 128); //IM_ARRAYSIZE(newObjectName)
	if (ImGui::Button("SAVE") == true)
	{
		rootObject->Serialize(scenePath);
	}
	ImGui::SameLine();
	if (ImGui::Button("LOAD") == true)
	{
		RESOURCE.PrepereLoadScen(scenePath, rootObject);
	}

	bool addObject = false;

	ImGui::InputText("new Object Name", newObjectName, 128); //IM_ARRAYSIZE(newObjectName)
	//ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.8f, 0.1f, 1.0f });
	if (ImGui::Button("add object") == true)
	{
		AddGameObject(imguiSystem);
	}
	ImGui::PopStyleColor();

	//ImGui::Separator();

	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.7f, 0.1f, 0.1f, 1.0f });
	if (ImGui::Button("remove object") == true)
	{
		selectedObject->Destroy();
		selectedObject = rootObject;
	}
	ImGui::PopStyleColor();

	//ImGui::Separator();

	ImGui::SameLine();
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.9f, 0.5f, 0.0f, 1.0f });
	if (ImGui::Button("move object  ") == true)
	{
		selectedObject->SetNewParent(imguiSystem->GetSavedObjcet());
	}
	ImGui::PopStyleColor();

	ImGui::Separator();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.3f, 0.1f, 1.0f });
	if (ImGui::Button("remember object") == true)
	{
		shared_ptr<GameObject> copyObject = make_shared<GameObject>(GameObject(rootObject, selectedObject->m_name + "_1"));
		copyObject->FullDuplicateObject(selectedObject);
		//rootObject->AddChild(copyObject);
		//rootObject->RemoveChild(copyObject);
		imguiSystem->SetGlobalSavedObject(copyObject);
	}
	ImGui::PopStyleColor();

	if (imguiSystem->GetGlobalSavedObjcet() != nullptr)
	{
		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.8f, 0.1f, 1.0f });
		string tmp1 = "Add " + imguiSystem->GetGlobalSavedObjcet()->m_name;
			if (ImGui::Button(tmp1.c_str()) == true)
			{
				shared_ptr<GameObject> copyObject = make_shared<GameObject>(GameObject(selectedObject, imguiSystem->GetGlobalSavedObjcet()->m_name + "_1"));
				copyObject->FullDuplicateObject(imguiSystem->GetGlobalSavedObjcet());
				selectedObject->AddChild(copyObject);
			}
		ImGui::PopStyleColor();
	}

	ImGui::Separator();

	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.5f, 0.5f, 1.0f });
	if (ImGui::Button("copyOld") == true)
	{
		selectedObject->DuplicateObject();
	}
	ImGui::SameLine();
	if (ImGui::Button("copyFull") == true)
	{
		shared_ptr<GameObject> copyObject = make_shared<GameObject>(GameObject(selectedObject->m_parent, selectedObject->m_name + "_1"));
		copyObject->FullDuplicateObject(selectedObject);
		selectedObject->m_parent->AddChild(copyObject);
	}
	ImGui::PopStyleColor();
	
	ImGui::Text("=================");

	//ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 1.0f, 0.0f, 0.0f, 1.0f });
	imguiSystem->indexInHierarchy = 0;

	// Drow Root button
	string selectedObjectName = imguiSystem->GetSelectedObjcet()->m_name;
	string savedObjectName = imguiSystem->GetSavedObjcet()->m_name;
	string name = rootObject->m_name;
	bool orangeColor = false;
	bool greenColor = false;

	if (name == savedObjectName)		 // zmian koloru zaznaczonego obiektu w hierarchi
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.9f, 0.5f, 0.0f, 1.0f });
		orangeColor = true;
	}

	if (name == selectedObjectName)		 // zmian koloru zaznaczonego obiektu w hierarchi
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.8f, 0.1f, 1.0f });
		greenColor = true;
	}

	if (ImGui::Button(name.c_str()))	// przycisk w hierarchi
	{
		imguiSystem->SetSavedObject(imguiSystem->GetSelectedObjcet());
		imguiSystem->SetSelectedObject(rootObject);
	}

	if (greenColor)  ImGui::PopStyleColor();

	if (orangeColor) ImGui::PopStyleColor();

	imguiSystem->indexInHierarchy++;

	rootObject->ImGuiAddButtonToHierarchy(imguiSystem, true);
	//ImGui::PopStyleColor();

	ImGui::End();
}

void Hierarchy::AddGameObject(ImguiSystem* imguiSystem)
{
	std::shared_ptr<GameObject> objcect = std::make_shared<GameObject>(GameObject(imguiSystem->GetSelectedObjcet(), newObjectName));

	objcect->SetUp();

	imguiSystem->GetSelectedObjcet()->AddChild(objcect);
}
