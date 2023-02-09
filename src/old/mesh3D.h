#pragma once

#include <Engine_Core.h>

using namespace std;


typedef struct vertex_t {
	glm::vec4 pos;
}vertex_t;
class Mesh3D
{
public:

	Mesh3D();
	int getMeshID();
	void addVertex(struct vertex_t vertice);
	vector<vertex_t>* getVertList();
private:
	static int meshID;
	glm::vec3 colorRGB;
	vector<struct vertex_t>* vVertList;
};

