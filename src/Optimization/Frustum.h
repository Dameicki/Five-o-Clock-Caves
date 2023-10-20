#pragma once
#define FRUSTUM Frustum::GetInstance()

#include <memory>
#include "Plane.h"
#include "Learnopengl/camera.h"

#define FRUSTUM_NEAR  0
#define FRUSTUM_FAR   1
#define FRUSTUM_LEFT  2
#define FRUSTUM_RIGHT 3
#define FRUSTUM_UP    4
#define FRUSTUM_DOWN  5

class Plane;

class Frustum
{
public:
	
	//Daje instancje singletona
	static Frustum& GetInstance();

	void SetUp();

	void Update();

	void GenerateFrustum(glm::mat4 pvMatrix);

	bool CheckSphereIntersection(glm::vec3 center, float radius);

private:

	std::shared_ptr<Plane> _planes[6];
};
