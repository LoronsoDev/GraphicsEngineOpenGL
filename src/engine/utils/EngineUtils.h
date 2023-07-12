#pragma once

#include <Engine_Core.h>
struct RGBA
{
	union
	{
		//All struct members occupy the same memory location.
		struct { float x, y, z, w; };
		struct { float r, g, b, a; };
		struct { float s, t, p, q; };
	};
};

