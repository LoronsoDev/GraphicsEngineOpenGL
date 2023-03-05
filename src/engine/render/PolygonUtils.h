#pragma once

#include <Engine_Core.h>

#define IDENTITY glm::mat4(1)

struct Vertex
{
	//Will contain more data on the future.
	glm::vec4 VertexPos;
};

typedef std::vector<Vertex> VertexBuffer;
typedef std::vector<glm::uint32> VertexIdBuffer;