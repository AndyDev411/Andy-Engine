#ifndef CUBERENDERER_H
#define CUBERENDERER_H

#include <iostream>
#include "../Componant.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "../ShaderManager.h"
#include "../Constants.h"
#include "../Shader.h"
#include "../Vector3.h"
#include "../Shader.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../Transform.h"


class CubeRenderer : public Componant {

public :
	static const GLfloat g_vertex_buffer_data[];
	static const int indicies[];
	Shader* material;
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;


	 CubeRenderer(Shader* toUse);

	 CubeRenderer(Shader* toUse, Transform* myTransorm);

	 void SetupMesh(Shader* toUse);

	 void DrawMesh();

	 void DrawMesh(Shader* toUse);

	 void DrawMesh(Shader* toUse, glm::vec3 pos);

	 void RotateMesh(glm::vec3 toRot, float angle);

	 void TranslateMesh(glm::vec3 toPos);

	 void SetMeterial(Shader* toSet);

	 void Update() override;

};


#endif // !CUBERENDERER_H
