#pragma once

#include <Learnopengl/shader.h>
#include <Learnopengl/camera.h>
#include <glad/glad.h> 
#define POST Postprocess::GetInstance()

class Postprocess{
public:
	static Postprocess& GetInstance();
	Shader PostprocessShader= Shader("res/shaders/fb_screen.vs", "res/shaders/fb_screen.fs");
	void Start();
	//void SetUpFrameBuffer();
	void BindFrameBuffer();
	void UnbindFrameBuffer();
	void Draw();
	void CleanUp();
	void IncreaseBrightness();
	void DecreaseBrightness();
	//void IncreaseContrast();
	//void DecreaseContrast();
	float GetBrightness();
	float GetContrast();
	glm::vec3 _color = glm::vec3(0.2f, 0.2f, 0.2f);
private:
	Postprocess();
	unsigned int quadVAO, quadVBO;
	float quadVertices[24];
	unsigned int fbo;
	unsigned int framebuffer;
	unsigned int textureColorbuffer;
	unsigned int rbo;
	float _brightness=0;
	float _contrast=0;
};