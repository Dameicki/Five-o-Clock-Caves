#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "../core/GameObject.h"

#include <memory>

enum ComponentType;

class Inspector {
public:
	Inspector();

	void StartDraw(std::shared_ptr<GameObject> selectedObject, ImguiSystem* imguiSystem);

	void AddComponet(std::shared_ptr<GameObject> selectedObject, ComponentType componentType);

private:
	int newComponent;
};