#include "GLSLShader.h"

GLSLShaderProgram::GLSLShaderProgram(std::string srcPath, RenderTypes type)
{
	SetProgram(srcPath, type);
}

void GLSLShaderProgram::SetProgram(std::string srcPath, RenderTypes type)
{
	
	
	
}

void GLSLShaderProgram::LinkPrograms()
{
	/*this->shId = glCreateShader(this->type);
	glShaderSource(shId, 1, &source, nullptr);
	glCompileShader(shId);*/
}

std::string GLSLShaderProgram::CheckErrors()
{
	//GLint success = 1;
	//char* infoLog = new char[1024];
	//infoLog[0] = '\0';
	//glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
	//	std::cout << "Shader compilation failure:\n" << infoLog << "\n";
	//	// exit(-1);
	//}
	//errorMSGs += "\n" + std::string(infoLog);
	//return errorMSGs;
}

void GLSLShaderProgram::Use()
{
}

void GLSLShaderProgram::SetInt(std::string identifier, int newVal)
{
}

void GLSLShaderProgram::SetFloat(std::string identifier, float newVal)
{
}

void GLSLShaderProgram::SetVec3(std::string identifier, glm::vec3 newVec3)
{
}

void GLSLShaderProgram::SetVec4(std::string identifier, glm::vec4 newVec4)
{
}

void GLSLShaderProgram::SetMat4(std::string identifier, glm::mat4 newMat4)
{
}
