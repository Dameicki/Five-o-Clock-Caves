#include "ShaderSystem.h"

ShaderSystem::ShaderSystem() : shaderObjects{
					  //œwiat³o//textura 
		{"default",		true,	true,	"res/shaders/default.vs",		"res/shaders/default.fs"	},
		{"light",		false,	false,	"res/shaders/light.vs",			"res/shaders/light.fs"		},
		{"color",		true,	false,	"res/shaders/color.vs",			"res/shaders/color.fs"		},
		{"box",			false,	false,	"res/shaders/forGeometry.vs",	"res/shaders/forGeometry.fs",	"res/shaders/box.gs"	},
		{"sprite",		false,	false,	"res/shaders/sprite.vs",		"res/shaders/sprite.fs"		},
		{"sphere",		false,	false,	"res/shaders/forGeometry.vs",	"res/shaders/forGeometry.fs",	"res/shaders/sphere.gs"	},
		{"depth" ,		true,	false,	"res/shaders/depth.vs",			"res/shaders/depth.fs"		},
		{"animated",	true,	true,	"res/shaders/animation.vs",		"res/shaders/animation.fs"	},
		{"world",		true,	true,	"res/shaders/worldTextures.vs",	"res/shaders/worldTextures.fs"	},
		{"button",		false,	false,	"res/shaders/button.vs",		"res/shaders/button.fs" },
		{"debugQuad",   false, false , "res/shaders/debugQuad.vs" ,		"res/shaders/debugQuad.fs" },
		{"depthAnimated",  true, false , "res/shaders/depthAnim.vs" ,	"res/shaders/depthAnim.fs" },
		{"colorFresnel",true,	false,	"res/shaders/color.vs",			"res/shaders/colorFresnel.fs"},
		{"animatedFresnel",	true,	true,	"res/shaders/animation.vs",		"res/shaders/animationFresnel.fs"	},
		{"defaultNoLights",	false,	true,	"res/shaders/default.vs",		"res/shaders/defaultNoLights.fs"	}
}
{
	SetUpGeometryShader(); 
	SetUpSpriteShader();
	pointLightsLimit = 5;
	spotLightsLimit = 7;

	shadowMap = std::make_shared<ShadowMap>(ShadowMap());
	shadowMap->Init();
}

ShaderSystem& ShaderSystem::GetInstance()
{
	static ShaderSystem* instance = NULL;

	if (instance == NULL)
		instance = new ShaderSystem();

	return *instance;
}

void ShaderSystem::UniformCamera()
{
	for (auto& shader : shaderObjects)
	{
		shader.UniformCamera();
	}
	
	viewBillboard = CAMERA.GetViewMatrix();
	viewBillboard[0][0] = 1.0f;
	viewBillboard[0][1] = 0.0f;
	viewBillboard[0][2] = 0.0f;

	viewBillboard[1][0] = 0.0f;
	viewBillboard[1][1] = 1.0f;
	viewBillboard[1][2] = 0.0f;

	viewBillboard[2][0] = 0.0f;
	viewBillboard[2][1] = 0.0f;
	viewBillboard[2][2] = 1.0f;
	
}

void ShaderSystem::UniformDirLight(glm::vec3 direction, glm::vec3 color, glm::vec3 specular, glm::vec3 ambient, bool enable, glm::mat4& lightSpace)
{
	

	for (auto& shader : shaderObjects)
	{
		color = POST._color;
		shader.UniformDirLight(direction, color, specular, ambient, enable, lightSpace);
	}
}

void ShaderSystem::UniformPointLight(glm::vec3 position, glm::vec3 color, glm::vec3 specular, glm::vec3 ambient, float constant, float linear, 
	float quadratic, bool enable, int id)
{
	if (id < pointLightsLimit)
	{
		for (auto& shader : shaderObjects)
		{
			shader.UniformPointLight(position, color, specular, ambient, constant, linear, quadratic, enable, id);
		}
	}
}

void ShaderSystem::UniformSpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 color, glm::vec3 specular, glm::vec3 ambient, float constant, 
	float linear, float quadratic, float cutOff, float outerCutOff, bool enable, int id)
{
	if (id < spotLightsLimit)
	{
		for (auto& shader : shaderObjects)
		{
			shader.UniformSpotLight(position, direction, color, specular, ambient, constant, linear, quadratic, cutOff, outerCutOff, enable, id);
		}
	}
}

void ShaderSystem::CheckNumberOfLights(LightType lightType, int n)
{
	switch (lightType)
	{
	case point:
		if (n < pointLightsLimit)
		{
			for (int i = pointLightsLimit - 1; i >= n; i--) // dla wszystkich œwiate³ z limitu których nie u¿ywamy 
			{
				for (auto& shader : shaderObjects) // we wszystkich shaderach 
				{
					shader.UniformPointLightEnabled(false, i); // ustawiamy enabled na false
				}
			}
		}
		break;
	case spot:
		if (n < spotLightsLimit)
		{
			for (int i = spotLightsLimit - 1; i >= n; i--) // dla wszystkich œwiate³ z limitu których nie u¿ywamy 
			{
				for (auto& shader : shaderObjects) // we wszystkich shaderach 
				{
					shader.UniformSpotLightEnabled(false, i); // ustawiamy enabled na false
				}
			}
		}
		break;
	case dir:
		if (n == -1)
		{
			for (auto& shader : shaderObjects) // we wszystkich shaderach 
			{
				shader.UniformDirLightEnabled(false, 1); // ustawiamy enabled na false
			}
		}
		break;
	default:
		break;
	}
}

void ShaderSystem::Draw(std::shared_ptr<Model> model, glm::mat4 transformMat, int shaderID, glm::vec3 color, float shininess, glm::vec3 specular)
{
	drowN++;
	//PrepareMatricesForShadowMap();

	//glm::mat4 dirLightProj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 100.0f);
	////glm::mat4 dirLightView = glm::lookAt(glm::vec3(-1.0f, 6.0f,0.0f), 
	//	//glm::vec3(0.0f, 1.0f, 0.0f), 
	//	//glm::vec3(0.0f, 1.0f, 0.0f)); 	//sztywno ustawione œwiat³o kierunkowe
	//glm::mat4 dirLightView = CAMERA.GetViewMatrix();
	//glm::mat4 dirlightSpaceMatrix = dirLightProj * dirLightView;
	
	shadowMap->BindForReading(GL_TEXTURE0);
	Shader& shader = shaderObjects[shaderID].GetShader();

	shader.use();
	shader.setMat4("model", transformMat);
	shader.setVec3("material.color", color);
	shader.setVec3("material.specular", specular);
	shader.setFloat("material.shininess", shininess);
	//shader.setMat4("lightSpaceMatrix", dirlightSpaceMatrix);
	shader.setInt("shadowMap", 0);
	 
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	 
	model->Draw(shader, shaderObjects[shaderID].GetNeedTexture()); 
}	

void ShaderSystem::DrawByGeometry(glm::mat4 transformMat, int shaderID, glm::vec3 color, int resolution, glm::vec3 size)
{
	if (drowDebug)
	{
		Shader& shader = shaderObjects[shaderID].GetShader();

		shader.use();
		//shader.setFloat("r", r);
		//vertexN = resolution;
		//shader.setInt("vertexN", resolution);
		shader.setMat4("model", transformMat);
		shader.setVec3("color", color);
		shader.setVec3("size", size);


		glBindVertexArray(VAO_geometry);
		glDrawArrays(GL_POINTS, 0, 1);
	}
}

void ShaderSystem::DrawByGeometrySphere(glm::mat4 transformMat, int shaderID, glm::vec3 color, int resolution, float radius)
{
	if (drowDebug)
	{
		Shader& shader = shaderObjects[shaderID].GetShader();

		// ---------------- TYMCZASOWE usuwanie rotacji
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				transformMat[i][j] = 0.0;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			transformMat[i][i] = 1.0;
		}
		// ----------------

		shader.use();
		//shader.setFloat("r", r);
		//vertexN = resolution;
		shader.setInt("vertexN", resolution);
		shader.setMat4("model", transformMat);
		shader.setVec3("color", color);
		shader.setFloat("r", radius);


		glBindVertexArray(VAO_geometry);
		glDrawArrays(GL_POINTS, 0, 1);
	}
}

void ShaderSystem::DrawSprite(unsigned int texture, glm::mat4 transformMat, int shaderID)
{
	Shader& shader = shaderObjects[shaderID].GetShader();

	glBindTexture(GL_TEXTURE_2D, texture);

	shader.use();

	shader.setMat4("model", transformMat);
	shader.setMat4("view", viewBillboard);

	glBindVertexArray(VAO_sprite);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	//glActiveTexture(GL_TEXTURE0);
}

void ShaderSystem::SetUpGeometryShader()
{
	float point[] = { 0.0f, 0.0f, 0.0f };

	glGenVertexArrays(1, &VAO_geometry);
	glGenBuffers(1, &VBO_geometry);

	glBindVertexArray(VAO_geometry);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_geometry);
	glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
}

void ShaderSystem::SetUpSpriteShader()
{
	float vertices[] = {
		// positions          // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &VAO_sprite);
	glGenBuffers(1, &VBO_sprite);
	glGenBuffers(1, &EBO_sprite);

	glBindVertexArray(VAO_sprite);

	glBindBuffer(GL_ARRAY_BUFFER, VBO_sprite);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO_sprite);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// texture coord attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void ShaderSystem::DrawButton(Button button, TextRenderer text) {
	float ButtonVertices[] = { 
		2.0 * button._posX / (float)CAMERA.SCR_WIDTH - 1.0,							2.0 * (button._posY + button._height) / (float)CAMERA.SCR_HEIGHT - 1.0f,
		2.0 * button._posX / (float)CAMERA.SCR_WIDTH - 1.0f,						2.0 * button._posY / (float)CAMERA.SCR_HEIGHT - 1.0f,
		2.0 * (button._posX + button._width) / CAMERA.SCR_WIDTH - 1.0f,				2.0 * button._posY / (float)CAMERA.SCR_HEIGHT - 1.0f,

		2.0 * button._posX / (float)CAMERA.SCR_WIDTH - 1.0f,						2.0 * (button._posY + button._height) / (float)CAMERA.SCR_HEIGHT - 1.0f,
		2.0 * (button._posX + button._width) / (float)CAMERA.SCR_WIDTH - 1.0f,		2.0 * button._posY / (float)CAMERA.SCR_HEIGHT - 1.0f,
		2.0 * (button._posX + button._width) / (float)CAMERA.SCR_WIDTH - 1.0f,		2.0 * (button._posY + button._height) / (float)CAMERA.SCR_HEIGHT - 1.0f
	};
	glGenVertexArrays(1, &ButtonVAO);
	glGenBuffers(1, &ButtonVBO);
	glBindVertexArray(ButtonVAO);
	glBindBuffer(GL_ARRAY_BUFFER, ButtonVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ButtonVertices), &ButtonVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	Shader& shader = shaderObjects[9].GetShader();
	shader.use();
	shader.setVec3("colour", button._color);
	text.RenderText(button._title, button._posX+5, CAMERA.SCR_HEIGHT - button._posY - (button._height/1.6), 0.5f, glm::vec3(1.0, 1.0, 1.0));
	shader.use();
	glBindVertexArray(ButtonVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);	
	glDeleteVertexArrays(1, &ButtonVAO);
	glDeleteBuffers(1, &ButtonVBO);
	
}

void ShaderSystem::DrawToShadowMap(std::shared_ptr<Model> model, glm::mat4 transformMat, bool animated)
{
	unsigned int shaderNr = 6;


	if (animated)
		shaderNr = 11;

	Shader& depthShader = shaderObjects[shaderNr].GetShader(); //depth shader


	//glm::mat4 dirLightProj = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 100.0f);
	////glm::mat4 dirLightView = glm::lookAt(glm::vec3(-1.0f, 6.0f, 0.0f), 
	//	//glm::vec3(0.0f, 1.0f, 0.0f), 
	//	//glm::vec3(0.0f, 1.0f, 0.0f)); 	//sztywno ustawione œwiat³o kierunkowe
	//glm::mat4 dirLightView = CAMERA.GetViewMatrix();
	//glm::mat4 dirlightSpaceMatrix = dirLightProj * dirLightView;

	depthShader.use();
	depthShader.setMat4("model", transformMat);
	//depthShader.setMat4("lightSpaceMatrix", dirlightSpaceMatrix);

	//shadowMap->BindForWriting();

	model->Draw(depthShader, false);

}
 