#pragma once


//..::GLM::..
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

//..::IMGUI::..
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//#include "../core/GameObject.h" // nie mo¿e byæ wzajemnych includów
#include "Component.h"
class GameObject; 

//..::STL::..
#include <iostream>
#include <memory>

//..::CEREAL::..
#include <cereal/cereal.hpp>
#include <cereal/types/memory.hpp>

namespace glm{

template<class Archive> void serialize(Archive& archive, glm::vec2& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y)); }
template<class Archive> void serialize(Archive& archive, glm::vec3& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z)); }
template<class Archive> void serialize(Archive& archive, glm::vec4& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z), CEREAL_NVP(v.w)); }
template<class Archive> void serialize(Archive& archive, glm::ivec2& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y)); }
template<class Archive> void serialize(Archive& archive, glm::ivec3& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z)); }
template<class Archive> void serialize(Archive& archive, glm::ivec4& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z), CEREAL_NVP(v.w)); }
template<class Archive> void serialize(Archive& archive, glm::uvec2& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y)); }
template<class Archive> void serialize(Archive& archive, glm::uvec3& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z)); }
template<class Archive> void serialize(Archive& archive, glm::uvec4& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z), CEREAL_NVP(v.w)); }
template<class Archive> void serialize(Archive& archive, glm::dvec2& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y)); }
template<class Archive> void serialize(Archive& archive, glm::dvec3& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z)); }
template<class Archive> void serialize(Archive& archive, glm::dvec4& v) { archive(CEREAL_NVP(v.x), CEREAL_NVP(v.y), CEREAL_NVP(v.z), CEREAL_NVP(v.w)); }

// glm matrices serialization
template<class Archive> void serialize(Archive& archive, glm::mat2& m) { archive(CEREAL_NVP(m[0]), CEREAL_NVP(m[1])); }
template<class Archive> void serialize(Archive& archive, glm::dmat2& m) { archive(CEREAL_NVP(m[0]), CEREAL_NVP(m[1])); }
template<class Archive> void serialize(Archive& archive, glm::mat3& m) { archive(CEREAL_NVP(m[0]), CEREAL_NVP(m[1]), CEREAL_NVP(m[2])); }
template<class Archive> void serialize(Archive& archive, glm::mat4& m) { archive(CEREAL_NVP(m[0]), CEREAL_NVP(m[1]), CEREAL_NVP(m[2]), CEREAL_NVP(m[3])); }
template<class Archive> void serialize(Archive& archive, glm::dmat4& m) { archive(CEREAL_NVP(m[0]), CEREAL_NVP(m[1]), CEREAL_NVP(m[2]), CEREAL_NVP(m[3])); }

template<class Archive> void serialize(Archive& archive, glm::quat& q) { archive(CEREAL_NVP(q.x), CEREAL_NVP(q.y), CEREAL_NVP(q.z), CEREAL_NVP(q.w)); }
template<class Archive> void serialize(Archive& archive, glm::dquat& q) { archive(CEREAL_NVP(q.x), CEREAL_NVP(q.y), CEREAL_NVP(q.z), CEREAL_NVP(q.w)); }
}

class Transform: public Component{
public:
	Transform(std::shared_ptr<Transform> parentTransform);// Konstruktor dla wszystkich obiektów oprócz "roota"
	Transform();// Konstruktor do tworzenia pierwszego obiektu "root"

	void SetUp() override;

	void Input() override;
	void Update() override;
	void Draw(std::shared_ptr<Transform> transform) override;

	void ImGuiAddToInspector(ImguiSystem* imguiSystem, int index) override;


	void IsDirtyFalse();

	glm::mat4 GetTransformMat(); 

	void SetPosition(glm::vec3 position);
	void SetAxisPosition(float pos, int axis);
	void SetRotation(glm::quat rotation);
	void SetRotation(float x, float y, float z);
	void SetScale(glm::vec3 scale);

	glm::vec3 GetPosition();
	glm::vec3 GetGlobalPosition();
	glm::quat GetRotation();
	glm::vec3 GetScale();

	// ---------------------------- TYMCZASOWE
	glm::vec3 GetRotationEulerDeg();
	void AddPosition(glm::vec3 vector);
	bool GetIsDirty();
	void UpdateTransformMat();
	void SetParentTR(std::shared_ptr<Transform> transform);
	void AddAxisRotation(float rotation, int axis);
	// ---------------------------- TYMCZASOWE

	template<class Archive>
	void serialize(Archive& ar)
	{
		ar(
			CEREAL_NVP(m_pos),
			CEREAL_NVP(m_rot), 
			CEREAL_NVP(m_rotV3),
			CEREAL_NVP(m_scale), 
			CEREAL_NVP(m_transformMat), 
			CEREAL_NVP(isDirty)
		);
	}
	
private:
	glm::vec3 m_pos;
	glm::quat m_rot;
	glm::vec3 m_rotV3;
	glm::vec3 m_scale;
	glm::mat4 m_transformMat;
	bool isDirty;

	std::shared_ptr<Transform> parentTR;
};

