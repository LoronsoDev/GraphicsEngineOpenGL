#pragma once

#define GLAD_ONLY_HEADERS
#include"VBO.h"

class VAO
{
	public:
		GLuint ID;
		VAO();

		void LinkVBO(VBO VBO, GLuint layout);
		void Bind();
		void Unbind();
		void Delete();
		void LinkAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);

};


