#pragma once

#include <Engine_Core.h>
#include <engine/polygon/PolygonUtils.h>

class Mesh3D
{
public:
	Mesh3D();
	inline int GetMeshID() { return s_MeshID; }
	inline void AddVertex(Vertex v) { m_VertexBuffer->push_back(v); }
	inline VertexBuffer* getVertList() { return m_VertexBuffer;  }

private:
	static int s_MeshID;

private:
	glm::vec3 m_ColorRGB;
	VertexBuffer* m_VertexBuffer;
};

