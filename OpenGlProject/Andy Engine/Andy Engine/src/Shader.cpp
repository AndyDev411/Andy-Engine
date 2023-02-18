#include "Shader.h"
#include "ShaderManager.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Shader::Shader(std::string vertexPath, std::string fragmentPath)
{
	ID = ShaderManager::LoadShader(vertexPath, fragmentPath);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setVec4(const std::string& name, float r, float g, float b, float a) const
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), r, g, b, a);
}

void Shader::setMatrix(const std::string& name, glm::mat4& trans)
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(trans));
}
