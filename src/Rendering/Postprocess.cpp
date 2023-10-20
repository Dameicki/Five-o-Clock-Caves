#include "Postprocess.h"


Postprocess::Postprocess() {

}

Postprocess& Postprocess::GetInstance()
{
    static Postprocess* instance = NULL;
    if(instance == NULL)
    {
        instance = new Postprocess();
    }
    return *instance;
}

void Postprocess::Start()
{
    float quadVertices[] = {
     -1.0f,  1.0f,  0.0f, 1.0f,
     -1.0f, -1.0f,  0.0f, 0.0f,
      1.0f, -1.0f,  1.0f, 0.0f,

     -1.0f,  1.0f,  0.0f, 1.0f,
      1.0f, -1.0f,  1.0f, 0.0f,
      1.0f,  1.0f,  1.0f, 1.0f
    };
    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &quadVBO);
    glBindVertexArray(quadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    PostprocessShader.use();
    PostprocessShader.setInt("screenTexture", 0);
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CAMERA.SCR_WIDTH, CAMERA.SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, CAMERA.SCR_WIDTH, CAMERA.SCR_HEIGHT);// use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

/*void Postprocess::SetUpFrameBuffer()
{
    glGenFramebuffers(2, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glGenTextures(1, &textureColorbuffer);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, CAMERA.SCR_WIDTH, CAMERA.SCR_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorbuffer, 0);
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, CAMERA.SCR_WIDTH, CAMERA.SCR_HEIGHT);// use a single renderbuffer object for both a depth AND stencil buffer.
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo); // now actually attach it
    // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}*/

void Postprocess::BindFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glEnable(GL_DEPTH_TEST);
}

void Postprocess::UnbindFrameBuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
}

void Postprocess::Draw()
{
    PostprocessShader.use();
    glBindVertexArray(quadVAO);
    glBindTexture(GL_TEXTURE_2D, textureColorbuffer);	// use the color attachment texture as the texture of the quad plane
    glDrawArrays(GL_TRIANGLES, 0, 6);

}

void Postprocess::CleanUp()
{
    glDeleteFramebuffers(1, &fbo);
    glDeleteBuffers(1, &quadVBO);
    glDeleteRenderbuffers(1, &rbo);
}

void Postprocess::IncreaseBrightness()
{
    _brightness += 0.01f;
}

void Postprocess::DecreaseBrightness()
{
    _brightness -= 0.01f;
}

/*void Postprocess::IncreaseContrast()
{
    _contrast += 0.01f;
}

void Postprocess::DecreaseContrast()
{
    _contrast -= 0.01f;
}*/

float Postprocess::GetBrightness()
{
    return _brightness;
}

float Postprocess::GetContrast()
{
    return _contrast;
}
