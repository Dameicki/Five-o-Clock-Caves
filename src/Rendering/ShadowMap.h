#pragma once
#include <glm/glm.hpp>

#include <Learnopengl/camera.h>
#include <Rendering/ShaderObject.h>



class ShadowMap
{
public:

	ShadowMap();
	void Init();
	void BindForWriting();
	void BindForReading(GLenum textureUnit);
	unsigned int _shadowMap;
private:
	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int _fbo;
	//glm::mat4 _mvp;

};

