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
		virtual bool bounding_box(ValType time0, ValType time1, AABB& output_box) const override;

	private:
		static void get_sphere_uv(const Point3& p, ValType& u, ValType& v);

	private:
		Point3 center_;
		ValType radius_;
		std::shared_ptr<Material> mat_ptr_;
	};
}

#endif // !SPHERE_H
