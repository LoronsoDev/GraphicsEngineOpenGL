#include "Object.h"

Object::Object()
{
}

std::vector<Mesh3D*> Object::GetMeshes()
{
	return m_Meshes;
}

void Object::AddMesh(Mesh3D* m)
{
	++numMeshes;
	m_Meshes.push_back(m);
}