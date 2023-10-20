#include "button.h"

Button::Button()
{
}

Button::Button(std::string title, int posx, int posy, int width, int height, int function, glm::vec3 color) : _title(title), _posX(posx), _posY(posy), _height(height), _width(width), _function(function), _color(color) {
	_colorDefault = color;
}




void Button::Update()
{
	glm::vec2 _mousePos = INPUT.GetMousePos();
	if(_mousePos.x <= _posX + _width && _mousePos.x >= _posX && _mousePos.y >= CAMERA.SCR_HEIGHT-_posY - _height && _mousePos.y <= CAMERA.SCR_HEIGHT-_posY)
	{	
		_color = glm::vec3(_colorDefault.r + 0.3, _colorDefault.g + 0.3, _colorDefault.b + 0.3);
		if(INPUT.IsMousePressed(GLFW_MOUSE_BUTTON_1)) {
			Function(_function);
		}
	}
	else
	{
		_color = _colorDefault;
	}
}

void Button::Function(int function)
{
	switch(function)
	{
	case 0:
		break;
	case 1: //Resume game
		INPUT.IsGamePaused = false;
		break;
	case 2: //Restart level
		//std::shared_ptr<GameObject> root = ENTITY.GetEntity("root");
		RESOURCE.PrepereLoadScen(ENTITY.GetEntity("root")->GetComponent<Scene>(SCENE)->_scenePath, ENTITY.GetEntity("root"));
		RESOURCE.LoadScen();
		ENTITY.GetEntity("root")->Update();
		break;
	case 3: //Load game
		INPUT.IsLoadingMenu = true;
		break;
	case 4: //Save game
		INPUT.IsSavingMenu = true;
		break;
	case 5: //Exit to menus
		INPUT.IsGamePaused = false;
		INPUT.IsMainMenu = true;
		break;
	case 6: //Exit to desktop
		_close = true;
		break;
	case 7: //_NewGame
		RESOURCE.PrepereLoadScen("res/scenes/lvl1.xml", ENTITY.GetEntity("root"));
		RESOURCE.LoadScen();
		ENTITY.GetEntity("root")->Update();
		INPUT.isMenuMoving = true;
		break;
	case 8: //_EffectsQuieter
		AUDIO.setEffectsVolume(AUDIO.getEffectsVolume() - 0.01f);
		break;
	case 9: //_EffectsLouder
		AUDIO.setEffectsVolume(AUDIO.getEffectsVolume() + 0.01f);
		break;
	case 10: //_SoundQuieter
		AUDIO.setSoundVolume(AUDIO.getSoundVolume() - 0.01f);
		break;
	case 11: //_SoundLouder
		AUDIO.setSoundVolume(AUDIO.getSoundVolume() + 0.01f);
		break;
	case 12: //_Darker
		//POST.DecreaseBrightness();
		POST._color -= glm::vec3(0.01f, 0.01f, 0.01f);
		break;
	case 13: //_Brighter
		POST._color += glm::vec3(0.01f, 0.01f, 0.01f);
		//POST.IncreaseBrightness();
		break;
	/*case 14: //_LessContrast
		POST.DecreaseContrast();
		break;
	case 15: //_MoreContrast
		POST.IncreaseContrast();
		break;*/
	case 16: //_Options
		INPUT.IsOptions = true;
		break;
	case 17: //_ReturnOptions
		INPUT.IsOptions = false;
		break;
	case 18: //_ReturnSave
		INPUT.IsSavingMenu = false;
		break;
	case 19: //ReturnLoad
		INPUT.IsLoadingMenu = false;
		break;
	case 20: //

		break;
	case 21: //Save1
		ENTITY.GetEntity("root")->Serialize("res/scenes/Save1.xml");
		INPUT.IsSavingMenu = false;
		break;
	case 22: //Save2
		ENTITY.GetEntity("root")->Serialize("res/scenes/Save2.xml");
		INPUT.IsSavingMenu = false;
		break;
	case 23: //Save3
		ENTITY.GetEntity("root")->Serialize("res/scenes/Save3.xml");
		INPUT.IsSavingMenu = false;
		break;
	case 24: //Save4
		ENTITY.GetEntity("root")->Serialize("res/scenes/Save4.xml");
		INPUT.IsSavingMenu = false;
		break;
	case 25: //Save5
		ENTITY.GetEntity("root")->Serialize("res/scenes/Save5.xml");
		INPUT.IsSavingMenu = false;
		break;
	case 26: //Load1
		RESOURCE.PrepereLoadScen("res/scenes/Save1.xml", ENTITY.GetEntity("root"));
		RESOURCE.LoadScen();
		ENTITY.GetEntity("root")->Update();
		INPUT.IsLoadingMenu = false;
		INPUT.IsMainMenu = false;
		break;
	case 27: //Load2
		RESOURCE.PrepereLoadScen("res/scenes/Save2.xml", ENTITY.GetEntity("root"));
		RESOURCE.LoadScen();
		ENTITY.GetEntity("root")->Update();
		INPUT.IsLoadingMenu = false;
		INPUT.IsMainMenu = false;
		break;
	case 28: //Load3
		RESOURCE.PrepereLoadScen("res/scenes/Save3.xml", ENTITY.GetEntity("root"));
		RESOURCE.LoadScen();
		ENTITY.GetEntity("root")->Update();
		INPUT.IsLoadingMenu = false;
		INPUT.IsMainMenu = false;
		break;
	case 29: //Load4
		RESOURCE.PrepereLoadScen("res/scenes/Save4.xml", ENTITY.GetEntity("root"));
		RESOURCE.LoadScen();
		ENTITY.GetEntity("root")->Update();
		INPUT.IsLoadingMenu = false;
		INPUT.IsMainMenu = false;
		break;
	case 30: //Load5
		RESOURCE.PrepereLoadScen("res/scenes/Save5.xml", ENTITY.GetEntity("root"));
		RESOURCE.LoadScen();
		ENTITY.GetEntity("root")->Update();
		INPUT.IsLoadingMenu = false;
		INPUT.IsMainMenu = false;
		break;
	case 31: //

		break;
	case 32: //

		break;

	default:
		break;
	}
}

