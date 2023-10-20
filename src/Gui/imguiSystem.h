#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//#include "../core/GameObject.h"
#include "inspector.h"
#include "hierarchy.h"

#include <memory>
#include <Core/AudioManager.h>
#include <Core/InputManager.h>

class GameObject;
class Inspector;
class Hierarchy;

class ImguiSystem {
public:
	ImguiSystem(GLFWwindow* window, const char* glsl_version);

	void Input();
	void StartDraw();
	void EndDraw(GLFWwindow* window);
	void SetTime(float time, int choose);
	void Destroy();

	void SetSelectedObject(std::shared_ptr<GameObject> object);
	std::shared_ptr<GameObject> GetSelectedObjcet();

	void SetSavedObject(std::shared_ptr<GameObject> object);
	std::shared_ptr<GameObject> GetSavedObjcet();

	void SetGlobalSavedObject(std::shared_ptr<GameObject> object);
	std::shared_ptr<GameObject> GetGlobalSavedObjcet();

	void SetRootObject(std::shared_ptr<GameObject> object);

	void SetSavedComponent(std::shared_ptr<Component> component);
	std::shared_ptr<Component> GetSavedComponent();
	
	int indexInHierarchy = 0;

private:
	std::shared_ptr<Inspector> inspector;
	std::shared_ptr<Hierarchy> hierarchy;
	std::shared_ptr<Component> savedComponent;
	float timeFrame,timeUpdate,timeDraw,timeInput,timeCollisionUpdate,timeOther;
	std::shared_ptr<GameObject> savedGameObject;
	std::shared_ptr<GameObject> globalSavedGameObject;
	std::shared_ptr<GameObject> selectedObject;
	std::shared_ptr<GameObject> rootObject;

	bool _active = true;
};