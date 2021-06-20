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
	};
}

#endif
