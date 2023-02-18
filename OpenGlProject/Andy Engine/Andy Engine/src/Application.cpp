

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "ShaderManager.h"
#include "Constants.h"
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Vector3.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "ECS/CubeRenderer.h"


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
    glScissor(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

}



int main(void)
{
    GLFWwindow* window;

   // Hello

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(512, 512, "Andy Engine", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback); // Screen Resize
    glfwSetCursorPosCallback(window, mouse_callback); // Mouse Move Delta
    glEnable(GL_DEPTH_TEST);

    if (glewInit() != GLEW_OK)
    {
        // Somthing went Wrong
        std::cout << "Error!" << std::endl;

    }// Init Glew


    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    /* GENERATE THE BUFFERS FOR THE GPU */
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);

    /* SETUP VERTEX ATTRIBUTES */

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
   
   

    /*SHADER SETUP*/

    std::string vertex_shader_path = SHADER_PATH + "Basic_Vertex.shader";     // Get Vertex Shader Path
    std::string fragment_shader_path = SHADER_PATH + "Basic_Fragment.shader";   // Get Fragment Shader Path

    Shader Basic = Shader(vertex_shader_path, fragment_shader_path); // Create Our Shader

    /* TEXTURES */
    unsigned int texture;
    glGenTextures(1, &texture);

    glBindTexture(GL_TEXTURE_2D, texture);

    // Set Texture Paramaters of curently Bound texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // Load actual Texture Data
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("wall.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Could Not Load Texture!" << std::endl;
    }
    stbi_image_free(data); // FREE MEMORY


    /* DELTA TIME */
    double frameStartTime = 0;
    double frameEndTime = 0;
    float dealtaTime = 0;

    Basic.use(); // don't forget to activate/use the shader before setting uniforms!
    glUniform1i(glGetUniformLocation(Basic.ID, "ourTexture"), 0);

    /* COMPONANT SETU{ */
    Transform myTran = Transform();
    myTran.position = glm::vec3(-0.5f, 0.0f, 0.0f);
    myTran.scale = glm::vec3(0.5f, 0.5f, 0.5f);

    Transform myTranTwo = Transform();
    myTranTwo.position = glm::vec3(0.5f, 0.0f, 0.0f);
    myTranTwo.scale = glm::vec3(0.5f, 0.5f, 0.5f);

    CubeRenderer myCube = CubeRenderer(&Basic, &myTran);
    CubeRenderer myCubeTwo = CubeRenderer(&Basic, &myTranTwo);


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        frameStartTime = glfwGetTime();

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        
        /*DRAW HERE*/

        /* MAKE CUBES ROTATE */
        myCube.transform->Rotate(myCube.transform->rotation + glm::vec3(0.5f, 0.2f, -0.05f));
        myCubeTwo.transform->Rotate(myCubeTwo.transform->rotation + glm::vec3(-0.3f, 0.01f, 0.6f));

        /* DRAW AND UPDATE TWO CUBES */
        myCube.Update();
        myCubeTwo.Update();


        glfwSwapBuffers(window);
        glfwPollEvents();

        /* GET DELTA TIME*/
        frameEndTime = glfwGetTime();
        dealtaTime = (frameEndTime - frameStartTime);

    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    ShaderManager::Dispose();
    return 0;
}


