#include "Leaf.h"


Leaf::Leaf(TeaType teaType):teaType(teaType)
{
    iTeaType = teaType;
    type = LEAF_COMP;
    isPickable = true;
}

Leaf::Leaf()
{
    teaType = JUMP;
    iTeaType = 0;
    type = LEAF_COMP;
    isPickable = true;
}

void Leaf::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
    ImGui::Text(" ");

    string tmp = "[ Leaf " + to_string(index) + " ]";
    if (ImGui::CollapsingHeader(tmp.c_str()))
    {
        static const char* items[]{ "Jump", "Strength" };

        ImGui::ListBox("teaType", &(int)iTeaType, items, IM_ARRAYSIZE(items));

        if (iTeaType != teaType)
            teaType = (TeaType)iTeaType;
    }
}

std::shared_ptr<Component> Leaf::GetCopyComponent()
{
    std::shared_ptr<Component> copyComponent = std::make_shared<Leaf>(Leaf(teaType));
    return copyComponent;
}

TeaType Leaf::GetTeaType()
{
    return teaType;
}
