#include "CubeRenderer.h"
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
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "../Transform.h"

const GLfloat CubeRenderer::g_vertex_buffer_data[] = {
    // positions          // colors           // texture coords
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 1.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 0.0f,

     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 1.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 1.0f,
     0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 1.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 0.0f,
     0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 1.0f,
     0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 1.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 0.0f,
     0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,    1.0f, 0.0f, 0.0f,      0.0f, 1.0f
};

const int CubeRenderer::indicies[] = {
0, 1, 3,
1, 2, 3,
};

CubeRenderer::CubeRenderer(Shader* toUse)
{
    SetupMesh(toUse);
}
CubeRenderer::CubeRenderer(Shader* toUse, Transform* myTransorm)
{
    SetupMesh(toUse);
    SetTransform(myTransorm);
}

void CubeRenderer::SetupMesh(Shader* toUse)
{

    SetMeterial(toUse);

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // SET VERTEX AND INDICIES
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);


    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    model = glm::mat4(1);

    view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}

void CubeRenderer::Update()
{
    DrawMesh();
}

void CubeRenderer::DrawMesh()
{

    DrawMesh(material);


}

void CubeRenderer::DrawMesh(Shader* toUse)
{
    toUse->use();

    glm::mat4 model = glm::mat4(1.0f);
    if (transform != nullptr)
    {
        model = glm::translate(model, transform->position); // Set Position

        model = glm::rotate(model, glm::radians(transform->rotation.x), glm::vec3(1.0f, 0.0f, 0.0f)); // X
        model = glm::rotate(model, glm::radians(transform->rotation.y), glm::vec3(0.0f, 1.0f, 0.0f)); // Y
        model = glm::rotate(model, glm::radians(transform->rotation.z), glm::vec3(0.0f, 0.0f, 1.0f)); // Z

        model = glm::scale(model, transform->scale);
    }

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f)); // Draw In Correct Position

    glm::mat4 projection;
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

    toUse->setMatrix("model", model);
    toUse->setMatrix("view", view);
    toUse->setMatrix("projection", projection);

    glDrawArrays(GL_TRIANGLES, 0, 36);
    

}

void CubeRenderer::DrawMesh(Shader* toUse, glm::vec3 pos)
{
    toUse->use(); // Set the Material

    toUse->setMatrix("model", model);
    toUse->setMatrix("view", view);
    toUse->setMatrix("projection", projection);

    glDrawArrays(GL_TRIANGLES, 0, 36);

}

void CubeRenderer::RotateMesh(glm::vec3 toRot, float angle)
{
    model = glm::rotate(model, glm::radians(angle), toRot);
}

void CubeRenderer::SetMeterial(Shader* toUse)
{
    material = toUse;
}

void CubeRenderer::TranslateMesh(glm::vec3 toPos)
{
    model = glm::translate(model, toPos);
}
