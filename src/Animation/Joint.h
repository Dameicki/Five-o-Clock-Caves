#pragma once


#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/quaternion.hpp>

#include <list>
#include <string>

class Joint
{
public:
	Joint(std::string name, int id, glm::mat4 transform);
	Joint();

private:
	std::string m_name;
	std::list<Joint> m_children;
	int m_id;
	glm::mat4 m_transform;
};
