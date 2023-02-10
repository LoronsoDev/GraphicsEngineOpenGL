#include "Object.h"

Object::Object()
{
}

Mesh3D* Object::GetMesh()
{
	return m_Mesh;
}

void Object::SetMesh(Mesh3D* m)
{
	m_Mesh = m;
}