#include "Options.h"

Options::Options()
{
}

Options::Options(TextRenderer text) : _text(text)
{
	_Bg = Button::Button("", CAMERA.SCR_WIDTH / 2 - 225, CAMERA.SCR_HEIGHT / 2 - 225,			450,		450,	0, glm::vec3(0.1f, 0.1f, 0.1f));

	_EffectsQuieter = Button::Button("-", CAMERA.SCR_WIDTH / 2 - 110 + 215, CAMERA.SCR_HEIGHT / 2 + 100, 55, 50, 8, glm::vec3(0.0f, 0.4f, 0.0f));
	_EffectsLouder = Button::Button("+", CAMERA.SCR_WIDTH / 2 - 110 + 215 + 60, CAMERA.SCR_HEIGHT / 2 + 100, 55, 50, 9, glm::vec3(0.4f, 0.0f, 0.0f));
	_SoundQuieter = Button::Button("-", CAMERA.SCR_WIDTH / 2 - 110 + 215, CAMERA.SCR_HEIGHT / 2 + 25, 55, 50, 10, glm::vec3(0.0f, 0.4f, 0.0f));
	_SoundLouder = Button::Button("+", CAMERA.SCR_WIDTH / 2 - 110 + 215 + 60, CAMERA.SCR_HEIGHT / 2 + 25, 55, 50, 11, glm::vec3(0.4f, 0.0f, 0.0f));
	_Darker = Button::Button("-", CAMERA.SCR_WIDTH / 2 - 110+215, CAMERA.SCR_HEIGHT / 2 - 50, 55, 50, 12, glm::vec3(0.0f, 0.4f, 0.0f));
	_Brighter = Button::Button("+", CAMERA.SCR_WIDTH / 2 - 110 + 215 + 60, CAMERA.SCR_HEIGHT / 2 - 50, 55, 50, 13, glm::vec3(0.4f, 0.0f, 0.0f));
	//_LessContrast = Button::Button("-", CAMERA.SCR_WIDTH / 2 - 110 + 215, CAMERA.SCR_HEIGHT / 2 - 125, 55, 50, 14, glm::vec3(0.0f, 0.4f, 0.0f));
	//_MoreContrast = Button::Button("+", CAMERA.SCR_WIDTH / 2 - 110 + 215 + 60, CAMERA.SCR_HEIGHT / 2 - 125, 55, 50, 15, glm::vec3(0.4f, 0.0f, 0.0f));
	_ReturnOptions = Button::Button("       Return", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 - 180, 220, 50, 17, glm::vec3(0.0f, 0.0f, 0.0f));
}

void Options::Draw()
{
	_text.RenderText("Options", CAMERA.SCR_WIDTH / 2 - 55, CAMERA.SCR_HEIGHT / 2 - 200, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	ShaderSystem& shaders = ShaderSystem::GetInstance();
	shaders.DrawButton(_EffectsQuieter, _text);
	shaders.DrawButton(_EffectsLouder, _text);
	std::string volume = std::to_string((int)(100.f * AUDIO.getEffectsVolume()));
	_text.RenderText("Effects volume: " + volume, CAMERA.SCR_WIDTH / 2 - 198, CAMERA.SCR_HEIGHT / 2 - 133, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	shaders.DrawButton(_SoundQuieter, _text);
	shaders.DrawButton(_SoundLouder, _text);
	volume = std::to_string((int)(100.f * AUDIO.getSoundVolume()));
	_text.RenderText("Sound volume:     " + volume, CAMERA.SCR_WIDTH / 2 - 198, CAMERA.SCR_HEIGHT / 2 -58, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	shaders.DrawButton(_Darker, _text);
	shaders.DrawButton(_Brighter, _text);
	//volume = std::to_string((int)(100.f * POST.GetBrightness()));;
	volume = std::to_string((int)(100.f * POST._color.r));;
	_text.RenderText("Brightness        " + volume, CAMERA.SCR_WIDTH / 2 - 198, CAMERA.SCR_HEIGHT / 2 + 17, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	//shaders.DrawButton(_LessContrast, _text);
	//shaders.DrawButton(_MoreContrast, _text);
	//volume = std::to_string((int)(100.f * POST.GetContrast()));;
	//_text.RenderText("Contrast            " + volume, CAMERA.SCR_WIDTH / 2 - 198, CAMERA.SCR_HEIGHT / 2 + 92, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	shaders.DrawButton(_ReturnOptions, _text);
	shaders.DrawButton(_Bg, _text);
}

void Options::Update()
{
	_EffectsQuieter.Update();
	_EffectsLouder.Update();
	_SoundQuieter.Update();
	_SoundLouder.Update();
	_Darker.Update();
	_Brighter.Update();
	//_LessContrast.Update();
	//_MoreContrast.Update();
	_ReturnOptions.Update();
}
