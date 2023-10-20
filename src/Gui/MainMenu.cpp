#include "MainMenu.h"

MainMenu::MainMenu()
{
}

MainMenu::MainMenu(TextRenderer text, std::shared_ptr<GameObject> rootObject) : _text(text), _rootObject(rootObject)
{
	//_Background = Button::Button("", CAMERA.SCR_WIDTH / 2 - 200, CAMERA.SCR_HEIGHT / 2 - 250,			400,		550,	0, glm::vec3(0.0f, 0.2f, 0.4f));
	_NewGame = Button::Button("      New game", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 + 113,		220,		50,		7, glm::vec3(0.1f, 0.1f, 0.1f));
	_LoadGame = Button::Button("     Load game", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 + 38,		220,		50,		3, glm::vec3(0.1f, 0.1f, 0.1f));
	_Options = Button::Button("       Options", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 - 37,				220,		50,		16, glm::vec3(0.1f, 0.1f, 0.1f));
	_ExitGame = Button::Button(" Exit to desktop", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 - 112, 220,		50,		6, glm::vec3(0.1f, 0.1f, 0.1f));
	textSize = 0.6f;
}

void MainMenu::Draw()
{
		ShaderSystem& shaders = ShaderSystem::GetInstance();
		shaders.DrawButton(_NewGame, _text);
		shaders.DrawButton(_LoadGame, _text);
		shaders.DrawButton(_Options, _text);
		shaders.DrawButton(_ExitGame, _text);
}

void MainMenu::Update()
{
		_NewGame.Update();
		_LoadGame.Update();
		_Options.Update();
		_ExitGame.Update();
}

void MainMenu::MoveMenu()
{
	float velocity = CAMERA.MovementSpeed * TIME.GetDeltaTime() * 50;
	_NewGame._posY += velocity;
	_LoadGame._posY += velocity;
	_Options._posY += velocity;
	_ExitGame._posY += velocity;
	if(textSize > 0) textSize *= 0.9;
	if(_NewGame._posY > CAMERA.SCR_HEIGHT && _LoadGame._posY > CAMERA.SCR_HEIGHT && _Options._posY > CAMERA.SCR_HEIGHT && _ExitGame._posY > CAMERA.SCR_HEIGHT)
	{
		_text.RenderText("Press space to skip", CAMERA.SCR_WIDTH - 400, 1000, 1.f, glm::vec3(1.f, 1.f, 0.f));
		INPUT.isMenuMoving = false;
		INPUT.IsIntroMoving = true;
	}

}

void MainMenu::ResetMenu()
{
	_NewGame._posY = CAMERA.SCR_HEIGHT / 2 + 113;
	_LoadGame._posY = CAMERA.SCR_HEIGHT / 2 + 38;
	_Options._posY = CAMERA.SCR_HEIGHT / 2 - 37;
	_ExitGame._posY = CAMERA.SCR_HEIGHT / 2 - 112;
}
	
	
