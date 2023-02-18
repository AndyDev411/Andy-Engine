#pragma once
#ifndef SHADERMANAGER
#define SHADERMANAGER

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <vector>

class ShaderManager {
	public :
		// Functions

		static unsigned int LoadShader(std::string& shader_path, std::string& fragment_shader_path);
		static std::string ParseFile(const std::string filePath);

		static unsigned int CompileShader(unsigned int type, const std::string& source);

		static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

		static void Dispose();

};




#endif