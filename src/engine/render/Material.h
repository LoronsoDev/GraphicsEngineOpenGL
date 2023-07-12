#pragma once
#include <string>
#include "RenderProgram.h"
#include "Texture.h"

class Material
{

private:
	RenderProgram* program;
	Texture* texture;
	RGBA color;
	uint8_t shininess;

public:
	bool hasColor = false;
	bool isAffectedByLight = false;

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

	virtual inline void setColor(RGBA  color)
	{
		hasColor = true;
		this->color = color;
	}
	virtual inline RGBA getColor() const
	{
		return(this->color);
	}

	virtual inline void setShininess(uint8_t shininess)
	{
		isAffectedByLight = true;
		this->shininess = shininess;
	}

	virtual inline float getShininess() const
	{
		return this->shininess;
	}

	virtual void loadPrograms(std::string vertexSrc, std::string fragment)=0;
	virtual void prepare() = 0;
};
