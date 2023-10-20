#pragma once

#include "core/InputManager.h"
#include "core/GameObject.h"
#include "core/Time.h"
#include "Transform.h"
#include "Component.h"
#include "AnimatorComponent.h"

class GameObject;
class Component;

class PlayerController : public Component
{
public:
	PlayerController(int keyCodeForward, int keyCodeBackward, int keyCodeLeft, int keyCodeRight, int keyCodeInteract, int keyCodeJump, float runSpeed = 5, float smooth = 0.5f, float stopSpeed = 0.1f, float jumpPower = 10, float gravity = -20, float gravityUp = -7, float rotationSpeed = 400);

	void SetUp() override;

	void Input() override;
	void Update() override;
	void Draw(std::shared_ptr<Transform> transform) override;

	void Collision(std::shared_ptr<CollisionResult> collResult) override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;

	void PlayerMove();
	void PlayerJump();
	void PlayerUpdateRotation();

	void SetPushForce(float force);
	float GetPushForce();

	void SetJumps(int jumps);
	void SetUpwardSpeed(float speed);

	void SetPowerUP(int powerUp);

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			cereal::base_class<Component>(this),
			CEREAL_NVP(_runSpeed),
			CEREAL_NVP(_smooth),
			CEREAL_NVP(_stopSpeed),
			CEREAL_NVP(_jumpPower),
			CEREAL_NVP(_gravity),
			CEREAL_NVP(_gravityUp),
			CEREAL_NVP(_rotationSpeed),
			CEREAL_NVP(_keyCodeForward),
			CEREAL_NVP(_keyCodeBackward),
			CEREAL_NVP(_keyCodeLeft),
			CEREAL_NVP(_keyCodeRight),
			CEREAL_NVP(_keyCodeInteract),
			CEREAL_NVP(_keyCodeJump),
			CEREAL_NVP(currentRotation),
			CEREAL_NVP(targetRotation),
			CEREAL_NVP(_animator),
			CEREAL_NVP(_pushForce),
			CEREAL_NVP(_jumps)
		);
	}

private:
	float GetCurentGravity(float speedY);

	shared_ptr<AnimatorComponent> _animator;

	friend class cereal::access;
	PlayerController() {}
	float _runSpeed;
	float _smooth;
	float _stopSpeed;
	float _jumpPower;
	float _gravity;
	float _gravityUp;
	float _rotationSpeed;
	float _pushForce = 1;
	int _jumps = 1;

	int _keyCodeForward;
	int _keyCodeBackward;
	int _keyCodeLeft;
	int _keyCodeRight;
	int _keyCodeInteract; //ALt key for jumping
	int _keyCodeJump;

	float currentXSpeed = 0;
	float currentZSpeed = 0;
	float targetXSpeed = 0;
	float targetZSpeed = 0;
	float upwardSpeed = 0;
	int jumpsLeft;
	float currentRotation;
	float targetRotation;
	bool isInAir = false;

};

CEREAL_REGISTER_TYPE(PlayerController);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Component, PlayerController);