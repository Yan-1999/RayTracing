#pragma once

#ifndef COLOR_H

#include "vec3.h"

namespace RayTracing
{
	using Color = Vec3;

	void write_color(std::ostream& out, Color pixel_color);
}

#endif // !COLOR_H
