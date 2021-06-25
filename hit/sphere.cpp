#include "sphere.h"

#include <cmath>

bool RayTracing::Sphere::hit(const Ray& r, ValType t_min, ValType
	t_max, HitRecord& rec) const
{
	Vec3 oc = r.origin();
	oc -= center_;
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
	Vec3 outward_normal = rec.p_ - center_;
	outward_normal /= radius_;
	rec.set_face_normal(r, outward_normal);
	get_sphere_uv(outward_normal, rec.u_, rec.v_);
	rec.mat_ptr_ = mat_ptr_;

	return true;
}

bool RayTracing::Sphere::bounding_box(ValType time0, ValType time1, AABB& output_box)
const
{
	output_box = AABB(
		center_ - Vec3(radius_, radius_, radius_),
		center_ + Vec3(radius_, radius_, radius_));
	return true;
}

inline void RayTracing::Sphere::get_sphere_uv(const Point3& p, ValType& u, ValType& v)
{
	// p: a given point on the sphere of radius one, centered at the origin.
	// u: returned value [0,1] of angle around the Y axis from X=-1.
	// v: returned value [0,1] of angle from Y=-1 to Y=+1.
	//     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
	//     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
	//     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

	auto theta = acos(-p.y());
	auto phi = atan2(-p.z(), p.x()) + pi;

	u = phi / (2 * pi);
	v = theta / pi;
}
