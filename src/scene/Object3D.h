#pragma once

#include "Object.h"

class Object3D : public Object
{
public:
	virtual void LoadDataFromFile(std::string path) override;
};
