#pragma once
#include <string>
#include "RenderProgram.h"
#include "Texture.h"

class Material
{

private:
	RenderProgram* program;
	Texture* texture;

public:
	inline void setProgram(RenderProgram* program)
	{
		this->program = program;
	}
	inline RenderProgram* getProgram()
	{
		return this->program;
	}
	virtual inline void setTexture(Texture * texture)
	{
		this->texture = texture;
	}
	virtual inline Texture * getTexture()
	{
		return this->texture;
	}

	virtual void loadPrograms(std::string vertexSrc, std::string fragment)=0;
	virtual void prepare() = 0;
};
