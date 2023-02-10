#include "Object.h"

Object::Object()
{
	
}

Mesh3D* Object::getMesh()
{
	return mesh;
}

void Object::setMesh(Mesh3D* m)
{
	mesh = m;
}