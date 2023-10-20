#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
}

PauseMenu::PauseMenu(TextRenderer text, std::shared_ptr<GameObject> rootObject) : _text(text), _rootObject(rootObject)
{
	_Background = Button::Button("", CAMERA.SCR_WIDTH / 2 - 200, CAMERA.SCR_HEIGHT / 2 - 250, 400, 600, 0, glm::vec3(0.1f, 0.1f, 0.1f));
	_ResumeButton = Button::Button("       Resume", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 + 225 , 220, 50, 1, glm::vec3(0.0f, 0.0f, 0.0f));
	_RestartLevel = Button::Button("  Restart level", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 + 150, 220, 50, 2, glm::vec3(0.0f, 0.0f, 0.0f));
	_LoadButton = Button::Button("     Load game", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 + 75, 220, 50, 3, glm::vec3(0.0f, 0.0f, 0.0f));
	_SaveButton = Button::Button("     Save game", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 + 0, 220, 50, 4, glm::vec3(0.0f, 0.0f, 0.0f));
	_Options = Button::Button("       Options", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 - 75, 220, 50, 16, glm::vec3(0.0f, 0.0f, 0.0f));
	_ExitToMenu = Button::Button("   Exit to menu", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 - 150, 220, 50, 5, glm::vec3(0.0f, 0.0f, 0.0f));
	_ExitGame = Button::Button(" Exit to desktop", CAMERA.SCR_WIDTH / 2 - 110, CAMERA.SCR_HEIGHT / 2 - 225, 220, 50, 6, glm::vec3(0.0f, 0.0f, 0.0f));
	_BackgroundControls1 = Button::Button("", 10, CAMERA.SCR_HEIGHT / 2 + 100, 330, 190, 0, glm::vec3(0.1f, 0.1f, 0.1f));
	_BackgroundControls2 = Button::Button("", CAMERA.SCR_WIDTH - 260, CAMERA.SCR_HEIGHT / 2 + 100, 250, 190, 0, glm::vec3(0.1f, 0.1f, 0.1f));
	_BackgroundControls3 = Button::Button("", 0, CAMERA.SCR_HEIGHT / 2 + 90, 350, 210, 0, glm::vec3(0.0f, 0.0f, 0.6f));
	_BackgroundControls4 = Button::Button("", CAMERA.SCR_WIDTH - 270, CAMERA.SCR_HEIGHT / 2 + 90, 290, 210, 0, glm::vec3(0.0f, 0.6f, 0.0f));
}

void PauseMenu::Draw()
{
	_text.RenderText("Pause Menu", CAMERA.SCR_WIDTH / 2 - 80, CAMERA.SCR_HEIGHT / 2 - 310, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	ShaderSystem::GetInstance().DrawButton(_ResumeButton, _text);
	ShaderSystem::GetInstance().DrawButton(_RestartLevel, _text);
	ShaderSystem::GetInstance().DrawButton(_LoadButton, _text);
	ShaderSystem::GetInstance().DrawButton(_SaveButton, _text);
	ShaderSystem::GetInstance().DrawButton(_ExitToMenu, _text);
	ShaderSystem::GetInstance().DrawButton(_ExitGame, _text);
	ShaderSystem::GetInstance().DrawButton(_Options, _text);
	ShaderSystem::GetInstance().DrawButton(_Background, _text); 
	_text.RenderText("Player 1:", 15, CAMERA.SCR_HEIGHT / 2 - 280, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	_text.RenderText("Walk:       Arrow keys", 15, CAMERA.SCR_HEIGHT / 2 - 230, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	_text.RenderText("Jump:       NUM_2 or .", 15, CAMERA.SCR_HEIGHT / 2 - 180, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	_text.RenderText("Interact: NUM_3 or /", 15, CAMERA.SCR_HEIGHT / 2 - 130, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	_text.RenderText("Player 2:", CAMERA.SCR_WIDTH - 255, CAMERA.SCR_HEIGHT / 2 - 280, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	_text.RenderText("Walk:       AWSD", CAMERA.SCR_WIDTH - 255, CAMERA.SCR_HEIGHT / 2 - 230, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	_text.RenderText("Jump:       SPACE", CAMERA.SCR_WIDTH - 255, CAMERA.SCR_HEIGHT / 2 - 180, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	_text.RenderText("Interact: E", CAMERA.SCR_WIDTH - 255, CAMERA.SCR_HEIGHT / 2 - 130, 0.6f, (glm::vec3(1.f, 1.f, 1.f)));
	ShaderSystem::GetInstance().DrawButton(_BackgroundControls1, _text);
	ShaderSystem::GetInstance().DrawButton(_BackgroundControls2, _text);
	ShaderSystem::GetInstance().DrawButton(_BackgroundControls3, _text);
	ShaderSystem::GetInstance().DrawButton(_BackgroundControls4, _text);
}

void PauseMenu::Update()
{
	_ResumeButton.Update();
	_Options.Update();
	_RestartLevel.Update();
	_LoadButton.Update();
	_SaveButton.Update();
	_ExitToMenu.Update();
	_ExitGame.Update();
}
