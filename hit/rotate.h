#pragma once

#ifndef ROTATE_H
#define  ROTATE_H

#include "hit.h"
namespace RayTracing
{

	class RotateY :public Hittable
	{
	public:
		RotateY(std::shared_ptr<Hittable> p, ValType angle);

		virtual bool hit(
			const Ray& r, ValType t_min, ValType t_max, HitRecord& rec) const
			override;

		virtual bool bounding_box(ValType time0, ValType time1,
			AABB& output_box)
			const override
		{
			output_box = bbox_;
			return hasbox_;
		}

	public:
		std::shared_ptr<Hittable> ptr_;
		ValType sin_theta_;
		ValType cos_theta_;
		bool hasbox_;
		AABB bbox_;
	};

}

#endif // !ROTATE_H
