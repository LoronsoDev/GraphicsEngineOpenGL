#pragma once

#include <Engine_Core.h>
#include <engine/render/PolygonUtils.h>

class Mesh3D
{
public:
	Mesh3D();
	inline int GetMeshID() { return s_MeshID; }
	inline void AddVertex(Vertex v) { m_VertexBuffer->push_back(v); }
	inline VertexBuffer* GetVertList() { return m_VertexBuffer;  }
	inline glm::vec3 GetMeshColor() { return m_ColorRGB; }

private:
	static int s_MeshID;

private:
	glm::vec3 m_ColorRGB;
	VertexBuffer* m_VertexBuffer;
};

