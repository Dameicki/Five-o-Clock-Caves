#pragma once


#include "Button.h"
#include "../learnopengl/camera.h"
#include "../Rendering/ShaderSystem.h"
#include "Rendering/TextRenderer.h"
#include "Core/GameObject.h"
#include FT_FREETYPE_H

class MainMenu {
public:
	MainMenu();
	MainMenu(TextRenderer text, std::shared_ptr<GameObject> rootObject);
	void Draw();
	void Update();
	void MoveMenu();
	void ResetMenu();

	Button _Background;
	Button _NewGame;
	Button _LoadGame;
	Button _Options;
	//Button _EffectsLouder;
	//Button _EffectsQuieter;
	//Button _SoundLouder;
	//Button _SoundQuieter;
	//Button _Brighter;
	//Button _Darker;
	//Button _MoreContrast;
	//Button _LessContrast;
	Button _ExitGame;
private:
	TextRenderer _text;
	float textSize;
	//bool _Main;
	std::shared_ptr<GameObject> _rootObject;

};