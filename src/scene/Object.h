#pragma once

#include <scene/Entity.h>
#include <engine/render/Mesh3D.h>

#include <Engine_Core.h>


enum ObjectType
{
	TRIANGLE
};

class Object : public Entity
{
public:
	Object();

	Mesh3D* GetMesh();
	void SetMesh(Mesh3D* mesh);

	virtual void LoadDataFromFile(std::string file) = 0;
private:
	Mesh3D* m_Mesh;
	ObjectType m_Type;
};



