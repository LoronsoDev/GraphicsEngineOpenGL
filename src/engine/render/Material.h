#pragma once
#include <string>
#include "RenderProgram.h"
class Material
{

private:
	RenderProgram* program;
public:
	inline void setProgram(RenderProgram* program)
	{
		this->program = program;
	}
	inline RenderProgram* getProgram()
	{
		return this->program;
	}
	virtual void loadPrograms(std::string vertexSrc, std::string fragment)=0;
	virtual void prepare() = 0;
};
