#pragma once

#include <Engine_Core.h>

class Texture
{
public:
	enum TextureType
	{
		NORMAL,
		COLOR2D,
		CUBE3D,
		UNDEFINED
	};
protected:
	const char* texturePath = "";
	unsigned int ID = 0;
	TextureType textureType = COLOR2D;
	glm::ivec2 size = {0,0};

public:
	Texture(const char* path) : texturePath(path) {}

	virtual ~Texture() = default;
	/**
	 * \brief Loads texture from file
	 * \param fileName path to texture file
	 */
	virtual void Load(std::string fileName) = 0;
	/**
	 * \brief
	 * \return ID of the texture in the shader program 
	 */
	virtual unsigned int GetID() = 0;
	/**
	 * \brief 
	 * \return Width and height of the texture in pixels
	 */
	virtual glm::ivec2 GetSize() = 0;
	/**
	 * \brief "Next render passes will use this texture."
	 */
	virtual void Bind(unsigned int textureUnit) = 0;
};
