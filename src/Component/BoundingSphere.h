#pragma once

#include <glad/glad.h> 
#include <glm/glm.hpp>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Component.h"
#include "../Core/GameObject.h"

class Component;
class GameObject;

class BoundingSphere : public Component {
public:
	BoundingSphere();
	BoundingSphere(float radius);

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	void SetParameters(glm::vec4 properties);
	void SetRadius(float radius);
	void SetCenterOffset(glm::vec3 centerOffset);

	glm::vec3 GetCenterOffset();
	float GetRadius();


	

private:
	glm::vec3 _centerOffset;
	float _radius;
};
