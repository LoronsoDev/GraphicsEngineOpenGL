#pragma once
#include <engine/base/Window.h>


class UserInterface
{
public:
	virtual void CreateContext(engine::Window* window) = 0;
	virtual void Init()	  = 0;
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void Shutdown() = 0;
};
