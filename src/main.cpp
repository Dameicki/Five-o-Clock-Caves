//#pragma comment(linker, "/subsystem:windows /entry:mainCRTStartup")
// dear imgui: standalone example application for GLFW + OpenGL 3, using programmable pipeline
// If you are new to dear imgui, see examples/README.txt and documentation at the top of imgui.cpp.
// (GLFW is a cross-platform general purpose library for handling windows, inputs, OpenGL/Vulkan graphics context creation, etc.)

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#define STB_IMAGE_IMPLEMENTATION

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// About OpenGL function loaders: modern OpenGL doesn't have a standard header file and requires individual function pointers to be loaded manually. 
// Helper libraries are often used for this purpose! Here we are supporting a few common ones: gl3w, glew, glad.
// You may use another loader/header of your choice (glext, glLoadGen, etc.), or chose to manually implement your own.
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
#include <GL/gl3w.h>    // Initialize with gl3wInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

#include <GLFW/glfw3.h> // Include glfw3.h after our OpenGL definitions


#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm\gtx\transform.hpp>

#include "learnopengl/camera.h"
#include "gui/imguiSystem.h"
#include "core/GameObject.h"
#include "Rendering/ShaderSystem.h"
#include "Optimization/Frustum.h"
#include "Rendering/ShadowMap.h"
#include "Rendering/TextRenderer.h"
#include "Rendering/Postprocess.h"
#include "Gui/PauseMenu.h"
#include "Gui/MainMenu.h"
#include "Gui/Options.h"
#include "Gui/SaveMenu.h"
#include "Gui/LoadGameMenu.h"
#include "Gui/Button.h"

//..::COMPONENTS::..
#include "component/MeshRenderer.h"
#include "Component/PointLight.h"
#include "Component/PlayerController.h"
#include "Component/BoxCollider.h"
#include "Component/LinearMotion.h"
#include "Component/SinMotion.h"
#include "Component/PlayerStick.h"
#include "Component/SpotLight.h"
#include "Component/SpriteRenderer.h"
#include "Component/CameraController.h"
#include "Component/BoundingSphere.h"
#include "Component/PlayerInteraction.h"
#include "Component/ActionBase.h"
#include "Component/Interactable.h"
#include "Component/Lever.h"
#include "Component/ActionLever.h"
#include "Component/Platform.h"
#include "Component/Death.h"
#include "Component/PuzzleChecker.h"
#include "Component/AnimatorComponent.h"
#include "Component/Intro.h"

//..::CORE::..
#include "core/GameObject.h"
#include "core/InputManager.h"
#include "core/Time.h"
#include "core/CollisionManager.h"
#include "Core/EntityManager.h"
#include "Core/AudioManager.h"
//#include "core/Serializer.h"

#include <math.h>
#include <memory>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <ft2build.h>
#include <irrKlang.h>
#include FT_FREETYPE_H


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Decide GL+GLSL versions
#if __APPLE__
	// GL 3.2 + GLSL 150
	const char* glsl_version = "#version 150";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
	// GL 4.3 + GLSL 430
	const char* glsl_version = "#version 430";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Five'o'clock Caves", NULL, NULL);				// URUCHOM W OKNIE
   // GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Five'o'clock Caves", glfwGetPrimaryMonitor(), NULL);// URUCHOM NA PEŁNYM EKRANIE
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //audio setup
    AUDIO.setUp((float)0.15, 1); //ustawiam glosnosc muzyki na 15% i efektów na 100%
    AUDIO.playMusic("res/audio/cave.ogg", true);

    // tworzenie imgui
    // ---------------
    std::shared_ptr<ImguiSystem> imguiSystem = std::make_shared<ImguiSystem>(window, glsl_version);

    INPUT.SetUp(window, mode->width, mode->height);

	// tell GLFW to capture our mouse                                    //  USTAWIANIE WIDOCZNO�CI KURSORA
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);       //  USTAWIANIE WIDOCZNO�CI KURSORA
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);           //  USTAWIANIE WIDOCZNO�CI KURSORA

	// Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
	bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
	bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
	bool err = !gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
#endif
	if (err)
	{
		fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

    //Freetype creation
    TextRenderer text(mode->width, mode->height);
    text.Load("res/upheavtt.ttf", 48);
   

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    //stbi_set_flip_vertically_on_load(true);  // Model krasnoluda ma ju� odwr�con� teksture

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	//====================================== START ================================================

	// build and compile shaders
	// -------------------------
	ShaderSystem::GetInstance().UniformDirLight();// ustawiam �wiat�a 

	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


	glm::vec3 textColor(1.f, 1.f, 1.f);

	glm::vec3 deltaColor(-0.1f, -0.1f, -0.1f);

	std::shared_ptr<GameObject> root = std::make_shared<GameObject>(GameObject("root"));

	PauseMenu pauseMenu = PauseMenu(text, root);
	MainMenu mainMenu = MainMenu(text, root);
	Options options = Options(text);
	LoadGameMenu loadMenu = LoadGameMenu(text, root);
	SaveMenu saveMenu = SaveMenu(text, root);
	Intro intro = Intro(text, root);

	root->Deserialize("res\\scenes\\lvl1.xml");
	CAMERA.SetUp(glm::vec3(-13.5f, 60.0f, 13.5f));
	root->Load();

	root->SetUp();
	FRUSTUM.SetUp();

	imguiSystem->SetSelectedObject(root);
	imguiSystem->SetSavedObject(root);
	imguiSystem->SetRootObject(root);


	// Tak dodaje modle do listy modeli w edytorze (nowe modele których nie ma na scenie)
	//RESOURCE.GetModel("res/models/Paintings/door.obj");
	//RESOURCE.GetModel("res/models/Paintings/jump.obj");
	//RESOURCE.GetModel("res/models/Paintings/nextLevel.obj");
	//RESOURCE.GetModel("res/models/Rock/rock.fbx");

	// Alternatywne tekstury ścian i podłogi
	RESOURCE.GetModel("res/models/Ground/ground2.obj");
	RESOURCE.GetModel("res/models/Ground/ground3.obj");
	RESOURCE.GetModel("res/models/Ground/ground4.obj");
	RESOURCE.GetModel("res/models/Ground/ground5.obj");
	RESOURCE.GetModel("res/models/Ground/ground6.obj");

	// dekoracje
	RESOURCE.GetModel("res/models/Stalactite/stalagnate.fbx");
	RESOURCE.GetModel("res/models/Stalactite/stalactite.fbx");
	RESOURCE.GetModel("res/models/Paintings/strengt.obj");

    POST.Start();

    TIME.PerFrameTimeLogic();
    glfwSwapInterval(1);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        //std::cout << "While Start" << std::endl;
        //AUDIO.setSoundVolume(imguiSystem->musicVolume);
        //AUDIO.setEffectsVolume(imguiSystem->effectsVolume);
        //POST.PostprocessShader.setFloat("brightness", POST._brightness);
        //POST.PostprocessShader.setFloat("contrast", POST._contrast);
        //POST.BindFrameBuffer();
        // per-frame time logic
        // --------------------
        TIME.PerFrameTimeLogic();
        TIME.PerUpdateTimeLogic();
        imguiSystem->SetTime(TIME.GetDeltaTime(), 5); // Przekazanie czasu 5=Last frame time do imgui
        // input
        // -----
        //processInput(window);

		// render
		// ------
		//glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		imguiSystem->Input();
        imguiSystem->StartDraw(); // wy�wietlanie okienek imgui 
        TIME.PerUpdateTimeLogic();
        float otherTime = TIME.GetTimeForUpdate();
		if(!INPUT.GetInstance().IsMainMenu) //Jeśli nie jest włączone main menu wykonaj:
		{
			if(INPUT.GetInstance().IsKeyPressed(GLFW_KEY_ESCAPE)) INPUT.GetInstance().IsGamePaused = true; //ESC włącza menu pauzy
			if(INPUT.GetInstance().IsGamePaused)  //IF Menu pauzy włączone
			{
				mainMenu.ResetMenu();
				intro.Reset();
				if(INPUT.IsOptions)  //IF Okno opcji włączone
				{
					options.Draw();
					options.Update();
				}
				else			//IF  Okno opcji wyłączone
				{
					if(INPUT.IsSavingMenu) //IF Okno zapisu gry włączone
					{
						saveMenu.Draw();
						saveMenu.Update();
					}
					else				//IF Okno zapisu gry wyłączone
					{
						if(INPUT.IsLoadingMenu)  //IF Okno wczytania gry włączone
						{
							loadMenu.Draw();
							loadMenu.Update();
						}
						else                         //IF Okno wczytania gry wyłączone
						{
							pauseMenu.Draw();
							pauseMenu.Update();
							if(pauseMenu._ExitGame._close) glfwSetWindowShouldClose(window, GLFW_TRUE);
							TIME.PerUpdateTimeLogic();
							imguiSystem->SetTime(TIME.GetTimeForUpdate(), 2);  // Przekazanie czasu 2=Input do imgui 
							TIME.PerUpdateTimeLogic();
							imguiSystem->SetTime(TIME.GetTimeForUpdate(), 0);  // Przekazanie czasu 0=Update do imgui

						}
					}
				}
			}
			else    //IF menu pauzy wyłączone
			{
				root->Input();  // aktualizacja stanu inputu
				TIME.PerUpdateTimeLogic();
				imguiSystem->SetTime(TIME.GetTimeForUpdate(), 2);  // Przekazanie czasu 2=Input do imgui 

				root->Update(); // aktualizacja grafu sceny (trasform�w)
				TIME.PerUpdateTimeLogic();
				imguiSystem->SetTime(TIME.GetTimeForUpdate(), 0);  // Przekazanie czasu 0=Update do imgui

				// collision
				// -----
				COLLISION.Update();
				TIME.PerUpdateTimeLogic();
				imguiSystem->SetTime(TIME.GetTimeForUpdate(), 3);  // Przekazanie czasu 3=CollisionUpdate do imgui
			}

			FRUSTUM.Update();                                   // frustum culling

			ShaderSystem::GetInstance().frustumN = 0; // zerowanie licznika obiektow sprawdzonych frustumem
			LIGHTS.visiblePointN = 0;// zerowanie licznika światęł
			LIGHTS.visibleSpotN  = 0;// zerowanie licznika światęł
			root->CheckIfDrawableInCurrentRoom();
			LIGHTS.FrustumCulling();	// Sprawdzenie frusumem tlko świateł w obecnym pokoju
			TIME.PerUpdateTimeLogic();
			otherTime = otherTime + TIME.GetTimeForUpdate();

			//SHADOW MAP FIRST PASS-----
			glEnable(GL_DEPTH_TEST);
			ShaderSystem::GetInstance().shadowMap->BindForWriting();
			glViewport(0, 0, 1024, 1024);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glCullFace(GL_FRONT);
			root->DrawToShadowMap(); // rysowanie mapy cieni do framebuffera
			glViewport(0, 0, CAMERA.SCR_WIDTH, CAMERA.SCR_HEIGHT);
			glCullFace(GL_BACK);
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			//SHADOW MAP FIRST PASS END-----


			ShaderSystem::GetInstance().drowN = 0;// zerowanie licznika obiektow rysowanych
			root->DrawCurrentRoom(); // rysowanie grafu sceny optymalnie
			//root->DrawShadowMap();
			//glBindFramebuffer(GL_FRAMEBUFFER, 0);
			//..........::SHADOW MAPPING FIRST PASS END ::......

			//..........::SHADOW MAPPING SECOND PASS ::.......


			// Ładuje nową scene
			RESOURCE.LoadScen();

			//..........::SHADOW MAPPING SECOND PASS END::.......
		}
		else    //IF   MenuGłówne  włączone
		{
			if(INPUT.IsOptions)    //IF Okno opcji włączone
			{
				options.Draw();
				options.Update();
			}
			else					//IF Okno opcji wyłączone
			{
				if(INPUT.IsLoadingMenu)  //IF Okno wczytania gry włączone
				{
					loadMenu.Draw();
					loadMenu.Update();
				}
				else					//IF Okno ładowania nowej gry wyłączone
				{
					if (INPUT.isMenuMoving || INPUT.IsIntroMoving)
					{
						if (INPUT.isMenuMoving)
						{
							mainMenu.Draw();
							mainMenu.MoveMenu();
						}
						intro.Update();
						intro.Draw();
						text.RenderText("Press space", CAMERA.SCR_WIDTH - 400, 1000, 1.f);
						text.RenderText("to skip", CAMERA.SCR_WIDTH - 400, 1050, 1.f);
					}
					else
					{
						mainMenu.Update();
						mainMenu.Draw();
						if(mainMenu._ExitGame._close) glfwSetWindowShouldClose(window, GLFW_TRUE);
					}
					
				}
			}
		}
        
        //text.RenderText("Brytyjskie Krasnoludy", CAMERA.SCR_WIDTH / 2 - 300, 100, 1.f, textColor);
        textColor += deltaColor * TIME.GetDeltaTime();


		//POST.UnbindFrameBuffer();
		//POST.Draw();
		

		TIME.PerUpdateTimeLogic();
		imguiSystem->SetTime(TIME.GetTimeForUpdate(), 1);// Przekazanie czasu 1=Draw do imgui
		imguiSystem->EndDraw(window); // od�wierzanie okienek imgui 
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		INPUT.UpdateOldStates();
		glfwSwapBuffers(window);
		glfwPollEvents();
		TIME.PerUpdateTimeLogic();
		imguiSystem->SetTime(TIME.GetTimeForUpdate() + otherTime, 4);  // Przekazanie czasu 4=Other do imgui
	}
	//POST.CleanUp();
	// glfw: terminate, clearing all previously allocated GLFW resources.
	 // ------------------------------------------------------------------
	imguiSystem->Destroy();
	glfwTerminate();
	AUDIO.removeAudio();
	return 0;
}

