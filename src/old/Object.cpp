#include "Object.h"

Object::Object()
{
	this->setPos(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	this->setRot(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
	this->setScale(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	this->setModelMatrix(glm::mat4(1.0f));
	mesh = new Mesh3D();
}

Mesh3D* Object::getMesh()
{
	return mesh;
}

void Object::setMesh(Mesh3D* m)
{
	mesh = m;
}