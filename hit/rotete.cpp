#include "rotate.h"

RayTracing::RotateY::RotateY(std::shared_ptr<Hittable> p, ValType angle)
	: ptr_(p) {
	auto radians = degrees_to_radians(angle);
	sin_theta_ = std::sin(radians);
	cos_theta_ = std::cos(radians);
	hasbox_ = ptr_->bounding_box(0, 1, bbox_);

	Point3 min(infinity, infinity, infinity);
	Point3 max(-infinity, -infinity, -infinity);

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				auto x = i * bbox_.max().x() + (1 - i) * bbox_.min().x();
				auto y = j * bbox_.max().y() + (1 - j) * bbox_.min().y();
				auto z = k * bbox_.max().z() + (1 - k) * bbox_.min().z();

				auto newx = cos_theta_ * x + sin_theta_ * z;
				auto newz = -sin_theta_ * x + cos_theta_ * z;

				Vec3 tester(newx, y, newz);

				for (int c = 0; c < 3; c++)
				{
					min[c] = std::min(min[c], tester[c]);
					max[c] = std::max(max[c], tester[c]);
				}
			}
		}
	}

	bbox_ = AABB(min, max);
}

bool RayTracing::RotateY::hit(const Ray& r, ValType t_min, ValType t_max, 
	HitRecord& rec) const
{
	auto origin = r.origin();
	auto direction = r.direction();

	origin[0] = cos_theta_ * r.origin()[0] - sin_theta_ * r.origin()[2];
	origin[2] = sin_theta_ * r.origin()[0] + cos_theta_ * r.origin()[2];

	direction[0] = cos_theta_ * r.direction()[0] - sin_theta_ * r.direction()[2];
	direction[2] = sin_theta_ * r.direction()[0] + cos_theta_ * r.direction()[2];

	Ray rotated_r(origin, direction, r.time());

	if (!ptr_->hit(rotated_r, t_min, t_max, rec))
	{
		return false;
	}

	auto p = rec.p_;
	auto normal = rec.normal_;

	p[0] = cos_theta_ * rec.p_[0] + sin_theta_ * rec.p_[2];
	p[2] = -sin_theta_ * rec.p_[0] + cos_theta_ * rec.p_[2];

	normal[0] = cos_theta_ * rec.normal_[0] + sin_theta_ * rec.normal_[2];
	normal[2] = -sin_theta_ * rec.normal_[0] + cos_theta_ * rec.normal_[2];

	rec.p_ = p;
	rec.set_face_normal(rotated_r, normal);

	return true;
}
