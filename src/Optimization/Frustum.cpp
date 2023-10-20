#include "Frustum.h"

Frustum& Frustum::GetInstance()
{
	static Frustum* instance = NULL;

	if (instance == NULL)
		instance = new Frustum();

	return *instance;
}

void Frustum::SetUp()
{
	for (int i = 0; i < 6; i++) _planes[i] = std::make_shared<Plane>(Plane(glm::vec3(0.0f), 0.0f));
	glm::mat4 projection = glm::perspective(glm::radians(CAMERA.Zoom), (float)CAMERA.SCR_WIDTH / (float)CAMERA.SCR_HEIGHT, 0.1f, 65.0f); // TODO nie mo�e by� na sztywno
	glm::mat4 view = CAMERA.GetViewMatrix();
	GenerateFrustum(projection * view);
}

void Frustum::Update()
{
	glm::mat4 projection = glm::perspective(glm::radians(CAMERA.Zoom), (float)CAMERA.SCR_WIDTH / (float)CAMERA.SCR_HEIGHT, 0.1f, 65.0f); // TODO nie mo�e by� na sztywno
	glm::mat4 view = CAMERA.GetViewMatrix();
	GenerateFrustum(projection * view);
}

void Frustum::GenerateFrustum(glm::mat4 pvMatrix)
{

	_planes[FRUSTUM_RIGHT]->_normal.x = pvMatrix[0][3] - pvMatrix[0][0];
	_planes[FRUSTUM_RIGHT]->_normal.y = pvMatrix[1][3] - pvMatrix[1][0];
	_planes[FRUSTUM_RIGHT]->_normal.z = pvMatrix[2][3] - pvMatrix[2][0];
	_planes[FRUSTUM_RIGHT]->_distance = pvMatrix[3][3] - pvMatrix[3][0];

	_planes[FRUSTUM_LEFT]->_normal.x = pvMatrix[0][3] + pvMatrix[0][0];
	_planes[FRUSTUM_LEFT]->_normal.y = pvMatrix[1][3] + pvMatrix[1][0];
	_planes[FRUSTUM_LEFT]->_normal.z = pvMatrix[2][3] + pvMatrix[2][0];
	_planes[FRUSTUM_LEFT]->_distance = pvMatrix[3][3] + pvMatrix[3][0];

	_planes[FRUSTUM_DOWN]->_normal.x = pvMatrix[0][3] + pvMatrix[0][1];
	_planes[FRUSTUM_DOWN]->_normal.y = pvMatrix[1][3] + pvMatrix[1][1];
	_planes[FRUSTUM_DOWN]->_normal.z = pvMatrix[2][3] + pvMatrix[2][1];
	_planes[FRUSTUM_DOWN]->_distance = pvMatrix[3][3] + pvMatrix[3][1];

	_planes[FRUSTUM_UP]->_normal.x = pvMatrix[0][3] - pvMatrix[0][1];
	_planes[FRUSTUM_UP]->_normal.y = pvMatrix[1][3] - pvMatrix[1][1];
	_planes[FRUSTUM_UP]->_normal.z = pvMatrix[2][3] - pvMatrix[2][1];
	_planes[FRUSTUM_UP]->_distance = pvMatrix[3][3] - pvMatrix[3][1];

	_planes[FRUSTUM_FAR]->_normal.x = pvMatrix[0][3] - pvMatrix[0][2];
	_planes[FRUSTUM_FAR]->_normal.y = pvMatrix[1][3] - pvMatrix[1][2];
	_planes[FRUSTUM_FAR]->_normal.z = pvMatrix[2][3] - pvMatrix[2][2];
	_planes[FRUSTUM_FAR]->_distance = pvMatrix[3][3] - pvMatrix[3][2];

	_planes[FRUSTUM_NEAR]->_normal.x = pvMatrix[0][3] + pvMatrix[0][2];
	_planes[FRUSTUM_NEAR]->_normal.y = pvMatrix[1][3] + pvMatrix[1][2];
	_planes[FRUSTUM_NEAR]->_normal.z = pvMatrix[2][3] + pvMatrix[2][2];
	_planes[FRUSTUM_NEAR]->_distance = pvMatrix[3][3] + pvMatrix[3][2];

	for (int i = 0; i < 6; i++) _planes[i]->Normalize();
}

bool Frustum::CheckSphereIntersection(glm::vec3 center, float radius)
{
	for (int i = 0; i < 6; i++)
	{
		// Plane-sphere intersection test. If p*n + d + r < 0 then we're outside the plane.
		if (glm::dot(center, _planes[i]->_normal) + _planes[i]->_distance + radius <= 0)
			return false;
	}

	// If none of the planes had the entity lying on its "negative" side then it must be
	// on the "positive" side for all of them. Thus the entity is inside or touching the frustum.
	return true;
}
