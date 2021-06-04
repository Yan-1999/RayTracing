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
		Camera()
		{
			auto aspect_ratio = 16.0 / 9.0;
			auto viewport_height = 2.0;
			auto viewport_width = aspect_ratio * viewport_height;
			auto focal_length = 1.0;

			Vec3 temp_vec(0, 0, focal_length);

			origin_ = Point3(0, 0, 0);
			horizontal_ = Vec3(viewport_width, 0.0, 0.0);
			vertical_ = Vec3(0.0, viewport_height, 0.0);
			// lower_left_corner_ = origin_ - horizontal_ / 2 - vertical_ / 2
			//     - Vec3(0, 0, focal_length);
			lower_left_corner_ = origin_;
			lower_left_corner_ -= temp_vec;
			horizontal_.divide(2, temp_vec);
			lower_left_corner_ -= temp_vec;
			vertical_.divide(2, temp_vec);
			lower_left_corner_ -= temp_vec;
		}

		Ray get_ray(ValType u, ValType v) const
		{
			Vec3 dir = lower_left_corner_;
			// temp_vec = lower_left_corner_ + u * horizontal_ + v * vertical_
			//     - origin_
			Vec3 temp_vec = horizontal_ * u;
			dir += temp_vec;
			vertical_.multiply(v, temp_vec);
			dir += temp_vec;
			dir -= origin_;

			return Ray(origin_, dir);
		}

	private:
		Point3 origin_;
		Point3 lower_left_corner_;
		Vec3 horizontal_;
		Vec3 vertical_;
	};
}

#endif // !CAMERA_H
