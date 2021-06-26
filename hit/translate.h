#pragma once

#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "hit.h"

namespace RayTracing
{

	class Translate :public Hittable
	{
	public:
		Translate(std::shared_ptr<Hittable> p, const Vec3& displacement)
			: ptr_(p), offset_(displacement) {}

		virtual bool hit(
			const Ray& r, ValType t_min, ValType t_max, HitRecord& rec)const
			override;

		virtual bool bounding_box(ValType time0, ValType time1,
			AABB& output_box)const override;

	public:
		std::shared_ptr<Hittable> ptr_;
		Vec3 offset_;
	};

}
#endif // !TRANSLATE_H
