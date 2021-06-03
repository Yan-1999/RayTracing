#pragma once

#ifndef COLOR_H

#include "vec3.h"

namespace RayTracing
{
	using color = vec3;

	void write_color(std::ostream& out, color pixel_color);
}

#endif // !COLOR_H
