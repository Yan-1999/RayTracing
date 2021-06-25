#pragma once

#ifndef SPHERE_H
#define SPHERE_H

#include "hit.h"

namespace RayTracing
{
	class Sphere :public Hittable
	{
	public:
		Sphere() : center_(Point3()), radius_(0) {}
		Sphere(Point3 center, ValType r, std::shared_ptr<Material> m)
			:center_(center), radius_(r), mat_ptr_(m)
		{}

		virtual bool hit(const Ray& r, ValType t_min, ValType t_max,
			HitRecord& rec) const override;
		virtual bool bounding_box(double time0, double time1, AABB& output_box);

	private:
		Point3 center_;
		ValType radius_;
		std::shared_ptr<Material> mat_ptr_;
	};
}

#endif // !SPHERE_H
