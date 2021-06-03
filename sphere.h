#pragma once
#include "hit.h"

namespace RayTracing
{

	class Sphere :public Hittable
	{
	public:
		Sphere() : center_(Point3()), radius_(0) {}
		Sphere(Point3 center, Point3::ValType r) : center_(center), radius_(r)
		{}

		virtual bool hit(const Ray& r, Ray::ValType t_min, Ray::ValType t_max,
			HitRecord& rec) const override;

	private:
		Point3 center_;
		Point3::ValType radius_;
	};
}
