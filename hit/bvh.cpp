#include "bvh.h"

#include <algorithm>

bool RayTracing::box_compare(const std::shared_ptr<Hittable>& a,
	const std::shared_ptr<Hittable>& b, size_t axis)
{
	RayTracing::AABB box_a;
	RayTracing::AABB box_b;

	if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
	{
		std::cerr << "No bounding box in bvh_node constructor.\n";
	}

	return box_a.min()[axis] < box_b.min()[axis];
}

bool RayTracing::box_x_compare(const std::shared_ptr<Hittable>& a,
	const std::shared_ptr<Hittable>& b)
{
	return box_compare(a, b, 0);
}

bool RayTracing::box_y_compare(const std::shared_ptr<Hittable>& a,
	const std::shared_ptr<Hittable>& b)
{
	return box_compare(a, b, 1);
}

bool RayTracing::box_z_compare(const std::shared_ptr<Hittable>& a,
	const std::shared_ptr<Hittable>& b)
{
	return box_compare(a, b, 2);
}

RayTracing::BVHNode::BVHNode(
	const std::vector<std::shared_ptr<Hittable>>& src_objects,
	size_t start, size_t end, ValType time0, ValType time1)
{
	// Create a modifiable array of the source scene objects
	auto objects = src_objects;

	int axis = random_int(0, 2);
	auto comparator = (axis == 0) ? RayTracing::box_x_compare
		: (axis == 1) ? RayTracing::box_y_compare
		: RayTracing::box_z_compare;

	size_t object_span = end - start;

	if (object_span == 1)
	{
		left_ = right_ = objects[start];
	}
	else if (object_span == 2)
	{
		if (comparator(objects[start], objects[start + 1]))
		{
			left_ = objects[start];
			right_ = objects[start + 1];
		}
		else
		{
			left_ = objects[start + 1];
			right_ = objects[start];
		}
	}
	else
	{
		std::sort(objects.begin() + start, objects.begin() + end, comparator);

		auto mid = start + object_span / 2;
		left_ = std::make_shared<BVHNode>(objects, start, mid, time0, time1);
		right_ = std::make_shared<BVHNode>(objects, mid, end, time0, time1);
	}

	AABB box_left, box_right;

	if (!left_->bounding_box(time0, time1, box_left)
		|| !right_->bounding_box(time0, time1, box_right)
		)
	{
		std::cerr << "No bounding box in bvh_node constructor.\n";
	}

	box_ = AABB::surrounding_box(box_left, box_right);
}

bool RayTracing::BVHNode::hit(const Ray& r, ValType t_min, ValType t_max, HitRecord& rec) const
{
	if (!box_.hit(r, t_min, t_max))
	{
		return false;
	}

	bool hit_left = left_->hit(r, t_min, t_max, rec);
	bool hit_right = right_->hit(r, t_min, hit_left ? rec.t_ : t_max, rec);

	return hit_left || hit_right;
}
