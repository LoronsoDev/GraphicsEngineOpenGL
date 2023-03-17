#include "OpenGLContext.h"

void engine::OpenGL1Context::Init(Window* window)
{
	m_RenderWindow = window;
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

	for (const auto & obj : *objs)
	{
		for(auto mesh : obj->GetMeshes())
		{
			const auto vertices = mesh->GetVertList();

			for (Vertex v : *vertices)
			{
				v.pos = obj->GetModelMatrix() * v.pos;

				auto color = mesh->GetMeshColor();
				glColor3f(v.pos.x, v.pos.y, v.pos.z); //Purposefully inputted vertex position.
				glVertex3f(v.pos.x, v.pos.y, v.pos.z);
			}
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
	m_RenderWindow = window;
	m_ContextWindow = (GLFWwindow*) window->GetNativeWindow();

	glfwMakeContextCurrent(m_ContextWindow);
	gladLoadGL(glfwGetProcAddress);

	//UI CREATE CONTEXT
	UI = std::make_unique<OpenGLImGUI>(OpenGLImGUI());
	UI->CreateContext(window);
	UI->Init();

	glEnable(GL_DEPTH_TEST);

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

void engine::OpenGL4Context::SetupCamera(Camera* cam, bool isMainCam)
{
	cam->computeViewMatrix();

	if(isMainCam)
		m_MainCamera = cam;
}

void engine::OpenGL4Context::SetupObject(Object* obj)
{
	for(const auto & mesh : obj->GetMeshes())
	{
		Material* mat = mesh->getMaterial();
		mat->prepare();

		RenderProgram* program = mat->getProgram();
		program->use();

		Texture* texture = mat->getTexture();
		
		glGenVertexArrays(1, &vbo.boId);
		glGenBuffers(1, &vbo.vbo);
		glGenBuffers(1, &vbo.idxbo);
		glBindVertexArray(vbo.boId);
		glBindBuffer(GL_ARRAY_BUFFER, vbo.vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.idxbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->GetVertList()->size(),
			mesh->GetVertList()->data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo.idxbo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * mesh->GetIdBufferList()->size(),
			mesh->GetIdBufferList()->data(), GL_STATIC_DRAW);

		bufferObjectList[mesh->GetMeshID()] = vbo;

		glEnableVertexAttribArray(program->shaderProgramVars["vPos"]);
		glVertexAttribPointer(program->shaderProgramVars["vPos"], 4, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)offsetof(Vertex, pos));

		//Commented out as it's getting optimized by GLSL (variable not used).
		/*glEnableVertexAttribArray(p->shaderProgramVars["vColor"]);
		glVertexAttribPointer(p->shaderProgramVars["vColor"], 4, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)offsetof(Vertex, color));*/

		glEnableVertexAttribArray(program->shaderProgramVars["vTextureUV"]);
		glVertexAttribPointer(program->shaderProgramVars["vTextureUV"], 2, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)offsetof(Vertex, textureUV));


		glBindVertexArray(0);

		program->setInt("textureColor", 0);
		texture->Load();
		texture->Bind(0);

	}
	
}

void engine::OpenGL4Context::RemoveObject(Object* obj)
{

}

void engine::OpenGL4Context::DrawObjects(std::vector<Object*>* objs)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	UI->Update();

	for(auto & obj: *objs)
	{
		obj->SetPos(UI->userPos);
		obj->SetRot(UI->userRot);
		obj->SetScale(UI->userScale);

		//obj->LoadDataFromFile(UI->userPath);

		for(auto & mesh : obj->GetMeshes())
		{
			auto vbo = bufferObjectList[mesh->GetMeshID()];

			Material* m = mesh->getMaterial();
			RenderProgram* p = m->getProgram();

			p->use();
			
			glm::mat4 MVP = m_MainCamera->getProjection() * m_MainCamera->getView() * obj->GetModelMatrix();

			p->setMat4("MVP", MVP);

			Texture* texture = mesh->getMaterial()->getTexture();
			//dibujado
			glBindVertexArray(vbo.boId);
			texture->Bind(0);

			glDrawElements(GL_TRIANGLES, mesh->GetIdBufferList()->size(),
				GL_UNSIGNED_INT, nullptr);

			texture->Unbind();
			glBindVertexArray(0);
		}
	}

	UI->Render();

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
