#include "mesh3D.h"

int Mesh3D::s_MeshID = 0;

Mesh3D::Mesh3D()
{
	s_MeshID = s_MeshID + 1;

	m_ColorRGB = glm::vec3(1.0f, 1.0f, 1.0f);
	m_VertexBuffer = new VertexBuffer();
}