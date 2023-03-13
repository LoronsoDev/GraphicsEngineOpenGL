#pragma once
#define GLAD_ONLY_HEADERS

#include <engine/render/Mesh3D.h>
#include <engine/render/Material.h>
#include <engine/opengl/GLSLShader.h>

class GLSLMaterial : public Material
{
public:
	void loadPrograms(std::string vertexSrc, std::string fragmentSrc) override;
	void prepare() override;
	void use();
private:
	GLSLShader* program;
};

