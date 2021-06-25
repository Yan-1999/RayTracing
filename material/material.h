#pragma once

#ifndef MATERIAL_H
#define MATERIAL_H

#include "../ray/ray.h"
#include "../vec3/color.h"


namespace RayTracing
{
	struct HitRecord;

	class Material
	{
	public:
		virtual bool scatter(
			const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
		) const = 0;

		virtual Color emitted(ValType u, ValType v, const Point3& p) const
		{
			return Color(0, 0, 0);
		}
	};
}

#endif
