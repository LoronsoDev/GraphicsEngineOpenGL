#include "OpenGLContext.h"

#include "engine/render/GLSLMaterial.h"

void engine::OpenGL1Context::Init(Window* window)
{
	m_ContextWindow = reinterpret_cast<GLFWwindow*>(window);

	glfwMakeContextCurrent(m_ContextWindow);
	gladLoadGL(glfwGetProcAddress);

	std::cout << " OPENGL CONTEXT CREATED SUCCESFULLY \n";
	std::cout << " CONTEXT RUNNING OPENGL1 \n";
	std::cout << "    Vendor    | " << reinterpret_cast<const char*> (glGetString(GL_VENDOR)) << "\n";
	std::cout << "     GPU      | " << reinterpret_cast<const char*> (glGetString(GL_RENDERER)) << "\n";
	std::cout << "  GL VERSION  | " << reinterpret_cast<const char*> (glGetString(GL_VERSION)) << "\n";

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
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glBegin(GL_TRIANGLES);

	for (auto obj : *objs)
	{
		const auto vertices = obj->GetMesh()->GetVertList();

		for (Vertex v : *vertices)
		{
			v.VertexPos = obj->GetModelMatrix() * v.VertexPos;

			auto color = obj->GetMesh()->GetMeshColor();
			glColor3f(v.VertexPos.x, v.VertexPos.y, v.VertexPos.z); //Purposefully inputted vertex position.
			glVertex3f(v.VertexPos.x, v.VertexPos.y, v.VertexPos.z);
		}
	}

	glEnd();

	SwapBuffers();
}

bool engine::OpenGL1Context::IsClosed()
{
	return false;
}

int engine::OpenGL1Context::GetWidth()
{
	return 0;
}

int engine::OpenGL1Context::GetHeight()
{
	return 0;
}

/*
 *
 *	--- OPENGL4 ---
 *
 */

void engine::OpenGL4Context::Init(Window* window)
{
	m_ContextWindow = reinterpret_cast<GLFWwindow*>(window);

	glfwMakeContextCurrent(m_ContextWindow);
	gladLoadGL(glfwGetProcAddress);

	std::cout << " OPENGL CONTEXT CREATED SUCCESFULLY \n";
	std::cout << " CONTEXT RUNNING OPENGL4 \n";
	std::cout << "    Vendor    | " << reinterpret_cast<const char*> (glGetString(GL_VENDOR)) << "\n";
	std::cout << "     GPU      | " << reinterpret_cast<const char*> (glGetString(GL_RENDERER)) << "\n";
	std::cout << "  GL VERSION  | " << reinterpret_cast<const char*> (glGetString(GL_VERSION)) << "\n";
}

void engine::OpenGL4Context::SwapBuffers()
{
	glfwSwapBuffers(m_ContextWindow);
}

void engine::OpenGL4Context::SetupObject(Object* obj)
{
	Mesh3D* mesh = obj->GetMesh();
	Material * mat = mesh->getMaterial();
	mat->prepare();
	mat->getProgram()->use();

	VBO_t vbo;
	glGenVertexArrays(1, &vbo.boId);

	glGenBuffers(1, &vbo.vbo);
	glGenBuffers(1, &vbo.idxbo);

	glBindBuffer(GL_ARRAY_BUFFER, vbo.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->GetVertList()->size(),
		mesh->GetVertList()->data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.idxbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->GetIdBufferList()->size(),
		mesh->GetIdBufferList()->data(), GL_STATIC_DRAW);

	bufferObjectList[mesh->GetMeshID()] = vbo;
}

void engine::OpenGL4Context::RemoveObject(Object* obj)
{

}

void engine::OpenGL4Context::DrawObjects(std::vector<Object*>* objs)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	for(auto obj: *objs)
	{
		Mesh3D* mesh = obj->GetMesh();
		Material* m = mesh->getMaterial();
		RenderProgram* p = m->getProgram();
		VBO_t buffer = this->bufferObjectList[mesh->GetMeshID()];

		glBindVertexArray(buffer.boId);
		glBindBuffer(GL_ARRAY_BUFFER, buffer.vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.idxbo);
		p->use();
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)0x00);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)(sizeof(glm::vec4) + sizeof(glm::vec4)));

		glm::mat4 MVP = obj->GetModelMatrix();
		p->setMat4("mMat", MVP);

		//dibujado
		glDrawElements(GL_TRIANGLES, mesh->GetIdBufferList()->size(),
			GL_UNSIGNED_INT, nullptr);

	}
	glEnd();

	SwapBuffers();
	
}

bool engine::OpenGL4Context::IsClosed()
{
	return false;
}

int engine::OpenGL4Context::GetWidth()
{
	return 0;
}

int engine::OpenGL4Context::GetHeight()
{
	return 0;
}
