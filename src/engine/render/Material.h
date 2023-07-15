#pragma once
#include <string>
#include "RenderProgram.h"
#include "Texture.h"

class Material
{
public:
	enum BlendMode
	{
		ALPHA,
		ADD,
		MULTIPLY
	};

private:
	RenderProgram* program;
	Texture* texture;
	RGBA color;
	uint8_t shininess;
	BlendMode blendMode;

public:
	bool hasColor = false;
	bool isAffectedByLight = true;
	bool isCulled = true;
	bool hasDepthBuffer = true;
	float alpha = 1.0f;
	
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

	virtual inline BlendMode getBlendMode() const
	{
		return blendMode;
	}

	virtual inline void setBlendMode(BlendMode blendMode)
	{
		this->blendMode = blendMode;
	}

	virtual inline bool getLighting() const
	{
		return isAffectedByLight;
	}

	virtual inline void setLighting(bool enableLighting)
	{
		isAffectedByLight = enableLighting;
	}

	virtual inline bool getCulling() const
	{
		return isCulled;
	}

	//Enable or disable polygon culling (for polygons not looking at camera)
	virtual inline void setCulling(bool enableCulling)
	{
		isCulled = enableCulling;
	}

	virtual inline bool getDepthWrite() const
	{
		return hasDepthBuffer;
	}

	//Enable or disable depth buffer
	virtual void setDepthWrite(bool enable)
	{
		hasDepthBuffer = enable;
	}


	virtual void loadPrograms(std::string vertexSrc, std::string fragment)=0;
	virtual void prepare() = 0;
};
