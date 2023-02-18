#include "Transform.h"
#include <glm.hpp>

Transform::Transform()
{
	position = glm::vec3(0.0f);
	rotation = glm::vec3(1.0f);
	scale = glm::vec3(1.0f);
}

Transform::~Transform()
{
}

void Transform::Rotate(glm::vec3 p_rotation)
{
	rotation = p_rotation;
}

void Transform::Translate(glm::vec3 p_position)
{
	position += p_position;
}

void Transform::Scale(glm::vec3 p_scale)
{
	scale = p_scale;
}

glm::vec3 Transform::GetPosition()
{
	return position;
}

glm::vec3 Transform::GetRotation()
{
	return rotation;
}

glm::vec3 Transform::GetScale()
{
	return scale;
}
