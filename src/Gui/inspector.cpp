#include "inspector.h"
#include "../Component/PlayerController.h"
#include "../Component/LinearMotion.h"
#include "../Component/SinMotion.h"
#include "../Component/PlayerStick.h"
#include "../Component/PointLight.h"
#include "../Component/SpotLight.h"
#include "../Component/SpriteRenderer.h"
#include "../Component/Lever.h"
#include "../Component/ActionLever.h"
#include "../Component/Platform.h"
#include "../Component/PlayerInteraction.h"
#include "../Component/PuzzleChecker.h"
#include "../Component/Pickable.h"
#include "../Component/DoorInteract.h"
#include "../Component/ActionCog.h"
#include "../Component/Death.h"
#include "../Component/BoxController.h"
#include "../Component/PlaceForCog.h"
#include "../Component/ActionBox.h"
#include "../Component/ActionMesh.h"
#include "../Component/ActionDoor.h"
#include "../Component/AnimatorComponent.h"
#include "../Component/GooldDoorInteract.h"
#include "../Component/Teapot.h"
#include "../Component/Leaf.h"
#include "../Component/Level.h"
#include "../Component/AllPlayers.h"
#include "../Component/DirLight.h"
#include "../Component/Scene.h"



class Teapot;
class Leaf;

//#include "../Component"
//#include "../Component"


Inspector::Inspector()
{
	newComponent = 0;
}

void Inspector::StartDraw(std::shared_ptr<GameObject> selectedObject, ImguiSystem* imguiSystem)
{

	ImGui::Begin("Inspector");

	selectedObject->ImGuiAddToInspector(imguiSystem);

	static const char* items[]{ "  ", "PlayerController", "BoxCollider",
		"LinearMotion", "SinMotion", "MeshRenderer", "PlayerStick", "PointLight",
		"SpotLight", "SpriteRenderer" ,"Interactable", "Lever","ActionBase",
		"ActionLever","Platform","PlayerInteraction", "PuzzleChecker", "Cog", "Door", "ActionCog",
		"DeathZone", "BoxController" ,"PlaceForCog", "ActionBox", "ActionMesh", "ActionDoor",
		"Animator","GooldDoor", "Teapot", "Leaf", "Level", "AllPlayers", "DirLight", "Scene" };//,  "Bush" };
		

	ImGui::Text(" ");
	ImGui::Text("--------------------");
	ImGui::ListBox("newComponent", &newComponent, items, IM_ARRAYSIZE(items));

	if (newComponent != 0)
	{
		AddComponet(selectedObject, (ComponentType)(newComponent + 1));// +1 ¿eby nie by³o transforma
		newComponent = 0;
	}
		

	ImGui::End();
}

void Inspector::AddComponet(std::shared_ptr<GameObject> selectedObject, ComponentType componentType)
{
	std::shared_ptr<Component> component;

	switch (componentType)
	{
	//case NONE: // nie powino Wyst¹piæ
	//	break;
	//case TRANSFORM:
	//	break;
	case PLAYER_CONTROLLER:
		component = std::make_shared<PlayerController>(PlayerController(GLFW_KEY_UP, GLFW_KEY_DOWN, GLFW_KEY_RIGHT, GLFW_KEY_LEFT, GLFW_KEY_KP_3, GLFW_KEY_KP_2));
		break;
	case BOX_COLLIDER:
		component = std::make_shared<BoxCollider>(BoxCollider());
		break;
	case LINEAR_MOTION:
		component = std::make_shared<LinearMotion>(LinearMotion());
		break;
	case SIN_MOTION:
		component = std::make_shared<SinMotion>(SinMotion());
		break;
	case MESH_RENDERER:
		component = std::make_shared<MeshRenderer>(MeshRenderer("res/models/Ground/ground.obj"));
		break;
	case PLAYER_STICK:
		component = std::make_shared<PlayerStick>(PlayerStick());
		break;
	case POINT_LIGHT:
		component = std::make_shared<PointLight>(PointLight());
		break;
	case SPOT_LIGHT:
		component = std::make_shared<SpotLight>(SpotLight());
		break;
	case SPRITE_RENDERER:
		component = std::make_shared<SpriteRenderer>(SpriteRenderer());
		break;
	case LEVER:
		component = std::make_shared<Lever>(Lever());
		break;
	case ACTION_LEVER:
		component = std::make_shared<ActionLever>(ActionLever());
		break;
	case PLATFORM:
		component = std::make_shared<Platform>(Platform());
		break;
	case PLAYER_INTERACTION:
		component = std::make_shared<PlayerInteraction>(PlayerInteraction(GLFW_KEY_KP_3, GLFW_KEY_KP_5));
		break;
	case PUZZLE_CHECKER:
		component = std::make_shared<PuzzleChecker>(PuzzleChecker());
		break;
	case COG_COMP:
		component = std::make_shared<Pickable>(Pickable());
		break;
	case DOOR_COMP:
		component = std::make_shared<DoorInteract>(DoorInteract());
		break;
	case ACTION_COG:
		component = std::make_shared<ActionCog>(ActionCog());
		break;
	case DEATH_ZONE:
		component = std::make_shared<Death>(Death());
		break;
	case BOX_CONTROLLER:
		component = std::make_shared<BoxController>(BoxController());
		break;
	case PLACE_FOR_COG:
		component = std::make_shared<PlaceForCog>(PlaceForCog());
		break;
	case ACTION_BOX:
		component = std::make_shared<ActionBox>(ActionBox());
		break;
	case ACTION_MESH:
		component = std::make_shared<ActionMesh>(ActionMesh());
		break;
	case ACTION_DOOR:
		component = std::make_shared<ActionDoor>(ActionDoor());
		break;
	case ANIMATOR:
		component = make_shared<AnimatorComponent>(AnimatorComponent("res/models/Dwarf-1/model1.fbx", vector<string>{"res/models/Dwarf-1/model1.fbx", "res/models/Animations/anim1.fbx"}, vector<float>{0, 1.2}));
		break;
	case GOOLD_DOOR_COMP:
		component = make_shared<GooldDoorInteract>(GooldDoorInteract());
		break;
	case TEAPOT:
		component = make_shared<Teapot>(Teapot(NONE_EFFECT));
		break;
	case LEAF_COMP:
		component = make_shared<Leaf>(Leaf(JUMP));
		break;
	case LEVEL:
		component = make_shared<Level>(Level());
		break;
	case ALL_PLAYERS:
		component = make_shared<AllPlayers>(AllPlayers());
		break;
	case DIR_LIGHT :
		component = make_shared<DirLight>(DirLight());
		break;
	case SCENE:
		component = make_shared<Scene>(Scene());
		break;
	default:
		return; // nie doda siê nowy komponent
		break;
	}

	selectedObject->AddComponent(component);
	component->SetUp();
}

