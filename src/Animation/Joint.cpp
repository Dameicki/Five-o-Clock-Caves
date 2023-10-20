#include "Joint.h"

Joint::Joint(std::string name, int id, glm::mat4 transform) : m_name(name), m_id(id), m_transform(m_transform)
{
	m_children = std::list<Joint>();
}

Joint::Joint()
{
}
