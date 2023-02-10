#pragma once

#include <scene/Entity.h>
#include "engine/polygon/Mesh3D.h"

#include <Engine_Core.h>
enum Tipo{triangulo};
class Object : public Entity
{
public:
	Object();
	Mesh3D* getMesh();
	void setMesh(Mesh3D* m);
	virtual void loadDataFromFile(std::string file)=0;
private:
	Mesh3D* mesh;
	Tipo t;
};



