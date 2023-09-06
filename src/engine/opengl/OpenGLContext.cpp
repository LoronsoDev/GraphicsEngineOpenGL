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

void engine::OpenGL1Context::SetupLighting(std::vector<Light*>* lights, glm::vec3 * ambient)
{
	std::cout << "OpenGL1Context::SetupLighting not implemented \n";
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

void engine::OpenGL4Context::SetupLighting(std::vector<Light*>* lights, glm::vec3 * ambient)
{
	this->ambient = ambient;
	this->lights = lights;

	for(Light * l : *lights)
	{
		OpenGLImGUI::ModifiableIngameItem* uiItem = new OpenGLImGUI::ModifiableIngameItem;
		uiItem->item_type_id = l->name;
		uiItem->userPos = l->position;
		uiItem->userRot = glm::vec4(l->direction.x, l->direction.y, l->direction.z, 1.0f);
		uiItem->userScale.x = l->linearAttenuation;
		uiItem->userScale.y = l->quadraticAttenuation;
		uiItem->userScale.z = l->intensity;
		uiItem->auxValues = glm::vec4(l->color.x, l->color.y, l->color.z, 1.0f);
		UI->sceneLights.push_back(uiItem);
	}
}

void engine::OpenGL4Context::SetupObject(Object* obj)
{
	if (!obj->isVisualizer)
	{
		OpenGLImGUI::ModifiableIngameItem* uiItem = new OpenGLImGUI::ModifiableIngameItem;
		uiItem->item_type_id = obj->name;
		uiItem->userPos = obj->GetPos();
		uiItem->userRot = obj->GetRot();
		uiItem->userScale = obj->GetScale();
		uiItem->uniformScale = (uiItem->userScale.x + uiItem->userScale.y + uiItem->userScale.z) / 3; //set uniform scale to the average of the vector
		UI->sceneObjects.push_back(uiItem);
	}


	for(const auto & mesh : obj->GetMeshes())
	{
		Material* mat = mesh->getMaterial();
		mat->prepare();

		RenderProgram* program = mat->getProgram();
		program->use();

		Texture* texture = mat->getTexture();
		RGBA color = mat->getColor();

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

		if (mat->hasColor) //if color has been set
		{
			glEnableVertexAttribArray(program->shaderProgramVars["vColor"]);
			glVertexAttribPointer(program->shaderProgramVars["vColor"], 4, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (void*)offsetof(Vertex, color));

		}

		if(mat->isAffectedByLight)
		{
			glEnableVertexAttribArray(program->shaderProgramVars["vNormal"]);
			glVertexAttribPointer(program->shaderProgramVars["vNormal"], 4, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (void*)offsetof(Vertex, normal));
		}

		if (texture)
		{
			glEnableVertexAttribArray(program->shaderProgramVars["vTextureUV"]);
			glVertexAttribPointer(program->shaderProgramVars["vTextureUV"], 2, GL_FLOAT, GL_FALSE,
				sizeof(Vertex), (void*)offsetof(Vertex, textureUV));
		}


		glBindVertexArray(0);

		if (texture)
		{
			program->setInt("textureColor", 0);
			texture->Load();
			texture->Bind(0);
		}
	}
	
}

void engine::OpenGL4Context::RemoveObject(Object* obj)
{

}

void engine::OpenGL4Context::DrawObjects(std::vector<Object*>* objs)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	UI->Update();

	int numLight = 0;
	for (auto& l : *lights)
	{
		if (!l->manualControl)
		{
			UI->sceneLights[numLight]->userPos = l->position;

			if (l->sceneVisualizer)
			{
				auto& obj = l->sceneVisualizer;

				obj->SetPos(l->position);
				obj->SetRot(glm::vec4(l->direction.x, l->direction.y, l->direction.z, 1.0f));

				l->linearAttenuation = UI->sceneLights[numLight]->userScale.x;
				l->quadraticAttenuation = UI->sceneLights[numLight]->userScale.y;
				l->intensity = UI->sceneLights[numLight]->userScale.z;
				l->color = UI->sceneLights[numLight]->auxValues;
				l->specularColor = UI->sceneLights[numLight]->auxValues;

			}

			continue;
		}


		l->position = UI->sceneLights[numLight]->userPos;
		l->direction = UI->sceneLights[numLight]->userRot;
		l->linearAttenuation = UI->sceneLights[numLight]->userScale.x;
		l->quadraticAttenuation = UI->sceneLights[numLight]->userScale.y;
		l->intensity = UI->sceneLights[numLight]->userScale.z;
		l->color = UI->sceneLights[numLight]->auxValues;
		l->specularColor = UI->sceneLights[numLight]->auxValues;

		if (l->sceneVisualizer)
		{
			auto& obj = l->sceneVisualizer;

			obj->SetPos(l->position);
			obj->SetRot(glm::vec4(l->direction.x, l->direction.y, l->direction.z, 1.0f));

		}

		
		
		numLight++;
	}

	int numObject = 0;
	for(auto & obj: *objs)
	{
		if(!obj->isVisualizer)
		{
			obj->SetPos(UI->sceneObjects[numObject]->userPos);
			obj->SetRot(UI->sceneObjects[numObject]->userRot);
			obj->SetScale(UI->sceneObjects[numObject]->userScale);

			numObject++;
		}
		
		//obj->LoadDataFromFile(UI->userPath);

		for(auto & mesh : obj->GetMeshes())
		{
			auto vbo = bufferObjectList[mesh->GetMeshID()];

			Material* m = mesh->getMaterial();
			RenderProgram* p = m->getProgram();

			p->use();
			
			glm::mat4 MVP = m_MainCamera->getProjection() * m_MainCamera->getView() * obj->GetModelMatrix();

			p->setMat4("MVP", MVP);
			if(mesh->getMaterial()->isAffectedByLight)
			{
				p->setMat4("M", obj->GetModelMatrix()); //Necessary for normals computation

				for(int i = 0; i < lights->size(); ++i)
				{
					Light * light = (*lights)[i];
					int type = static_cast<int>(light->getType());
					glm::vec3 col = light->getColor();
					glm::vec4 color = glm::vec4(col.r, col.g, col.b, 1.f);
					float linAtt = light->getLinearAttenuation();

					p->setInt("numLights", lights->size());
					std::string light_str = "lights[" + std::to_string(i) + "]";

					p->setFloat(light_str + (".intensity"), light->intensity);
					p->setInt(light_str		+ (".type"), type);
					p->setVec4(light_str	+ (".color"), color);
					p->setFloat(light_str + (".quadraticAttenuation"), light->quadraticAttenuation);
					p->setFloat(light_str	+ (".linearAttenuation"), linAtt);
					p->setVec3(light_str	+ (".position"), light->position);
					p->setVec3(light_str	+ (".direction"), glm::normalize(- light->direction));
					p->setVec3(light_str + (".specularColor"), light->specularColor);
				}

				auto viewPos = m_MainCamera->GetPos();

				p->setVec4("viewPos", glm::vec4(viewPos.x, viewPos.y, viewPos.z, 1.0f));
				p->setFloat("shininess", m->getShininess());
				p->setVec3("ambient", *ambient);
			}

			Texture* texture = mesh->getMaterial()->getTexture();
			//dibujado
			glBindVertexArray(vbo.boId);

			if(texture)
			{
				texture->Bind(0);
			}

			glDrawElements(GL_TRIANGLES, mesh->GetIdBufferList()->size(),
				GL_UNSIGNED_INT, nullptr);

			if(texture)
			{
				texture->Unbind();
			}
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
