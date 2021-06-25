#pragma once

#ifndef HIT_H


#include <memory>

#include "../ray/ray.h"
#include "../vec3/vec3.h"
#include "aabb.h"

namespace RayTracing
{
	class Material;

	struct HitRecord
	{
		Point3 p_;
		Vec3 normal_;
		std::shared_ptr<Material> mat_ptr_;
		ValType t_ = 0;
		ValType u_;
		ValType v_;
		bool front_face_ = false;

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
		virtual bool bounding_box(ValType time0, ValType time1, AABB& output_box) const = 0;
	};

}

#endif // !HIT_H
