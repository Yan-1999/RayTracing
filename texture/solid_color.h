#pragma once

#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H

#include "texture.h"

namespace RayTracing
{
	class SolidColor :public Texture
	{
	public:
		SolidColor() {}
		SolidColor(Color c) : color_value_(c) {}

		SolidColor(ValType red, ValType green, ValType blue)
			: SolidColor(Color(red, green, blue)) {}

		virtual Color value(ValType u, ValType v, const Vec3& p) const override
		{
			return color_value_;
		}

	private:
		Color color_value_;
	};

}

#endif // !SOLID_COLOR_H
