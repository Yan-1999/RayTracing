#pragma once
#ifndef BOX_H
#define BOX_H

#include "hittable_list.h"
#include "../vec3/vec3.h"

namespace RayTracing
{
	class Box : public HittableList
	{
	public:
		Box() {}
		Box(const Point3& p0, const Point3& p1,
			std::shared_ptr<Material> ptr);

		virtual bool hit(const Ray& r, ValType t_min, ValType t_max,
			HitRecord& rec) const override;

		virtual bool bounding_box(ValType time0, ValType time1,
			AABB& output_box) const override
		{
			output_box = AABB(box_min_, box_max_);
			return true;
		}

	public:
		Point3 box_min_;
		Point3 box_max_;
		HittableList sides_;
	};
}


#endif // !BOX_H
