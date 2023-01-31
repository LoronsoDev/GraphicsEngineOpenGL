#pragma once

#include <Engine_Core.h>
#include <engine/base/Shader.h>


class GLSLShader : public Shader
{
public:
	GLSLShader(std::string srcPath) : Shader(srcPath) {}
	GLSLShader(std::string srcPath, RenderTypes type) : Shader(srcPath, type) {}
};

class GLSLShaderProgram : public RenderProgram
{
private:
	std::vector<GLSLShader> shaders;

public:
	virtual void LinkPrograms() override;
	virtual std::string CheckErrors() override;
	virtual void Use() override;
	virtual void SetInt(std::string identifier, int newVal) override;
	virtual void SetFloat(std::string identifier, float newVal) override;
	virtual void SetVec3(std::string identifier, glm::vec3 newVec3) override;
	virtual void SetVec4(std::string identifier, glm::vec4 newVec4) override;
	virtual void SetMat4(std::string identifier, glm::mat4 newMat4) override;

public:
	GLSLShaderProgram() = default;
};

