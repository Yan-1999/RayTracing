#pragma once
#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "hit.h"

#include "../ray/ray.h"
namespace RayTracing
{

	class MovingSphere :public Hittable
	{
	public:
		MovingSphere() {}
		MovingSphere(
			Point3 cen0, Point3 cen1, ValType _time0, ValType _time1, ValType r,
			std::shared_ptr<Material> m)
			: center0_(cen0), center1_(cen1), time0_(_time0), time1_(_time1), radius_(r),
			mat_ptr_(m)
		{};

		Point3 center(ValType time) const
		{
			return center0_ + ((time - time0_) / (time1_ - time0_)) * (center1_ - center0_);
		}

		virtual bool hit(
			const Ray& r, ValType t_min, ValType t_max, HitRecord& rec) const override;
		virtual bool bounding_box(
			double time0, double time1, AABB& output_box) const override;

	public:
		Point3 center0_, center1_;
		ValType time0_, time1_;
		ValType radius_;
		std::shared_ptr<Material> mat_ptr_;
	};

}

#endif // !MOVING_SPHERE_H
