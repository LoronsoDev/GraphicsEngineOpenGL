#include "GLSLMaterial.h"



void GLSLMaterial::loadPrograms(std::string vertexSrc, std::string fragmentSrc)
{
	setProgram(new GLSLShader());
	program = static_cast<GLSLShader*>( getProgram() );
	program->setProgram(vertexSrc, RenderProgram::renderTypes_e::vertex);
	program->setProgram(fragmentSrc, RenderProgram::renderTypes_e::fragment);
}

void GLSLMaterial::prepare()
{
	program->linkPrograms();
}

void GLSLMaterial::use()
{
	program->use();
}
