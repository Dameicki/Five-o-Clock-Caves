#pragma once

#define GLM_SWIZZLE
#define INPUT InputManager::GetInstance()

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Core/Time.h>
#include <iostream>
#include <vector>

class InputManager
{
public:
	
	//Daje instancje singletona
	static InputManager& GetInstance();

	//Aktualizuje stan flag inputu
	void Update();

	//Ustawia okno dla glfw oraz klawisze które nasłuchujemy
	void SetUp(GLFWwindow* window, const unsigned int SCR_WIDTH, const unsigned int SCR_HEIGHT);

	//Nasłuchuje dane klawisze
	void ProcessInput();

	//Ustawia stan klawisza w _keyFlagArray
	void SetKeyFlagState(int keyCode, int action);

	//Ustawia stan przycisku myszy w _mouseButtonFlagArray
	void SetMouseButtonFlagState(int mouseCode, int action);

	//Zwraca flage danego klawisza
	bool GetKeyDown(int keyCode);
	bool IsKeyPressed(int keyCode);
	bool IsKeyReleased(int keyCode);

	//Zwraca flage danego przycisku myszy
	bool GetMouseButtonState(int mouseCode);
	bool GetMouseButtonDown(int mouseCode);
	bool IsMousePressed(int mouseCode);

	//Seter i geter do pozycji myszki
	void SetMousePos(float xpos, float ypos);
	glm::vec2 GetMousePos();

	//Seter i geter do offsetu myszki
	void SetMouseOffset(float xOffset, float yOffset);
	glm::vec2 GetMouseOffset();

	void SetFirstMouse(bool firstMouse);
	bool GetFirstMouse();
	void UpdateOldStates();

	static int ImGuiKeyCorrelation(int keyCode);

	//Callback metoda dla glfw od zmiany wielkości okna
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		GetInstance().FramebufferSizeCallbackIMP(width,height);
	}
	//Implementacja callbacka od zmiany wielkości okna
	void FramebufferSizeCallbackIMP(int width, int height);


	//Callback metoda dla glfw od klikniecia klawisza
	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		GetInstance().KeyCallbackIMP(key, scancode, action, mods);
	}
	//Implementacja callbacka od klikniecia klawisza
	void KeyCallbackIMP(int key, int scancode, int action, int mods);


	//Callback metoda dla glfw od klikniecia przycisków myszy
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		GetInstance().MouseButtonCallbackIMP(button, action, mods);
	}
	//Implementacja callbacka od klikniecia przycisków myszy
	void MouseButtonCallbackIMP(int button, int action, int mods);


	//Callback metoda dla glfw od ruszania myszki
	static void MouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		GetInstance().MouseCallbackIMP(xpos,ypos);
	}
	//Implementacja callbacka od ruszania myszki
	void MouseCallbackIMP(double xpos, double ypos);

	//Callback metoda dla glfw od ruszania oknem
	static void WindowPosCallback(GLFWwindow* window, int xpos, int ypos)
	{
		GetInstance().WindowPosCallbackIMP(xpos, ypos);
	}
	//Implementacja callbacka od ruszania oknem
	void WindowPosCallbackIMP(double xpos, double ypos);
	bool IsGamePaused = false;
	bool IsMainMenu = true;
	bool IsOptions = false;
	bool IsSavingMenu = false;
	bool IsLoadingMenu = false;
	bool IsMenuDrawable = true;
	bool isMenuMoving = false;
	bool IsIntroMoving = false;
private:
	InputManager();
	InputManager(InputManager const&);

	//Trzyma stare stany przycisku
	bool _oldKeyPressFlagArray[349] = { 0 };

	//Trzyma stany wszystkich klawiszy ich kod odpowiada lokalizacji
	bool _keyPressFlagArray[349] = { 0 };

	//Trzyma stany wszystkich klawiszy ich kod odpowiada lokalizacji z ostatniej klatki
	bool _keyHoldFlagArray[349] = { 0 };

	//Trzyma stany przycisków myszy
	bool _mouseButtonPreviousPressFlagArray[3] = { 0 };
	bool _mouseButtonPressFlagArray[3] = { 0 };

	//Pozycja myszki
	glm::vec2 _mousePos;

	//Offset ruchu myszki
	glm::vec2 _mouseOffset;

	bool _firstMouse = true;

	GLFWwindow* _window;

	std::vector<int> _lastKeys;
};
