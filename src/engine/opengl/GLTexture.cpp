#include <engine/opengl/GLTexture.h>
#include <engine/utils/stb_image.h>
#include <engine/utils/EngineUtils.h>

void GLTexture::Load(std::string fileName)
{
	//out from stbi_load
	int* x = nullptr;
	int* y = nullptr;
	int* channels = nullptr;
	//

	RGBA_8888 * image = (RGBA_8888*) stbi_load(fileName.c_str(), x, y, channels, 4);
	
	auto id = GetID();
	auto size = GetSize();

	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);



	stbi_image_free(image);
}

void GLTexture::Bind(unsigned int textureUnit)
{
	glActiveTexture(GL_TEXTURE0 + textureUnit);

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
}
