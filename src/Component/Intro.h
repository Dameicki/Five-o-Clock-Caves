#pragma once
#include "learnopengl/camera.h"
#include "Rendering/ShaderSystem.h"
#include "Rendering/TextRenderer.h"
#include "Core/GameObject.h"
#include FT_FREETYPE_H

class Intro : public Component
{
	TextRenderer txt;
	float xPos, yPos;
	std::shared_ptr<GameObject> _root;
public:
	Intro(TextRenderer text,std::shared_ptr<GameObject> root);
	void Update() override;
	void Draw();
	void Move();
	void Reset();
};