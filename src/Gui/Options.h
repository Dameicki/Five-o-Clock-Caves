#pragma once

#include "Button.h"
#include "../learnopengl/camera.h"
#include "Rendering/TextRenderer.h"
#include "../Rendering/ShaderSystem.h"
#include FT_FREETYPE_H

class Options {
public:
	Options();
	Options(TextRenderer text);

	void Draw();
	void Update();

	Button _EffectsLouder;
	Button _EffectsQuieter;
	Button _SoundLouder;
	Button _SoundQuieter;
	Button _Brighter;
	Button _Darker;
	//Button _MoreContrast;
	//Button _LessContrast;
	Button _ReturnOptions;
	Button _Bg;
private:
	TextRenderer _text;
};
