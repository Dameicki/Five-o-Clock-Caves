#include "Interactable.h"

Interactable::Interactable()
{
	type = INTERACTABLE;
}

void Interactable::Interact(std::shared_ptr<GameObject> player)
{
}

void Interactable::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
}
