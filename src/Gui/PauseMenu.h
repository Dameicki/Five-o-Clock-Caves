#pragma once
#ifndef PAUSEMENU
#define PAUSEMENU

#include "Button.h"
#include "../learnopengl/camera.h"
#include "../Rendering/ShaderSystem.h"
#include "Rendering/TextRenderer.h"
#include "Core/GameObject.h"
#include FT_FREETYPE_H

class PauseMenu {
public:
	PauseMenu();
	PauseMenu(TextRenderer text, std::shared_ptr<GameObject> rootObject);
	void Draw();
	void Update();

	Button _Background;
	Button _ResumeButton;
	Button _RestartLevel;
	Button _LoadButton;
	Button _SaveButton;
	Button _Options;
	Button _ExitToMenu;
	Button _ExitGame;
	TextRenderer _text;
	Button _BackgroundControls1;
	Button _BackgroundControls2;
	Button _BackgroundControls3;
	Button _BackgroundControls4;
	std::shared_ptr<GameObject> _rootObject;

};


#endif