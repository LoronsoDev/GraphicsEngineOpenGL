#pragma once

#define GLAD_ONLY_HEADERS

#include <Engine_Core.h>
#include <engine/render/PolygonUtils.h>
#include <engine/render/Material.h>

class Mesh3D
{
public:
	Mesh3D();
	inline int GetMeshID() { return id; }
	inline void AddVertex(Vertex v) { m_VertexBuffer->push_back(v); }
	inline VertexBuffer* GetVertList() { return m_VertexBuffer; }
	inline VertexIdBuffer* GetIdBufferList() { return vTriangleIdxList; }
	inline glm::vec3 GetMeshColor() { return m_ColorRGB; }
	inline Material* getMaterial() { return this->mat; }
	inline void setMaterial(Material* mat) { this->mat = mat; }
	void addTriangle(glm::uint32 vId1, glm::uint32 vId2, glm::uint32 vId3);
	unsigned int VAO;
private:
	static int s_Counter;
	int id;

private:
	glm::vec3 m_ColorRGB;
	VertexBuffer* m_VertexBuffer;
	VertexIdBuffer* vTriangleIdxList;

	Material* mat;
};
