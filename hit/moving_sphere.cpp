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

bool RayTracing::MovingSphere::bounding_box(ValType time0, ValType time1, AABB& output_box) const
{
	AABB box0(
		center(time0) - Vec3(radius_, radius_, radius_),
		center(time0) + Vec3(radius_, radius_, radius_));
	AABB box1(
		center(time1) - Vec3(radius_, radius_, radius_),
		center(time1) + Vec3(radius_, radius_, radius_));
	output_box = AABB::surrounding_box(box0, box1);
	return true;
}
