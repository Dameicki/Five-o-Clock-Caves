#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "../core/GameObject.h"

#include <memory>

class ImguiSystem;

class Hierarchy {
public:
	Hierarchy();

	void StartDraw(std::shared_ptr<GameObject> rootObject, std::shared_ptr<GameObject> selectedObject, ImguiSystem* imguiSystem);

	void AddGameObject(ImguiSystem* imguiSystem);
private:

	char* newObjectName;
	char* scenePath;
};