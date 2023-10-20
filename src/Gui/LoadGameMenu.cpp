#include "LoadGameMenu.h"

LoadGameMenu::LoadGameMenu()
{
}

LoadGameMenu::LoadGameMenu(TextRenderer text, std::shared_ptr<GameObject> rootObject) : _text(text)
{
	_Bg = Button::Button("", CAMERA.SCR_WIDTH / 2 - 225, CAMERA.SCR_HEIGHT / 2 - 250, 450, 500, 0, glm::vec3(0.1f, 0.1f, 0.1f));
	_Load1 = Button::Button("       Load 1", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 + 150, 220, 50, 26, glm::vec3(0.0f, 0.0f, 0.0f));
	_Load2 = Button::Button("       Load 2", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 + 75, 220, 50, 27, glm::vec3(0.0f, 0.0f, 0.0f));
	_Load3 = Button::Button("       Load 3", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 + 0, 220, 50, 28, glm::vec3(0.0f, 0.0f, 0.0f));
	_Load4 = Button::Button("       Load 4", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 - 75, 220, 50, 29, glm::vec3(0.0f, 0.0f, 0.0f));
	_Load5 = Button::Button("       Load 5", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 - 150, 220, 50, 30, glm::vec3(0.0f, 0.0f, 0.0f));
	_ReturnLoad = Button::Button("       Return", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 - 225, 220, 50, 19, glm::vec3(0.0f, 0.0f, 0.0f));

}

void LoadGameMenu::Draw()
{
	_text.RenderText("Load game", CAMERA.SCR_WIDTH / 2 - 68, CAMERA.SCR_HEIGHT / 2 - 230, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	ShaderSystem& shaders = ShaderSystem::GetInstance();
	shaders.DrawButton(_ReturnLoad, _text);
	shaders.DrawButton(_Load1, _text);
	shaders.DrawButton(_Load2, _text);
	shaders.DrawButton(_Load3, _text);
	shaders.DrawButton(_Load4, _text);
	shaders.DrawButton(_Load5, _text);
	shaders.DrawButton(_Bg, _text);
}

void LoadGameMenu::Update()
{
	_Load1.Update();
	_Load2.Update();
	_Load3.Update();
	_Load4.Update();
	_Load5.Update();
	_ReturnLoad.Update();
}
