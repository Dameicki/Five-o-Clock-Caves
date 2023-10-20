#pragma once

#include "../learnopengl/shader.h"
#include "../learnopengl/camera.h"
#include "../learnopengl/model.h" 
#include "ShaderObject.h"
#include "ShadowMap.h"
#include "../Gui/Button.h"

#include <memory>
#include <Rendering\LightManager.h>
#include "Rendering/TextRenderer.h"
#include FT_FREETYPE_H

enum LightType;
class Button;

class ShaderSystem
{
public:
	//ShaderSystem(const ShaderSystem&) = delete; // usuno³em konstruktor kopiuj¹cy
	ShaderSystem();

	static ShaderSystem& GetInstance();

	void UniformCamera();

	void UniformDirLight(glm::vec3 direction = glm::vec3(-0.2f, -1.0f, -0.3f), 
		glm::vec3 color = glm::vec3(0.4f, 0.4f, 0.4f),
		glm::vec3 specular = glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3 ambient = glm::vec3(0.02f, 0.02f, 0.1f), 
		bool enable = true, glm::mat4& lightSpace = CAMERA.GetViewMatrix());

	void UniformPointLight(glm::vec3 position, glm::vec3 color, glm::vec3 specular, glm::vec3 ambient, float constant, 
		float linear, float quadratic, bool enable, int id);
	
	void UniformSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, glm::vec3 specular, glm::vec3 ambient, float constant, float linear,
		float quadratic, float cutOff, float outerCutOff, bool enable, int id);
	

	void CheckNumberOfLights(LightType lightType, int n);

	void Draw(std::shared_ptr<Model> model, glm::mat4 transformMat, int shaderID, glm::vec3 color = glm::vec3(1.0f), float shininess = 32.0f, glm::vec3 specular = glm::vec3(0.1f));


	void DrawByGeometry(glm::mat4 transformMat, int shaderID, glm::vec3 color, int resolution, glm::vec3 size);
	void DrawByGeometrySphere(glm::mat4 transformMat, int shaderID, glm::vec3 color, int resolution, float radius);

	void DrawSprite(unsigned int texture, glm::mat4 transformMat, int shaderID);
	void DrawButton(Button button, TextRenderer text);

	void DrawToShadowMap(std::shared_ptr<Model> model, glm::mat4 transformMat, bool animated);

	std::vector<ShaderObject> shaderObjects;

	std::shared_ptr<ShadowMap> shadowMap;

	//std::vector<ShaderObject> shaderObjects;

	bool drowDebug = false; // w³¹cz wy³¹cz renderowanie boxColliderów

	int drowN = 0;
	int frustumN = 0;

private:

	void SetUpGeometryShader();
	void SetUpSpriteShader();
	void PrepareMatricesForShadowMap();

	unsigned int VBO_geometry, VAO_geometry;
	unsigned int VBO_sprite, VAO_sprite, EBO_sprite, texture;
	unsigned int ButtonVAO, ButtonVBO;

	int pointLightsLimit, spotLightsLimit;

	glm::mat4 viewBillboard;
};
