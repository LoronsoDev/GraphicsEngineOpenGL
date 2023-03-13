#include <engine/opengl/GLTexture.h>
#include <engine/utils/stb_image.h>
#include <engine/utils/EngineUtils.h>

void GLTexture::Load(std::string fileName)
{
	//out from stbi_load
	int channels = 0;
	//
	stbi_set_flip_vertically_on_load(true);
	RGBA_8888 * image = (RGBA_8888*) stbi_load(fileName.c_str(), &size.x, &size.y, &channels, 4);

	if (!image) std::cout << "ENGINE ERROR: The texture path couldn't be read.";

	const auto size = GetSize();

	glGenTextures(1, &ID); //stores texture ID
	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(image);
}

void GLTexture::Bind(unsigned int textureUnit)
{
	auto id = GetID();

	switch (textureType)
	{
	case NORMAL:
	case COLOR2D:
		glBindTexture(GL_TEXTURE_2D, id);
		break;
	case CUBE3D:
		glBindTexture(GL_TEXTURE_CUBE_MAP, id);
		break;
	}

	glActiveTexture(GL_TEXTURE0 + textureUnit);
}
