#include "Pickable.h"

Pickable::Pickable()
{
    type = COG_COMP;
    isPickable = true;

}


void Pickable::SetUp()
{
    oldParent = m_gameObject->m_parent;

}

void Pickable::Interact(std::shared_ptr<GameObject> player)
{
    //cout << "Interactable::Interact() in "<< m_gameObject->m_name << endl;
    if (_held)
    {
        Throw();
    }
    else
    {
        PickUp(player);
    }
}

std::shared_ptr<Component> Pickable::GetCopyComponent()
{
    std::shared_ptr<Component> copyComponent = std::make_shared<Pickable>(Pickable());
    return copyComponent; return std::shared_ptr<Component>();
}


void Pickable::Throw()
{
    
    _held = false;
    auto& currentPos = m_gameObject->m_transform->GetGlobalPosition();
    currentPos += glm::vec3(0.0f, -2.0f, 0.0f);

    m_gameObject->SetNewParent(m_gameObject->GetRootObject(m_gameObject)->GetComponent<Scene>(SCENE)->_currentRoom);
    currentPos -= m_gameObject->m_parent->m_transform->GetPosition();
   

    m_gameObject->m_transform->SetPosition(currentPos);

    //std::cout << "somebody threw a cog!";
    m_gameObject->GetComponent<BoxCollider>(BOX_COLLIDER)->SetEnabled(true);

    m_gameObject->UpdateColliders();

   // _interactionPoint.gameObject.SetActive(true);
    //_player.GetComponent<PlayerInteraction>().pickedObj = null;
}

void Pickable::PickUp(std::shared_ptr<GameObject> player)
{
    _held = true;

    m_gameObject->SetNewParent(player);
    
    auto& currentPos = m_gameObject->m_transform->GetPosition();
    currentPos = glm::vec3(0.0f, 3.0f, 0.0f);

    m_gameObject->m_transform->SetPosition(currentPos);
    //std::cout << "somebody picked up a cog!";
    m_gameObject->GetComponent<BoxCollider>(BOX_COLLIDER)->SetEnabled(false);

    //_player.GetComponent<PlayerInteraction>().pickedObj = this;
    //_player.GetComponent<PlayerInteraction>().interactableObject = null;
}

void Pickable::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
    ImGui::Text(" ");

    string tmp = "[ Cog" + to_string(index) + " ]";
    if (ImGui::CollapsingHeader(tmp.c_str()))
    {




    }
}

void Pickable::Trigger(std::shared_ptr<CollisionResult> collResult)
{


}
