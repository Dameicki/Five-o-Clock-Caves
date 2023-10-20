#include "Intro.h"

Intro::Intro(TextRenderer text, std::shared_ptr<GameObject> root) : txt(text), _root(root)
{
	xPos = CAMERA.SCR_WIDTH / 2 - 500;
	yPos = CAMERA.SCR_HEIGHT;
}

void Intro::Update()
{
	Move();
	if (INPUT.IsKeyPressed(GLFW_KEY_SPACE))
	{
		ClearDelay();
	}
	if (!Delay(28.2f, true))
	{
		CAMERA.SetUp(glm::vec3(-13.5f, 60.0f, 13.5f));
		INPUT.IsGamePaused = false;
		INPUT.IsMainMenu = false;
		INPUT.IsIntroMoving = false;
		INPUT.isMenuMoving = false;
	}
}

void Intro::Draw()
{
	txt.RenderText("My fellow dwarfs...", xPos, yPos, 0.8f);

	txt.RenderText("Our main perpetuum mobile has broken.", xPos, yPos + 100, 0.8f);
	txt.RenderText("I heard rumors about secondary perpetuum, ", xPos, yPos + 200, 0.8f);
	txt.RenderText("that wasn't used for ages.", xPos, yPos + 300, 0.8f);
	txt.RenderText("As you are my most trustworthy dwarfs in here", xPos, yPos + 400, 0.8f);
	txt.RenderText("I command You, to seek and run the secondary machine...", xPos, yPos + 500, 0.8f);
}

void Intro::Move()
{
	if (yPos > -600)
	{
		float velocity = CAMERA.MovementSpeed * TIME.GetDeltaTime() * 10;
		yPos -= velocity;
	}
}

void Intro::Reset()
{
	yPos = CAMERA.SCR_HEIGHT;
}


