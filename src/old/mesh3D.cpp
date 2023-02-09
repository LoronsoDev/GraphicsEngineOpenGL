#include "mesh3D.h"

int Mesh3D::meshID = 0;

Mesh3D::Mesh3D()
{
	meshID = meshID + 1;
	colorRGB = glm::vec3(1.0f, 1.0f, 1.0f);
	vVertList = new vector<struct vertex_t>();
}

int Mesh3D::getMeshID()
{
	return meshID;
}
void Mesh3D::addVertex(struct vertex_t vertice)
{
	vVertList->push_back(vertice);
}

vector<struct vertex_t>* Mesh3D::getVertList()
{
	return vVertList;
}

