#include "ShadowMap.h"

ShadowMap::ShadowMap()
{
	
}

void ShadowMap::Init()
{
	glGenFramebuffers(1, &_fbo);
	glGenTextures(1, &_shadowMap);
	glBindTexture(GL_TEXTURE_2D, _shadowMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, _shadowMap, 0);
	
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
		std::cout << "shadow framebuffer is complete. yay!\n";
	else
		std::cout << "shadow framebuffer is NOT complete!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void ShadowMap::BindForWriting()
{
	glBindFramebuffer(GL_FRAMEBUFFER, _fbo);

}

void ShadowMap::BindForReading(GLenum textureUnit)
{
	glActiveTexture(textureUnit);
	glBindTexture(GL_TEXTURE_2D, _shadowMap);

}


