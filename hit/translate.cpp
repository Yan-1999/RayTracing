#include "translate.h"

bool RayTracing::Translate::hit(const Ray& r, ValType t_min, ValType t_max,
	HitRecord& rec) const
{
	Ray moved_r(r.origin() - offset_, r.direction(), r.time());
	if (!ptr_->hit(moved_r, t_min, t_max, rec))
	{
		return false;
	}

	rec.p_ += offset_;
	rec.set_face_normal(moved_r, rec.normal_);

	return true;
}

bool RayTracing::Translate::bounding_box(ValType time0, ValType time1, 
	AABB& output_box) const
{
	if (!ptr_->bounding_box(time0, time1, output_box))
	{
		return false;
	}

	output_box = AABB(
		output_box.min() + offset_,
		output_box.max() + offset_);

	return true;
}
