#include "CameraController.h"


CameraController::CameraController(std::shared_ptr<GameObject> &p1, std::shared_ptr<GameObject> &p2): player1(p1), player2(p2)
{

}


void CameraController::SetUp()
{
	type = CAMERA_CONTROLLER;
	levelComplet = false;

	camDefaultRotation[0] = CAMERA.Front;
	camDefaultRotation[1] = CAMERA.Right;
	camDefaultRotation[2] = CAMERA.Up;
	ShaderSystem::GetInstance().UniformCamera();
	CAMERA.setIsEditorMode(false);
	player1pos = player1->m_transform->GetGlobalPosition();
	player2pos = player2->m_transform->GetGlobalPosition();
}

void CameraController::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
	static bool editor = false;
	ImGui::Checkbox("Editor mode", &editor);

	ImGui::InputFloat3("CAMERA.Position", (float*)&CAMERA.Position, "%.3f");

	CAMERA.setIsEditorMode(editor);
}

void CameraController::Input()
{
	if (INPUT.GetKeyDown(GLFW_KEY_F1))
		CAMERA.setIsEditorMode(true);

	//tryb edytorski kamery
	/*if (INPUT.GetKeyDown(GLFW_KEY_F2))
		CAMERA.setIsEditorMode(false);
	if(CAMERA.getIsEditorMode())
	{
		forwardDirection = glm::vec3(0, 0, 0);
		sideDirection = glm::vec3(0, 0, 0);
		if (INPUT.GetKeyDown(GLFW_KEY_I))
			forwardDirection = CAMERA.Front;
		if (INPUT.GetKeyDown(GLFW_KEY_K))
			forwardDirection = -CAMERA.Front;
		if (INPUT.GetKeyDown(GLFW_KEY_J))
			sideDirection = -CAMERA.Right;
		if (INPUT.GetKeyDown(GLFW_KEY_L))
			sideDirection = CAMERA.Right;
		CAMERA.ProcessMouseMovement();
	}*/
}

void CameraController::Update()
{
	if (levelComplet == false)
	{
		player1pos = player1->m_transform->GetGlobalPosition();
		player2pos = player2->m_transform->GetGlobalPosition();
		if (CAMERA.getIsEditorMode()) CameraEditorMove();
		if (!CAMERA.getIsEditorMode()) CameraMove();
		m_gameObject->m_transform->SetPosition(CAMERA.Position);
		m_gameObject->m_transform->SetRotation(CAMERA.Front);
		ShaderSystem::GetInstance().UniformCamera();
	}
	else
	{
		SetPosition(glm::vec3(0.0f, 100.0f, 0.0f));
		SetLookDir(glm::vec3(1.0f, 0.0f, 0.0f));
		ShaderSystem::GetInstance().UniformCamera();
	}
}

void CameraController::Draw(std::shared_ptr<Transform> transform){}

void CameraController::LevelComplet()
{
	CAMERA.setIsEditorMode(true);
	levelComplet = true;
	SetPosition(glm::vec3(0.0f, 100.0f, 0.0f));
	SetLookDir(glm::vec3(1.0f, 0.0f, 0.0f));
}

void CameraController::SetPosition(glm::vec3 newPosition)
{
	CAMERA.Position = newPosition;
}

void CameraController::SetLookDir(glm::vec3 newLookDir)
{
	CAMERA.SetLookDir(newLookDir);
}

void CameraController::CameraEditorMove()
{
	float velocity = CAMERA.MovementSpeed * TIME.GetDeltaTime();
	CAMERA.Position += (forwardDirection + sideDirection) * velocity;
}

void CameraController::CameraMove()
{
	setDefaultRotation();
	glm::vec3 center = player1pos + (player2pos - player1pos) * 0.5f;
	glm::vec3 newPos = camDefaultPos + glm::vec3(center.x, 0, center.z);
	CAMERA.Position = CAMERA.Position + (newPos - CAMERA.Position) * TIME.GetDeltaTime();
}

void CameraController::CameraRotate()
{
}

void CameraController::setDefaultRotation()
{
	CAMERA.Front = camDefaultRotation[0];
	CAMERA.Right = camDefaultRotation[1];
	CAMERA.Up = camDefaultRotation[2];
}




