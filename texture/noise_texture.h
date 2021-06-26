#pragma once

#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H

#include <cmath>

#include "texture.h"
#include "perlin.h"

namespace RayTracing
{

	class NoiseTexture :public Texture
	{
	public:
		NoiseTexture() {}
		NoiseTexture(ValType sc) : scale_(sc) {}

		virtual Color value(ValType u, ValType v, const Point3& p) const
			override
		{
			return Color(1, 1, 1) * 0.5 * (1 + std::sin(scale_ * p.z() +
				10 * noise_.turb(p)));
		}

	public:
		Perlin noise_;
		ValType scale_;
	};

}
#endif // !NOISE_TEXTURE_H
