#include "constant_medium.h"

#ifdef DEBUG_CONSTANT_MEDIUM_HIT
#include <iostream>
#endif // DEBUG_CONSTANT_MEDIUM_HIT


bool RayTracing::ConstantMedium::hit(const Ray& r, ValType t_min,
	ValType t_max, HitRecord& rec) const
{

#ifdef DEBUG_CONSTANT_MEDIUM_HIT
	const bool enableDebug = false;
	const bool debugging = enableDebug && random_val() < 0.00001;
#endif // DEBUG_CONSTANT_MEDIUM_HIT

	HitRecord rec1, rec2;

	if (!boundary->hit(r, -infinity, infinity, rec1))
	{
		return false;
	}

	if (!boundary->hit(r, rec1.t_ + 0.0001, infinity, rec2))
	{
		return false;
	}

#ifdef DEBUG_CONSTANT_MEDIUM_HIT
	std::cerr << "\nt_min=" << rec1.t_ << ", t_max=" << rec2.t_ << '\n';
#endif // DEBUG_CONSTANT_MEDIUM_HIT


	if (rec1.t_ < t_min)
	{ 
		rec1.t_ = t_min; 
	}
	if (rec2.t_ > t_max) 
	{ 
		rec2.t_ = t_max;
	}

	if (rec1.t_ >= rec2.t_)
	{
		return false;
	}

	if (rec1.t_ < 0)
	{
		rec1.t_ = 0;
	}

	const auto ray_length = r.direction().length();
	const auto distance_inside_boundary = (rec2.t_ - rec1.t_) * ray_length;
	const auto hit_distance = neg_inv_density * log(random_val());

	if (hit_distance > distance_inside_boundary)
		return false;

	rec.t_ = rec1.t_ + hit_distance / ray_length;
	rec.p_ = r.at(rec.t_);

#ifdef DEBUG_CONSTANT_MEDIUM_HIT
	if (debugging) 
	{
		std::cerr << "hit_distance = " << hit_distance << '\n'
			<< "rec.t = " << rec.t_ << '\n'
			<< "rec.p = " << rec.p_ << '\n';
	}
#endif // DEBUG_CONSTANT_MEDIUM_HIT

	rec.normal_ = Vec3(1, 0, 0);  // arbitrary
	rec.front_face_ = true;     // also arbitrary
	rec.mat_ptr_ = phase_function;

	return true;
}
