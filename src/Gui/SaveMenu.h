#pragma once

#include "Button.h"
#include "../learnopengl/camera.h"
#include "../Rendering/ShaderSystem.h"
#include "Rendering/TextRenderer.h"
#include "Core/GameObject.h"
#include FT_FREETYPE_H

class SaveMenu {
public:
	SaveMenu();
	SaveMenu(TextRenderer text, std::shared_ptr<GameObject> rootObject);

	void Draw();
	void Update();
	Button _Save1;
	Button _Save2;
	Button _Save3;
	Button _Save4;
	Button _Save5;
	Button _ReturnSave;
	Button _Bg;
private:
	TextRenderer _text;
	std::shared_ptr<GameObject> _rootObject;

};