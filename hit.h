#pragma once

#ifndef HIT_H

#include "ray.h"
#include "vec3.h"

namespace RayTracing
{

	struct HitRecord
	{
		Point3 p_;
		Vec3 normal_;
		Ray::ValType t_;
	};

	class Hittable
	{
	public:
		virtual bool hit(const Ray& r, Ray::ValType t_min, Ray::ValType t_max,
			HitRecord& rec) const = 0;
	};

}

#endif // !HIT_H
