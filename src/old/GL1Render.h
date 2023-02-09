#pragma once

#define GLAD_ONLY_HEADERS

#include <Engine_Core.h>
#include "Render.h"

class GL1Render : public Render
{
public:
	GL1Render(int h, int w);
	void init();
private:
	GLFWwindow* window;
};

