#include "hittable_list.h"

bool RayTracing::HittableList::hit(const Ray& r, ValType t_min,
	ValType t_max, HitRecord& rec) const
{
	HitRecord temp_rec;
	bool hit_anything = false;
	auto closest_so_far = t_max;

	for (const auto& object : objects_)
	{
		if (object->hit(r, t_min, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec.t_;
			rec = temp_rec;
		}
	}

	return hit_anything;
}

bool RayTracing::HittableList::bounding_box(double time0, double time1, AABB& output_box) const
{
	if (objects_.empty()) 
	{ 
		return false;
	};

	AABB temp_box;
	bool first_box = true;

	for (const auto& object : objects_) 
	{
		if (!object->bounding_box(time0, time1, temp_box)) return false;
		output_box = first_box ? temp_box : AABB::surrounding_box(output_box, temp_box);
		first_box = false;
	}

	return true;
}
