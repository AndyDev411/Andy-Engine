#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "ShaderManager.h"
#include <fstream>
#include <string>
#include <vector>

unsigned int ShaderManager::LoadShader(std::string& vertex_shader_path, std::string& fragment_shader_path)
{
    std::string vertex_shader_content = ParseFile(vertex_shader_path);     // Get Vertex Shader String
    std::string fragment_shader_content = ParseFile(fragment_shader_path); // Get Fragment Shader String
    unsigned int shaderID = CreateShader(vertex_shader_content, fragment_shader_content); // Create the Shader and get the ID
    return(shaderID); // Return the Shader

}


// PARSE THE FILEs
std::string ShaderManager::ParseFile(const std::string filePath) 
{
    std::ifstream file(filePath);
    std::string str;
    std::string content;
    while (std::getline(file, str)) {
        content.append(str + "\n");
    }
    return content;
}

unsigned int ShaderManager::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    //TODO: ERROR HANDLING
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        // ERROR
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to Compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);
        return 0;
    }

    return id;
}

unsigned int ShaderManager::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

void ShaderManager::Dispose()
{

}