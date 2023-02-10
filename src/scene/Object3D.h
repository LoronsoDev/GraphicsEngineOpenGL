#pragma once

#include "Object.h"

class Object3D : public Object
{
public:
	Object3D() { std::cout << "\n - - - Object3D is not supported yet. - - -\n"; };
	virtual void LoadDataFromFile(std::string path) override;
};
