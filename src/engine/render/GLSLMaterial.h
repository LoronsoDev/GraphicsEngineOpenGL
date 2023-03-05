#pragma once
#define GLAD_ONLY_HEADERS

#include "Material.h"
#include "GLSLShader.h"

class GLSLMaterial : public Material
{
public:
	void loadPrograms(std::string vertexSrc, std::string fragmentSrc) override;
	void prepare() override;
	void use();
private:
	GLSLShader* program;
};

