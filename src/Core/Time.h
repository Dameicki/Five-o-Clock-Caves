#pragma once
#define TIME Time::GetInstance()

#include <GLFW/glfw3.h>

class Time
{
public:
	
	//Daje instancje singletona
	static Time& GetInstance();

	void Update();

	void PerFrameTimeLogic();

	void PerUpdateTimeLogic();

	float GetDeltaTime();
	float GetTimeForUpdate();

	void UpdateLastFrame();
	void SetWindowMoved(bool state);

private:
	Time();
	Time(Time const&);

	float deltaTime = 0.0f;		//czas wykonania calej petli gry
	float lastFrame = 0.0f;		//czas ostatniej petli gry
	float deltaTime1 = 0.0f;	//bufor	
	float lastFrame1 = 0.0f;	//bufor2 (sequel, bo jedynka byla tak dobra)

	bool windowMoved = false;
};
