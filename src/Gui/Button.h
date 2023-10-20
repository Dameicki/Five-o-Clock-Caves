#pragma once





#include "../Core/InputManager.h"
#include "../learnopengl/camera.h"
#include "../Core/AudioManager.h"
#include "../Rendering/Postprocess.h"

#include "../Core/GameObject.h"
#include "../Core/ResourceManager2.h"
#include "../Core/EntityManager.h"
#include "../Component/Scene.h"

class Button {
public:
	Button();
	Button(std::string title, int posx, int posy, int width, int height, int function, glm::vec3 color);
	void Update();

	int _posX;
	int _posY;
	int _height;
	int _width;
	int _function;
	glm::vec3 _color;
	glm::vec3 _colorDefault;
	std::string _title;
	bool _close = false;
private:
	void Function(int function);
};