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
		Sphere(Point3 center, ValType r) : center_(center), radius_(r)
		{}

		virtual bool hit(const Ray& r, ValType t_min, ValType t_max,
			HitRecord& rec) const override;

	private:
		Point3 center_;
		ValType radius_;
	};
}

#endif // !SPHERE_H
