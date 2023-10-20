#include "GameObject.h"

#include <fstream>

GameObject::GameObject(std::string name, int depth, std::list<std::shared_ptr<GameObject>> children, std::shared_ptr<Transform> transform, std::list<std::shared_ptr<Component>> components, bool ena) :
	m_name(name), m_depth(depth), m_children(children), m_transform(transform), m_components(components), enabled(ena)
{
	drawable = false;
	bsSetup = false;
	m_boundingSphere = std::make_shared<BoundingSphere>(BoundingSphere(0.0f));


}


GameObject::GameObject(std::shared_ptr<GameObject> parent, std::string name)
{
	//std::cout << "GameObject::GameObject(std::shared_ptr<GameObject> parent)" << std::endl;

	m_parent = parent;
	m_transform = std::make_shared<Transform>(Transform(m_parent->m_transform));
	m_boundingSphere = std::make_shared<BoundingSphere>(BoundingSphere(0.0f));
	m_children = std::list<std::shared_ptr<GameObject>>();
	m_components = std::list<std::shared_ptr<Component>>();
	//m_renderer = std::make_shared<MeshRenderer>(nullptr);  // startuje jako nullptr

	m_name = name;
	m_depth =m_parent->m_depth + 1;
	enabled = true;
	drawable = true;
	bsSetup = false;
	//parent->AddChild(shared_from_this()); // ERRORS
}

shared_ptr<GameObject> GameObject::GetRootObject(shared_ptr<GameObject> object)
{
	while (object->m_parent != nullptr)
	{
		object = object->m_parent;
	}

	return object;
}

/*
GameObject::GameObject(std::list<std::shared_ptr<GameObject>> children, std::string name)
{
	std::cout << "tworze obiekt z dziecmi\n";

	m_parent = nullptr;
	m_transform = nullptr; //std::make_shared<Transform>(Transform(m_parent->m_transform));
	//m_boundingSphere = std::make_shared<BoundingSphere>(BoundingSphere(0.0f));
	m_children = children; //std::list<std::shared_ptr<GameObject>>();
	m_components = std::list<std::shared_ptr<Component>>();
	//m_renderer = std::make_shared<MeshRenderer>(nullptr);  // startuje jako nullptr

	m_name = name;
	m_depth = 0; // m_parent->m_depth + 1;
	enabled = true;
	drawable = false;
	bsSetup = false;
}
*/
void GameObject::SetEnabled(bool newEnabled, bool byParent)
{
	if (byParent == false) // bezpoœrednie w³¹czenie lub wy³¹czenie gameObjetu
	{
		if (newEnabled != enabled)
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
		if (newEnabled == true && enabled == true) // jeœli w³¹czam obiekt to w³¹czam jego aktywne dzieci
		{
			this->OnEnabled();
		}
		else if (newEnabled == false && enabled == true) // jeœli wy³¹czamy obiekt to wy³¹czamy jego aktywne dzieci
		{
			this->OnDisabled();
		}
	}
}

void GameObject::Load()
{
	for (auto& component : m_components)
	{
		component->Load();
	}

	for (auto& child : m_children)
	{
		if (child->enabled == true)
			child->Load();
	}
}

void GameObject::SetUp()
{
	ENTITY.AddEntity(shared_from_this());

	for (auto& child : m_children)
	{
		//std::cout << "SetUp " << child->m_name << std::endl;
		child->AddParent(shared_from_this());
		child->m_transform->SetParentTR(m_transform);//std::make_shared<Transform>(Transform(m_transform));
	}


	m_transform->SetUp();
	m_boundingSphere->SetGameObject(shared_from_this());

	for (auto& component : m_components)
	{
		component->SetUp();
	}

	for (auto& child : m_children)
	{
		if(child->enabled == true)
			child->SetUp();
	}
}

GameObject::GameObject(std::string name)
{
	//std::cout << "GameObject::GameObject()" << std::endl;

	//m_parent = std::make_shared<GameObject>(nullptr); // startuje jako nullptr
	m_transform = std::make_shared<Transform>(Transform());
	m_boundingSphere = std::make_shared<BoundingSphere>();
	m_children = std::list<std::shared_ptr<GameObject>>();
	m_components = std::list<std::shared_ptr<Component>>();
	drawable = false;
	bsSetup = false;
	//m_renderer = std::make_shared<MeshRenderer>(nullptr); // startuje jako nullptr

	m_name = name;
	m_depth = 0;
}

void GameObject::Update()
{

	for (auto& component : m_components)
	{
		//std::cout << "Update in " << m_name << "    " << component->GetEnabled() << std::endl;
		if (component->GetEnabled() == true)
			component->Update();
	}
	//std::cout << "Update in "<< m_name << std::endl;
	m_transform->Update();


	for (auto& child : m_children)
	{
		if (child->enabled == true)
			child->Update();
	}

	m_transform->IsDirtyFalse(); // ju¿ wszystko zota³o przetransformowane
}

void GameObject::Input()
{
	for (auto& component : m_components)
	{
		if (component->GetEnabled() == true)
			component->Input();
	}

	for (auto& child : m_children)
	{
		if (child->enabled == true)
			child->Input();
	}
}

void GameObject::Trigger(std::shared_ptr<CollisionResult> collResult)
{
	for (auto& component : m_components)
	{
		component->Trigger(collResult);
	}
}

void GameObject::Collision(std::shared_ptr<CollisionResult> collResult)
{
	for (auto& component : m_components)
	{
		component->Collision(collResult);
	}

	m_transform->Update();
}

void GameObject::CheckIfDrawable()
{
	FrustumCulling();

	for (auto& child : m_children)
	{
		if (child->enabled == true)
			child->CheckIfDrawable();
	}
	
}

void GameObject::CheckIfDrawableInCurrentRoom()
{
	this->GetComponent<Scene>(SCENE)->_currentRoom->CheckIfDrawable();
	this->GetComponent<Scene>(SCENE)->_dwarfs->CheckIfDrawable();
}

void GameObject::Draw()
{
	if (drawable)
	{
		for (auto& component : m_components)
		{

			if (component->GetEnabled() == true)
			{
				component->Draw(m_transform);
			}
		}
	}

	for (auto& child : m_children)
	{
		if (child->enabled == true)
			child->Draw();
	}
}


void GameObject::DrawCurrentRoom()
{
	this->GetComponent<Scene>(SCENE)->_currentRoom->Draw();
	this->GetComponent<Scene>(SCENE)->_dwarfs->Draw();
}

unsigned int GameObject::CreateDebugQuad()
{
	unsigned int quadVAO, quadVBO;
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}

	return quadVAO;
}




void GameObject::DrawShadowMap()
{
	glDisable(GL_DEPTH_TEST);
	auto& Shader = ShaderSystem::GetInstance().shaderObjects.back().GetShader();

	Shader.use();
	Shader.setInt("depthMap", 0);

	static unsigned int VAO = CreateDebugQuad();
	glBindVertexArray(VAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ShaderSystem::GetInstance().shadowMap->_shadowMap);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);
	 

}

void GameObject::DrawToShadowMap()
{

	if (drawable)
	{
		
		for (auto& component : m_components)
		{
			if (component->GetEnabled() == true)
				component->DrawToShadowMap(m_transform);
		}
	}

	for (auto& child : m_children)
	{
		if (child->enabled == true)
			child->DrawToShadowMap();
	}
}



void GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	m_children.push_back(child);
	child->m_parent = shared_from_this();
}

void GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
	m_children.remove(child);
}

void GameObject::DestroyAllChild()
{
	while (m_children.size()>0)
	{
		m_children.front()->Destroy();
	}
}


void GameObject::Destroy()
{
	ENTITY.RemoveEntity(shared_from_this());
	m_parent->RemoveChild(shared_from_this());

	for (auto& component : m_components)
	{
		component->OnDisabled();
	}

	DestroyAllChild();

	//for (auto& child : m_children)
	//{
	//	if (child->enabled == true)
	//		child->SetEnabled(false);
	//		//child->OnDisabled();
	//}
}

void GameObject::SetNewParent(std::shared_ptr<GameObject> newParent)
{
	m_parent->RemoveChild(shared_from_this());
	m_transform->SetParentTR(newParent->m_transform);
	newParent->AddChild(shared_from_this());
}

void GameObject::DuplicateObject()
{
	shared_ptr<GameObject> copyObject = make_shared<GameObject>(GameObject(m_parent, m_name + "_1"));

	copyObject->m_transform->SetPosition(m_transform->GetPosition());
	copyObject->m_transform->SetRotation(m_transform->GetRotation());
	copyObject->m_transform->SetScale(m_transform->GetScale());
	
	//cout << "Kopiowanie (" << m_name << ")" << endl;

	copyObject->m_boundingSphere->SetGameObject(copyObject);

	for (auto & component : m_components)
	{ 
		//cout << typeid(component).name << endl;
		shared_ptr<Component> copyComponent = component->GetCopyComponent();
		//shared_ptr<Component> copyComponent = make_shared<MeshRenderer>(*dynamic_pointer_cast<MeshRenderer>(component));
		//shared_ptr<Component> copyComponent = make_shared<MeshRenderer>(component);
		copyObject->AddComponent(copyComponent);
		copyComponent->SetUp();
	}
	
	copyObject->m_transform->SetUp();
	
	m_parent->AddChild(copyObject);
}

void GameObject::FullDuplicateObject(std::shared_ptr<GameObject> objectToCopy)
{
	m_transform->SetPosition(objectToCopy->m_transform->GetPosition());
	m_transform->SetRotation(objectToCopy->m_transform->GetRotation());
	m_transform->SetScale(objectToCopy->m_transform->GetScale());

	m_boundingSphere->SetGameObject(shared_from_this());

	for (auto& component : objectToCopy->m_components)
	{
		shared_ptr<Component> copyComponent = component->GetCopyComponent();
		AddComponent(copyComponent);
		copyComponent->SetUp();
	}

	m_transform->SetUp();

	for (auto& child : objectToCopy->m_children)
	{
		shared_ptr<GameObject> copyChild = make_shared<GameObject>(GameObject(shared_from_this(), child->m_name));
		copyChild->FullDuplicateObject(child);
		AddChild(copyChild);
	}
}


void GameObject::AddParent(std::shared_ptr<GameObject> parent)
{
	m_parent = parent;
}


void GameObject::AddComponent(std::shared_ptr<Component> component)
{
	m_components.push_back(component);

	component->SetGameObject(shared_from_this());
}

void GameObject::RemoveComponent(std::shared_ptr<Component> component)
{
	m_components.remove(component);
	component->SetEnabled(false);
}

void GameObject::ImGuiAddButtonToHierarchy(ImguiSystem* imguiSystem, bool show)
{
	if (m_children.empty() == false)
	{
		ImGui::SameLine();
		string tmp = to_string(imguiSystem->indexInHierarchy);
		if (ImGui::TreeNode(tmp.c_str()))
		{
			for (auto& child : m_children)
			{
				string selectedObjectName = imguiSystem->GetSelectedObjcet()->m_name;
				string savedObjectName = imguiSystem->GetSavedObjcet()->m_name;
				string name = child->m_name;
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
					imguiSystem->SetSelectedObject(child);
				}

				if (greenColor)  ImGui::PopStyleColor();

				if (orangeColor) ImGui::PopStyleColor();

				imguiSystem->indexInHierarchy++;
				child->ImGuiAddButtonToHierarchy(imguiSystem); // dla wy³¹czonego obiektu musi siê coœ pojawiæ
			}

			ImGui::TreePop();
		}
	}
}

void GameObject::ImGuiAddToInspector(ImguiSystem* imguiSystem)
{
	bool enabledTMP = enabled;						// W³¹cznik	GameObjectu
	ImGui::Checkbox("_", &enabledTMP);	// W³¹cznik	GameObjectu // Tutaj jest nazwa GameObjectu
	this->SetEnabled(enabledTMP);					// W³¹cznik	GameObjectu

	// Zmiana nazwy
	int n = m_name.length();
	char newName[128];
	strcpy(newName, m_name.c_str());
	ImGui::SameLine();
	ImGui::InputText("Name", newName, 35); //IM_ARRAYSIZE(newObjectName)
	m_name = newName;

	m_transform->ImGuiAddToInspector(imguiSystem, 0);		// komponent trasform
	ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.8f, 0.1f, 1.0f });
	if (ImGui::Button("saveComponent"))			        // przycisk zapisz komponent
		imguiSystem->SetSavedComponent(m_transform);    // przycisk zapisz komponent
	ImGui::PopStyleColor();


	m_boundingSphere->ImGuiAddToInspector(imguiSystem, 0);

	int i = 0;
	shared_ptr<Component> componentToRemove;  // Torze wskaŸnik na kmponent do usuniêcia

	for (auto& component : m_components)
	{
		component->ImGuiAddToInspector(imguiSystem, i);	// Wyœwietlenie okna komponentu

			string save = "saveComponent" + to_string(i);   // przycisk zapisz komponent
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.8f, 0.1f, 1.0f });
			if (ImGui::Button(save.c_str()))			    // przycisk zapisz komponent
				imguiSystem->SetSavedComponent(component);  // przycisk zapisz komponent
			ImGui::PopStyleColor();

			string remove = "remove" + to_string(i);		// przycisk usuñ
			ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.7f, 0.1f, 0.1f, 1.0f });
		ImGui::SameLine();
		if (ImGui::Button(remove.c_str()))				// przycisk usuñ
			componentToRemove = component;    // zapamiêtuje który kmponent usun¹æ
		ImGui::PopStyleColor();

		ImGui::Separator();

		i++;
	}

	imguiSystem->GetSavedComponent();

	if(componentToRemove!= nullptr)
		RemoveComponent(componentToRemove); // usuwam komponent
}

void GameObject::SetBSSetup(bool state)
{
	bsSetup = state;
}

void GameObject::FrustumCulling()
{
	if (bsSetup)
	{
		ShaderSystem::GetInstance().frustumN++; // zwiekszenie licznika obiektow sprawdzonych frustumem
		drawable = FRUSTUM.CheckSphereIntersection(m_transform->GetGlobalPosition() + m_boundingSphere->GetCenterOffset(), m_boundingSphere->GetRadius());
	}
	else drawable = false;
}

void GameObject::UpdateColliders()
{
	for (auto& component : m_components)
	{
		if (component->GetType() == BOX_COLLIDER)
		{
			dynamic_pointer_cast<BoxCollider>(component)->UpdateCollider();
		}
	}

	for (auto& child : m_children)
	{
		child->UpdateColliders();
	}
}

std::shared_ptr<Component> GameObject::GetComponent(ComponentType type)
{
	for (auto& component : m_components)
	{
		if (component->GetType() == type)
		{
			return component;

		}
	}
	return std::shared_ptr<Component>();
}

void GameObject::Serialize(std::string path)
{
	std::ofstream outputFile(path);
	cereal::XMLOutputArchive archive(outputFile);
	serialize(archive);

}


void GameObject::Deserialize(std::string path)
{
	std::ifstream inputFile(path);
	cereal::XMLInputArchive archive(inputFile);
	serialize(archive);
	//inputFile.close();
}

void GameObject::OnEnabled()
{
	for (auto& component : m_components)
	{
		component->SetEnabled(true, true);
	}

	for (auto& child : m_children)
	{
		child->SetEnabled(true, true);
	}
}

void GameObject::OnDisabled()
{
	for (auto& component : m_components)
	{
		component->SetEnabled(false, true);
	}

	for (auto& child : m_children)
	{
		child->SetEnabled(false, true);
	}
}
