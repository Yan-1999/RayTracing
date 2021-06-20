#pragma once

#ifndef COLOR_H

#include "vec3.h"

namespace RayTracing
{
	using Color = Vec3;

	void write_color(std::ostream& out, Color pixel_color, int samples_per_pixel);
}

#endif // !COLOR_H
