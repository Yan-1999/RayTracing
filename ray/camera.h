#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include "ray.h"
#include "../vec3/vec3.h"

namespace RayTracing
{
	class Camera
	{
	public:
		Camera(
			Point3 lookfrom,
			Point3 lookat,
			Vec3   vup,
			ValType vfov, // vertical field-of-view in degrees
			ValType aspect_ratio
		)
		{
			auto theta = degrees_to_radians(vfov);
			auto h = tan(theta / 2);
			auto viewport_height = 2.0 * h;
			auto viewport_width = aspect_ratio * viewport_height;
			auto focal_length = 1.0;

			auto w = (lookfrom - lookat).unit();
			auto u = (vup.cross(w)).unit();
			auto v = w.cross(u);

			origin_ = lookfrom;
			horizontal_ = viewport_width * u;
			vertical_ = viewport_height * v;
			lower_left_corner_ = origin_ - horizontal_ / 2 - vertical_ / 2 - w;
		}

		Ray get_ray(ValType s, ValType t) const
		{
			return Ray(origin_,
				lower_left_corner_ + s * horizontal_ + t * vertical_ - origin_);
		}

	private:
		Point3 origin_;
		Point3 lower_left_corner_;
		Vec3 horizontal_;
		Vec3 vertical_;
	};
}

#endif // !CAMERA_H
