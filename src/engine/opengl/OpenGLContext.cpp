#include "OpenGLContext.h"

void engine::OpenGL1Context::Init()
{
	glfwMakeContextCurrent(m_ContextWindow);
	gladLoadGL(glfwGetProcAddress);

	std::cout << " OPENGL CONTEXT CREATED SUCCESFULLY \n";
	std::cout << "    Vendor    | " << reinterpret_cast<const char*> (glGetString(GL_VENDOR)) << "\n";
	std::cout << "     GPU      | " << reinterpret_cast<const char*> (glGetString(GL_RENDERER)) << "\n";
	std::cout << "    Driver    | " << reinterpret_cast<const char*> (glGetString(GL_VERSION)) << "\n";

	// 3.30 OpenGL version. Not used for now.
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 30);
}

void engine::OpenGL1Context::SwapBuffers()
{
	glfwSwapBuffers(m_ContextWindow);
}

void engine::OpenGL1Context::SetupObject(Object* obj)
{
	std::cout << "OpenGL1Context::SetupObject not implemented \n";
}

void engine::OpenGL1Context::RemoveObject(Object* obj)
{
	std::cout << "OpenGL1Context::RemoveObject not implemented \n";
}

void engine::OpenGL1Context::DrawObjects(std::vector<Object*>* objs)
{
	glm::vec4 color(1.f, 1.f, 1.f, 1.f);
	glBegin(GL_TRIANGLES);
	glColor3f(color.r, color.g, color.b);

	for (auto obj : *objs)
	{
		auto vertices = obj->GetMesh()->GetVertList();

		for (Vertex v : *vertices)
		{
			v.VertexPos = obj->GetModelMatrix() * v.VertexPos;

			auto color = obj->GetMesh()->GetMeshColor();
			glColor3f(color.x, color.y, color.z);
			glVertex3f(v.VertexPos.x, v.VertexPos.y, v.VertexPos.z);
		}
	}

	glEnd();
}

//void GL1Render::DrawObjects(const std::vector<Object*>* objects)
//{
//	glm::vec4 color(1.f, 1.f, 1.f, 1.f);
//	glBegin(GL_TRIANGLES);
//	glColor3f(color.r, color.g, color.b);
//	for (Object* object : *(objects))
//	{
//		for (Vertex vertex : *(object->GetMesh()->GetVertList()))
//		{
//			vertex.position = object->GetModelMatrix() * vertex.position;
//			glColor3f(vertex.color.r, vertex.color.g, vertex.color.b);
//			glVertex3f(vertex.position.x, vertex.position.y, vertex.position.z);
//		}
//	}
//	glEnd();
//}
