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

	bool isDynamicObject = false; //If this object is a visualizer, it's only in the scene for representation and it's managed by another entity.
	std::vector<Mesh3D*> GetMeshes();
	void AddMesh(Mesh3D* mesh);
	unsigned int numMeshes = 0;

	virtual void LoadDataFromFile(std::string file) = 0;
private:
	std::vector<Mesh3D*> m_Meshes;
	ObjectType m_Type;
};
