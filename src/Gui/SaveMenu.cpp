#include "SaveMenu.h"

SaveMenu::SaveMenu()
{
}

SaveMenu::SaveMenu(TextRenderer text, std::shared_ptr<GameObject> rootObject) : _text(text)
{
	_Bg = Button::Button("", CAMERA.SCR_WIDTH / 2 - 225, CAMERA.SCR_HEIGHT / 2 - 250, 450, 500, 0, glm::vec3(0.1f, 0.1f, 0.1f));
	_Save1 = Button::Button("       Save 1", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 + 150, 220, 50, 21, glm::vec3(0.0f, 0.0f, 0.0f));
	_Save2 = Button::Button("       Save 2", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 + 75, 220, 50, 22, glm::vec3(0.0f, 0.0f, 0.0f));
	_Save3 = Button::Button("       Save 3", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 + 0, 220, 50, 23, glm::vec3(0.5f, 0.0f, 0.0f));
	_Save4 = Button::Button("       Save 4", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 - 75, 220, 50, 24, glm::vec3(0.5f, 0.0f, 0.0f));
	_Save5 = Button::Button("       Save 5", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 - 150, 220, 50, 25, glm::vec3(0.5f, 0.0f, 0.0f));
	_ReturnSave = Button::Button("       Return", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 - 225, 220, 50, 18, glm::vec3(0.0f, 0.0f, 0.0f));

}

void SaveMenu::Draw()
{
	_text.RenderText("Save game", CAMERA.SCR_WIDTH / 2 - 68, CAMERA.SCR_HEIGHT / 2 - 230, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	ShaderSystem& shaders = ShaderSystem::GetInstance();
	shaders.DrawButton(_ReturnSave, _text);
	shaders.DrawButton(_Save1, _text);
	shaders.DrawButton(_Save2, _text);
	shaders.DrawButton(_Save3, _text);
	shaders.DrawButton(_Save4, _text);
	shaders.DrawButton(_Save5, _text);
	shaders.DrawButton(_Bg, _text);
}

void SaveMenu::Update()
{
	_Save1.Update();
	_Save2.Update();
	_ReturnSave.Update();
}
