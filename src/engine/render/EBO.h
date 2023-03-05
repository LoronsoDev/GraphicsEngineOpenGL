#pragma once

#define GLAD_ONLY_HEADERS

#include <Engine_Core.h>

class EBO
{
public:
	GLuint ID;
	EBO(GLuint* indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();

};

