#pragma once

#include <scene/Entity.h>
#include <engine/render/Mesh3D.h>

#include <Engine_Core.h>

enum ObjectType
{
	TRIANGLE
};

class Object : public Entity
{
public:
	Object();

	std::vector<Mesh3D*> GetMeshes();
	void AddMesh(Mesh3D* mesh);
	unsigned int numMeshes = 0;

	virtual void LoadDataFromFile(std::string file) = 0;
private:
	std::vector<Mesh3D*> m_Meshes;
	ObjectType m_Type;
};
