#include "Mesh3D.h"

int Mesh3D::s_MeshID = 0;

Mesh3D::Mesh3D()
{
	s_MeshID = s_MeshID + 1;

	m_ColorRGB = glm::vec3(1.0f, 1.0f, 1.0f);
	m_VertexBuffer = new VertexBuffer();
	vTriangleIdxList = new VertexIdBuffer();
}

void Mesh3D::addTriangle(glm::uint32 vId1, glm::uint32 vId2, glm::uint32 vId3)
{
	vTriangleIdxList->push_back(vId1);
	vTriangleIdxList->push_back(vId2);
	vTriangleIdxList->push_back(vId3);
}
