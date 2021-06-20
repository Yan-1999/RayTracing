#pragma once

#ifndef HIT_H

#include "../ray/ray.h"
#include "../vec3/vec3.h"

namespace RayTracing
{

	struct HitRecord
	{
		Point3 p_;
		Vec3 normal_;
		ValType t_;
		bool front_face_;

		inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
			front_face_ = r.direction().dot(outward_normal) < 0;
			normal_ = front_face_ ? outward_normal : -outward_normal;
		}
	};

	class Hittable
	{
	public:
		virtual bool hit(const Ray& r, ValType t_min, ValType t_max, HitRecord& rec)
			const = 0;
	};

}

#endif // !HIT_H
