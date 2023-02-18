#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm.hpp>

class Transform {
	public :
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;

		Transform();
		~Transform();
		void Rotate(glm::vec3 p_rotation);
		void Translate(glm::vec3 p_position);
		void Scale(glm::vec3 p_scale);
		glm::vec3 GetPosition();
		glm::vec3 GetRotation();
		glm::vec3 GetScale();

	protected:

};


#endif



