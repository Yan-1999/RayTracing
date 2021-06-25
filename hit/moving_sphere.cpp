#include "moving_sphere.h"

bool RayTracing::MovingSphere::hit(const Ray& r, ValType t_min, ValType t_max,
	HitRecord& rec) const
{
	Vec3 oc = r.origin() - center(r.time());
	auto a = r.direction().length_squared();
	auto half_b = oc.dot(r.direction());
	auto c = oc.length_squared() - radius_ * radius_;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
	{
		return false;
	}
	auto sqrtd = std::sqrt(discriminant);

	// Find the nearest root that lies in the acceptable range.
	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
		{
			return false;
		}
	}

	rec.t_ = root;
	r.at(rec.t_, rec.p_);
	Vec3 outward_normal = (rec.p_ - center(r.time())) / radius_;
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr_ = mat_ptr_;

	return true;
}