#include "PlayerInteraction.h"

PlayerInteraction::PlayerInteraction(int keyCodeInteract, int keyCodeInteractAlt) : _keyCodeInteract(keyCodeInteract), _keyCodeInteractAlt(keyCodeInteractAlt)
{
    type = PLAYER_INTERACTION;
}

void PlayerInteraction::Input()
{
    if (INPUT.IsKeyPressed(_keyCodeInteract) || INPUT.IsKeyPressed(_keyCodeInteractAlt))
    {
        if (_interactableObject != nullptr)
        {
            _interactableObject->Interact(m_gameObject);
            if (_interactableObject->isPickable)
                isHolding = !isHolding;
        }
    }
}

void PlayerInteraction::Update()
{
    if(!isHolding)
        _interactableObject = nullptr;
}

void PlayerInteraction::Trigger(std::shared_ptr<CollisionResult> collResult)
{
    if (collResult->GetObjectB()->GetCollisionLayer() == LEVER_COLL && _interactableObject == nullptr)
    {
        _interactableObject = dynamic_pointer_cast<Interactable>(collResult->GetObjectB()->GetOwner()->GetComponent(LEVER));
        return;
    }

    if (collResult->GetObjectB()->GetCollisionLayer() == COG && _interactableObject == nullptr)
    {
        _interactableObject = dynamic_pointer_cast<Interactable>(collResult->GetObjectB()->GetOwner()->GetComponent(COG_COMP));
        return;
    }

    if (collResult->GetObjectB()->GetCollisionLayer() == LEAF && _interactableObject == nullptr)
    {
        _interactableObject = dynamic_pointer_cast<Interactable>(collResult->GetObjectB()->GetOwner()->GetComponent(LEAF_COMP));
        return;
    }

    if (collResult->GetObjectB()->GetCollisionLayer() == DOOR && _interactableObject == nullptr)
    {
        _interactableObject = dynamic_pointer_cast<Interactable>(collResult->GetObjectB()->GetOwner()->GetComponent(DOOR_COMP));
        return;
    }

    if (collResult->GetObjectB()->GetCollisionLayer() == TEAPOT_COLL && _interactableObject == nullptr)
    {
        _interactableObject = dynamic_pointer_cast<Interactable>(collResult->GetObjectB()->GetOwner()->GetComponent(TEAPOT));
        return;
    }
}

void PlayerInteraction::SetUp()
{
    type = PLAYER_INTERACTION;
}

int PlayerInteraction::GetKeyCodeInteract()
{
    return _keyCodeInteract;
}

std::shared_ptr<Interactable> PlayerInteraction::GetInteractableObject()
{
    return _interactableObject;
}

void PlayerInteraction::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
    ImGui::Text(" ");
    static int tmpKey = 0;

    bool enabledTMP = enabled;	// stan włącznika
    ImGui::Checkbox("=== [ PlayerInteraction ] ===", &enabledTMP); // nawa jest tu
    /*
    static const char* keyboard[]{ "A", "D", "S", "W", "E", "Space", "Arrow UP", "Arrow DOWN", "Arrow RIGHT", "Arrow LEFT", "Keypad 2", "Keypad 3"};

    tmpKey = INPUT.ImGuiKeyCorrelation(_keyCodeInteract);
    ImGui::Combo("Interact", &tmpKey, keyboard, IM_ARRAYSIZE(keyboard));
    _keyCodeInteract = INPUT.ImGuiKeyCorrelation(tmpKey);

    tmpKey = INPUT.ImGuiKeyCorrelation(_keyCodeInteractAlt);
    ImGui::Combo("Interact", &tmpKey, keyboard, IM_ARRAYSIZE(keyboard));
    _keyCodeInteractAlt = INPUT.ImGuiKeyCorrelation(tmpKey);
    */

    this->SetEnabled(enabledTMP);			// metoda która reaguje na stan włącznika
}