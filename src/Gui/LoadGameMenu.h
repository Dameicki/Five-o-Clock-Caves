#pragma once

#include "Button.h"
#include "../learnopengl/camera.h"
#include "../Rendering/ShaderSystem.h"
#include "Rendering/TextRenderer.h"
#include "Core/GameObject.h"
#include FT_FREETYPE_H

class LoadGameMenu {
public:
	LoadGameMenu();
	LoadGameMenu(TextRenderer text, std::shared_ptr<GameObject> rootObject);

	void Draw();
	void Update();
	Button _Load1;
	Button _Load2;
	Button _Load3;
	Button _Load4;
	Button _Load5;
	Button _ReturnLoad;
	Button _Bg;
private:
	TextRenderer _text;
	std::shared_ptr<GameObject> _rootObject;

};