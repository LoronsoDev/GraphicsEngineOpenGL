#pragma once

#include <Engine_Core.h>

enum RenderTypes
{
	UNKNOWN = -1,
	VERTEX = 0,
	FRAGMENT = 1,
};

class Shader
{
public:

	std::string srcPath = "EMPTY PATH TO CODE";
	RenderTypes type = (RenderTypes)-1;

	std::string code = "EMPTY CODE";

	//Sets type from source code extension (.FRG, .VTX)
	Shader(std::string srcPath);
	Shader(std::string srcPath, RenderTypes type);

private:
	virtual void ParseSourceCode();
};

class RenderProgram
{
public:
	RenderTypes renderType;
	std::vector<Shader> shaderBuffer;

	/// <summary>
	/// Adds shader to the shader buffer
	/// </summary>
	/// <param name="shader">shader to add to buffer</param>
	virtual void PushShader(Shader shader) = 0;

	/// <summary>
	/// Compiles and links all source code in the program.
	/// </summary>
	virtual void LinkPrograms() = 0;

	/// <summary>
	/// Checks for any errors in the compilation/linking of the source code
	/// </summary>
	/// <returns>Error description (empty if no errors).</returns>
	virtual std::string CheckErrors() = 0;

	/// <summary>
	/// Sets this program as active for next render pass.
	/// </summary>
	virtual void Use() = 0;

	virtual void SetInt		(std::string identifier, int newVal) = 0;
	virtual void SetFloat	(std::string identifier, float newVal) = 0;
	virtual void SetVec3	(std::string identifier, glm::vec3 newVec3) = 0;
	virtual void SetVec4	(std::string identifier, glm::vec4 newVec4) = 0;
	virtual void SetMat4	(std::string identifier, glm::mat4 newMat4) = 0;
};

