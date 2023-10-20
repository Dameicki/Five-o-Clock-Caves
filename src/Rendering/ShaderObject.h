#pragma once

#include "../learnopengl/shader.h"
#include "../learnopengl/camera.h"

#include <string>
#include <memory>

class ShaderObject
{
public:
	ShaderObject(std::string name, bool needLight, bool needTexture,const char* vsPath, const char* fsPath): shader(vsPath, fsPath)
	{
		this->needLight = needLight;
		this->needTexture = needTexture;
		this->name = name;
	}

	ShaderObject(std::string name, bool needLight, bool needTexture, const char* vsPath, const char* fsPath, const char* gsPath) : shader(vsPath, fsPath, gsPath)
	{
		this->needLight = needLight;
		this->needTexture = needTexture;
		this->name = name;
	}

	void UniformCamera()
	{
		shader.use();
		shader.setVec3("viewPos", CAMERA.Position); // pozycja kamery
		glm::mat4 projection = glm::perspective(glm::radians(CAMERA.Zoom), (float)CAMERA.SCR_WIDTH / (float)CAMERA.SCR_HEIGHT, 0.1f, 65.0f); // TODO nie mo¿e byæ na sztywno
		glm::mat4 view = CAMERA.GetViewMatrix();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
	}

	void UniformDirLight(glm::vec3 direction, glm::vec3 color, glm::vec3 specular, glm::vec3 ambient, bool enable, glm::mat4 lightSpaceProj)
	{
		if (needLight == true)
		{
			shader.use();
			shader.setBool("dirLight.enable", enable);
			shader.setVec3("dirLight.ambient", ambient);
			shader.setVec3("dirLight.diffuse", color);
			shader.setVec3("dirLight.specular", specular);
			shader.setVec3("dirLight.direction", direction);
			shader.setMat4("lightSpaceMatrix", lightSpaceProj);
		}
	}

	void UniformPointLight(glm::vec3 position, glm::vec3 color, glm::vec3 specular, glm::vec3 ambient, float constant, float linear, float quadratic, bool enable, int id)
	{
		if (needLight == true)
		{
			std::string lightName = "pointLights[" + std::to_string(id);
			shader.use();
			shader.setBool(lightName + "].enable", enable);
			shader.setVec3(lightName + "].position" ,position);
			shader.setVec3(lightName + "].ambient", ambient);
			shader.setVec3(lightName + "].diffuse", color);
			shader.setVec3(lightName + "].specular", specular);
			shader.setFloat(lightName + "].constant", constant);
			shader.setFloat(lightName + "].linear", linear);
			shader.setFloat(lightName + "].quadratic", quadratic);
		}
	}

	void UniformSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, glm::vec3 specular, glm::vec3 ambient, float constant, float linear,
		float quadratic, float cutOff, float outerCutOff, bool enable, int id)
	{
		if (needLight)
		{
			std::string lightName = "spotLights[" + std::to_string(id);
			shader.use();
			shader.setBool(lightName + "].enable", enable);
			shader.setVec3(lightName + "].position", position);
			shader.setVec3(lightName + "].direction", direction);
			shader.setVec3(lightName + "].ambient", ambient);
			shader.setVec3(lightName + "].diffuse", color);
			shader.setVec3(lightName + "].specular", specular);
			shader.setFloat(lightName + "].constant", constant);
			shader.setFloat(lightName + "].linear", linear);
			shader.setFloat(lightName + "].quadratic", quadratic);
			shader.setFloat(lightName + "].cutOff", cutOff);
			shader.setFloat(lightName + "].outerCutOff", outerCutOff);
		}
	}

	void UniformPointLightEnabled(bool enable, int id)
	{
		if (needLight == true)
		{
			std::string lightName = "pointLights[" + std::to_string(id);
			shader.use();
			shader.setBool(lightName + "].enable", enable);
		}
	}

	void UniformSpotLightEnabled(bool enable, int id)
	{
		if (needLight)
		{
			std::string lightName = "spotLights[" + std::to_string(id);
			shader.use();
			shader.setBool(lightName + "].enable", enable);
		}
	}

	void UniformDirLightEnabled(bool enable, int id)
	{
		if (needLight)
		{
			std::string lightName = "dirLight";
			shader.use();
			shader.setBool(lightName + ".enable", enable);
		}
	}


	Shader GetShader()
	{
		return shader;
	}

	bool GetNeedTexture()
	{
		return needTexture;
	}

	std::string GetName()
	{
		return name;
	}

private:
	Shader shader;

	std::string name;

	bool needLight;
	bool needTexture;
};

