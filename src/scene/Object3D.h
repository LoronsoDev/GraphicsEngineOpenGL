#pragma once

#include "Object.h"
#include <pugixml.hpp>

class Object3D : public Object
{
public:
	virtual void LoadDataFromFile(std::string path) override;
};
