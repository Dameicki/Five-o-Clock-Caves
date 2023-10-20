#include "Time.h"

Time::Time()
{
}

Time& Time::GetInstance()
{
	static Time* instance = NULL;

	if (instance == NULL)
		instance = new Time();

	return *instance;
}

void Time::Update()
{
	PerFrameTimeLogic();
}

void Time::PerFrameTimeLogic()
{
    if (!windowMoved)
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
    }
    else
    {
        float currentFrame = glfwGetTime();
        lastFrame = currentFrame;
        deltaTime = 0;
        windowMoved = false;
    }
    if (deltaTime > 0.06) deltaTime = 0.06f; // TYMCZASOWE PILNOWANIE KROKU UPDATU
}

void Time::UpdateLastFrame()
{
    float currentFrame = glfwGetTime();
    lastFrame1 = currentFrame;
}

void Time::SetWindowMoved(bool state)
{
    windowMoved = state;
}

void Time::PerUpdateTimeLogic()
{
	float currentFrame = glfwGetTime();
	deltaTime1 = currentFrame - lastFrame1;
	lastFrame1 = currentFrame;
}

float Time::GetDeltaTime()
{
	return deltaTime;
}

float Time::GetTimeForUpdate()
{
	return deltaTime1;
}
