#pragma once

#define GLAD_ONLY_HEADERS
#include <engine/render/Texture.h>

#include "engine/render/Texture.h"

class GLTexture : public Texture
{
public:
	GLTexture(const char* path, const TextureType type = TextureType::COLOR2D) : Texture(path)
	{
		this->textureType = type;
	}

public:
	void Load() override;
	unsigned int GetID() override { return ID; }
	glm::ivec2 GetSize() override { return size; };
	void Bind(unsigned int textureUnit) override;
	void Unbind() override;
};

