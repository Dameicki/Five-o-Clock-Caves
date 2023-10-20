#include "PlayerController.h"

PlayerController::PlayerController(int keyCodeForward, int keyCodeBackward, int keyCodeLeft, int keyCodeRight, int keyCodeInteract, int keyCodeJump, float runSpeed, float smooth,
    float stopSpeed, float jumpPower, float gravity, float gravityUp, float rotationSpeed) : _keyCodeForward(keyCodeForward), _keyCodeBackward(keyCodeBackward), _keyCodeLeft(keyCodeLeft),
    _keyCodeRight(keyCodeRight), _keyCodeInteract(keyCodeInteract), _keyCodeJump(keyCodeJump), _runSpeed(runSpeed), _smooth(smooth), _stopSpeed(stopSpeed), _jumpPower(jumpPower),
    _gravity(gravity), _gravityUp(gravity), _rotationSpeed(rotationSpeed)
{
    currentRotation = 0;               // wywala error jak pobieram rotacje z game object bo pewnie pointer jest niezrobiony poprawnie jeszcze
    targetRotation = 0;
    type = PLAYER_CONTROLLER;
}

void PlayerController::SetUp()
{
    _animator = m_gameObject->GetComponent<AnimatorComponent>(ANIMATOR);
    jumpsLeft = _jumps;
}

void PlayerController::Input()
{
    // Movement na skos by nieruszac rotacja niczego a osiagnać ten movement
    if (INPUT.GetKeyDown(_keyCodeForward) && INPUT.GetKeyDown(_keyCodeLeft)) {
        targetZSpeed = -_runSpeed;
        targetXSpeed = 0;
    }
    else if (INPUT.GetKeyDown(_keyCodeForward) && INPUT.GetKeyDown(_keyCodeRight)) {
        targetZSpeed = 0;
        targetXSpeed = _runSpeed;
    }
    else if (INPUT.GetKeyDown(_keyCodeBackward) && INPUT.GetKeyDown(_keyCodeLeft)) {
        targetZSpeed = 0;
        targetXSpeed = -_runSpeed;
    }
    else if (INPUT.GetKeyDown(_keyCodeBackward) && INPUT.GetKeyDown(_keyCodeRight)) {
        targetZSpeed = _runSpeed;
        targetXSpeed = 0;
    }
    else if (INPUT.GetKeyDown(_keyCodeForward)) {
        targetZSpeed = -_runSpeed;
        targetXSpeed = _runSpeed;
    }
    else if (INPUT.GetKeyDown(_keyCodeBackward)) {
        targetZSpeed = _runSpeed;
        targetXSpeed = -_runSpeed;
    }
    else if (INPUT.GetKeyDown(_keyCodeLeft)) {
        targetZSpeed = -_runSpeed;
        targetXSpeed = -_runSpeed;
    }
    else if (INPUT.GetKeyDown(_keyCodeRight)) {
        targetZSpeed = _runSpeed;
        targetXSpeed = _runSpeed;
    }
    else {
        targetZSpeed = 0;
        targetXSpeed = 0;
    }

    if (INPUT.IsKeyPressed(_keyCodeJump) || INPUT.IsKeyPressed(_keyCodeInteract)) {
        PlayerJump();
    }
}

void PlayerController::Update()
{
    PlayerMove();
    m_gameObject->UpdateColliders();
}

void PlayerController::Collision(std::shared_ptr<CollisionResult> collResult)
{
    m_gameObject->m_transform->AddPosition(collResult->GetSeparationVector());
    if (collResult->GetDirectionVector() == glm::vec3(0.0f, -1.0f, 0.0f) && upwardSpeed < 0)
    {
        upwardSpeed = 0;
        if (collResult->GetObjectB()->GetCollisionLayer() == GROUND)
        {
            isInAir = false;
            jumpsLeft = _jumps;
        }
        else {
            jumpsLeft = 0;
        }
    }
    else if (collResult->GetDirectionVector() == glm::vec3(0.0f, 1.0f, 0.0f) && upwardSpeed > 0)
    {
        upwardSpeed = 0;
    }
}

void PlayerController::Draw(std::shared_ptr<Transform> transform)
{
}

void PlayerController::ImGuiAddToInspector(ImguiSystem* imguiSystem, int index)
{
    ImGui::Text(" ");		// Odstęp

    string tmp = "[ Player Controller " + to_string(index) + " ]";// nawa jest tu
    if (ImGui::CollapsingHeader(tmp.c_str()))
    {
        static int tmpKey = 0;

        bool enabledTMP = enabled;	// stan włącznika
        ImGui::Checkbox("enabled", &enabledTMP);
        /*
        static const char* keyboard[]{ "A", "D", "S", "W", "E", "Space", "Arrow UP", "Arrow DOWN", "Arrow RIGHT", "Arrow LEFT", "Keypad 2", "Keypad 3" };

        tmpKey = INPUT.ImGuiKeyCorrelation(_keyCodeForward);
        ImGui::Combo("Forward", &tmpKey, keyboard, IM_ARRAYSIZE(keyboard));
        _keyCodeForward = INPUT.ImGuiKeyCorrelation(tmpKey);

        tmpKey = INPUT.ImGuiKeyCorrelation(_keyCodeBackward);
        ImGui::Combo("Bacward", &tmpKey, keyboard, IM_ARRAYSIZE(keyboard));
        _keyCodeBackward = INPUT.ImGuiKeyCorrelation(tmpKey);

        tmpKey = INPUT.ImGuiKeyCorrelation(_keyCodeLeft);
        ImGui::Combo("Left", &tmpKey, keyboard, IM_ARRAYSIZE(keyboard));
        _keyCodeLeft = INPUT.ImGuiKeyCorrelation(tmpKey);

        tmpKey = INPUT.ImGuiKeyCorrelation(_keyCodeRight);
        ImGui::Combo("Right", &tmpKey, keyboard, IM_ARRAYSIZE(keyboard));
        _keyCodeRight = INPUT.ImGuiKeyCorrelation(tmpKey);

        tmpKey = INPUT.ImGuiKeyCorrelation(_keyCodeInteract);
        ImGui::Combo("Interact", &tmpKey, keyboard, IM_ARRAYSIZE(keyboard));
        _keyCodeInteract = INPUT.ImGuiKeyCorrelation(tmpKey);

        tmpKey = INPUT.ImGuiKeyCorrelation(_keyCodeJump);
        ImGui::Combo("Jump", &tmpKey, keyboard, IM_ARRAYSIZE(keyboard));
        _keyCodeJump = INPUT.ImGuiKeyCorrelation(tmpKey);

        */
        ImGui::InputFloat("RunSpeed", (float*)&_runSpeed);
        ImGui::InputFloat("Smooth", (float*)&_smooth);
        ImGui::InputFloat("StopSpeed", (float*)&_stopSpeed);
        ImGui::InputFloat("JumpPower", (float*)&_jumpPower);
        ImGui::InputFloat("Gravity", (float*)&_gravity);
        ImGui::InputFloat("GravityUp", (float*)&_gravityUp);
        ImGui::InputFloat("RotationSpeed", (float*)&_rotationSpeed);
        ImGui::InputFloat("PushForce", (float*)&_pushForce);
        ImGui::InputInt("Jumps", (int*)&_jumps);


        if (ImGui::Button("Reset Player"))
        {
            m_gameObject->m_transform->SetAxisPosition(5, 2);
            upwardSpeed = 0.0f;
        }

        this->SetEnabled(enabledTMP);			// metoda która reaguje na stan włącznika
    }
}

void PlayerController::PlayerMove()
{
    glm::vec3 newPos = m_gameObject->m_transform->GetPosition();

    currentXSpeed = currentXSpeed + (targetXSpeed - currentXSpeed) * _smooth;
    currentZSpeed = currentZSpeed + (targetZSpeed - currentZSpeed) * _smooth;

    float distanceX = currentXSpeed * TIME.GetDeltaTime();
    float distanceZ = currentZSpeed * TIME.GetDeltaTime();

    if (glm::abs(distanceX) > _stopSpeed || glm::abs(distanceZ) > _stopSpeed) {
        targetRotation = glm::atan(currentXSpeed, currentZSpeed) * 57.295779;
 
        float length = glm::length(glm::vec2(distanceX, distanceZ));


        if (length > _runSpeed * TIME.GetDeltaTime())
        {
            distanceX = (distanceX / length) * _runSpeed * TIME.GetDeltaTime();
            distanceZ = (distanceZ / length) * _runSpeed * TIME.GetDeltaTime();
        }

        PlayerUpdateRotation();

        if(isInAir == false)
            _animator->PlayAnimation(1); // ANIMACJA BIEGANIA
        else
            _animator->PlayAnimation(2); // ANIMACJA SKOKU (zatrzymana animacja biegania)
    }
    else
    {
        if (isInAir == false)
            _animator->PlayAnimation(0); // ANIMACJA STANIA
        else
            _animator->PlayAnimation(2); // ANIMACJA SKOKU (zatrzymana animacja biegania)
    }

    upwardSpeed += GetCurentGravity(upwardSpeed) * TIME.GetDeltaTime();
    newPos += glm::vec3(distanceX, upwardSpeed * TIME.GetDeltaTime(), distanceZ);
    m_gameObject->m_transform->SetPosition(newPos);

    if (upwardSpeed * TIME.GetDeltaTime() < -0.075f) isInAir = true; // Sprawdza czy spada
}

void PlayerController::PlayerJump()
{
    if (!isInAir)
    {
        upwardSpeed = _jumpPower;
        isInAir = true;
    }
    else if (jumpsLeft > 1)
    {
        upwardSpeed = _jumpPower;
        isInAir = true;
        jumpsLeft--;
    }
}

void PlayerController::PlayerUpdateRotation()
{
    currentRotation = m_gameObject->m_transform->GetRotationEulerDeg().y;
    float rotDiff = currentRotation - targetRotation;
    if (rotDiff > 180) rotDiff -= 360;
    else if (rotDiff < -180) rotDiff += 360;
    if (rotDiff > 4) {
        m_gameObject->m_transform->SetRotation(0, currentRotation - (_rotationSpeed * TIME.GetDeltaTime()), 0);
    }
    else if (rotDiff < -4) {
        m_gameObject->m_transform->SetRotation(0, currentRotation + (_rotationSpeed * TIME.GetDeltaTime()), 0);
    }
    else {
        m_gameObject->m_transform->SetRotation(0, targetRotation, 0);
    }
}

void PlayerController::SetPushForce(float force)
{
    if (force > 0) SetPowerUP(2);
    else if (force == 0) SetPowerUP(0);
    _pushForce = force;
}

float PlayerController::GetPushForce()
{
    return _pushForce;
}

void PlayerController::SetJumps(int jumps)
{
    if (jumps >= 2) SetPowerUP(1);
    else if (jumps == 1) SetPowerUP(0);
    _jumps = jumps;
}

void PlayerController::SetUpwardSpeed(float speed)
{
    upwardSpeed = speed;
}

void PlayerController::SetPowerUP(int powerUp)
{
    m_gameObject->GetComponent<AnimatorComponent>(ANIMATOR)->SetPowerUPShader(powerUp);
}

float PlayerController::GetCurentGravity(float speedY)
{
    if (speedY > 0)
        return _gravityUp;
    else
        return _gravity;
}
