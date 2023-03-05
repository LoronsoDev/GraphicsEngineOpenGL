#pragma once

#define GLAD_ONLY_HEADERS
#include <engine/render/Texture.h>

class GLTexture : public Texture
{
public:
	GLTexture(TextureType type)
	{
		this->textureType = type;
	}

public:
	void Load(std::string fileName) override;
	unsigned int GetID() override { return ID; }
	glm::ivec2 GetSize() override;
	void Bind(unsigned int textureUnit) override;
};

