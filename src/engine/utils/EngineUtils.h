#pragma once

#include <Engine_Core.h>
struct RGBA_8888
{
	union
	{
		//All struct members occupy the same memory location.
		struct { char x, y, z, w; };
		struct { char r, g, b, a; };
		struct { char s, t, p, q; };
	};
};

