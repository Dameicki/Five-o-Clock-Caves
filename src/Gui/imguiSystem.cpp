
#include "imguiSystem.h"

float brightness=0;
float contrast = 0;

ImguiSystem::ImguiSystem(GLFWwindow* window, const char* glsl_version)
{
    inspector = std::make_shared<Inspector>();
    hierarchy = std::make_shared<Hierarchy>();

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Setup style
    ImGui::StyleColorsDark();
    ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.1f, 0.5f, 0.5f, 1.0f));
    //ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));

    globalSavedGameObject = nullptr;
}

void ImguiSystem::Input()
{
    
    if (INPUT.GetKeyDown(GLFW_KEY_0) && INPUT.GetKeyDown(GLFW_KEY_MINUS) && INPUT.IsKeyPressed(GLFW_KEY_EQUAL))
    {
        _active = !_active;
        //std::cout << "Dev Mode: "<< _active << std::endl;
    }
    
}

void ImguiSystem::StartDraw()
{
    if (_active)
    {
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        static float f = 0.0f;
        static int counter = 0;
        ImGui::Begin("Setings");

        ImGui::Text("Application average    %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::Text("Last frame time:       %f ms", timeFrame);
        ImGui::Text("Update time:           %f ms", timeUpdate);
        ImGui::Text("Input time:            %f ms", timeInput);
        ImGui::Text("Draw time:             %f ms", timeDraw);
        ImGui::Text("Collision update time: %f ms", timeCollisionUpdate);
        ImGui::Text("Other time:            %f ms", timeOther);
        ImGui::Text("-----");
        ImGui::Text("Draw object    = %i", ShaderSystem::GetInstance().drowN);
        ImGui::Text("Frustum object = %i", ShaderSystem::GetInstance().frustumN);
        ImGui::Text("-----");
        ImGui::Text("Point Lights = %i / %i", LIGHTS.visiblePointN, LIGHTS.pointLights.size());
        ImGui::Text("Spot  Lights = %i / %i", LIGHTS.visibleSpotN,  LIGHTS.spotLights.size());
        ImGui::Text("-----");
        ImGui::Checkbox("DrawDebug", &ShaderSystem::GetInstance().drowDebug);
        if (ImGui::Button("removeAllLights")) LIGHTS.RemoveAllLights();
        ImGui::End();

        inspector->StartDraw(selectedObject, this);

        hierarchy->StartDraw(rootObject, selectedObject, this);
    }
}

void ImguiSystem::SetTime(float time, int choose)
{
    switch (choose)
    {
    case 0:
        timeUpdate = time*1000.0f;
        break;
    case 1:
        timeDraw = time*1000.0f;
        break;
    case 2:
        timeInput = time*1000.0f;
        break;
    case 3:
        timeCollisionUpdate = time*1000.0f;
        break;
    case 4:
        timeOther = time * 1000.0f;
        break;
    case 5:
        timeFrame = time * 1000.0f;
        break;
    }
}

void ImguiSystem::EndDraw(GLFWwindow* window)
{
    if (_active)
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

void ImguiSystem::Destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void ImguiSystem::SetSelectedObject(std::shared_ptr<GameObject> object)
{
    selectedObject = object;
}

std::shared_ptr<GameObject> ImguiSystem::GetSelectedObjcet()
{
    return selectedObject;
}

void ImguiSystem::SetSavedObject(std::shared_ptr<GameObject> object)
{
    savedGameObject = object;
}

std::shared_ptr<GameObject> ImguiSystem::GetSavedObjcet()
{
    return savedGameObject;
}

void ImguiSystem::SetGlobalSavedObject(std::shared_ptr<GameObject> object)
{
    globalSavedGameObject = object;
}

std::shared_ptr<GameObject> ImguiSystem::GetGlobalSavedObjcet()
{
    return globalSavedGameObject;
}

void ImguiSystem::SetRootObject(std::shared_ptr<GameObject> object)
{
    rootObject = object;
}

void ImguiSystem::SetSavedComponent(std::shared_ptr<Component> component)
{
    savedComponent = component;
}

std::shared_ptr<Component> ImguiSystem::GetSavedComponent()
{
    return savedComponent;
}
