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
			ValType aspect_ratio,
			ValType aperture,
			ValType focus_dist
		)
		{
			auto theta = degrees_to_radians(vfov);
			auto h = tan(theta / 2);
			auto viewport_height = 2.0 * h;
			auto viewport_width = aspect_ratio * viewport_height;
			auto focal_length = 1.0;

			w_ = (lookfrom - lookat).unit();
			u_ = (vup.cross(w_)).unit();
			v_ = w_.cross(u_);

			origin_ = lookfrom;
			horizontal_ = focus_dist * viewport_width * u_;
			vertical_ = focus_dist * viewport_height * v_;
			lower_left_corner_ = origin_ - horizontal_ / 2 - vertical_ / 2 -
				focus_dist * w_;
			lens_radius_ = aperture / 2;
		}

		Ray get_ray(ValType s, ValType t) const
		{
			Vec3 rd = lens_radius_ * Vec3::RandomInUnitDisk();
			Vec3 offset = u_ * rd.x() + v_ * rd.y();

			return Ray(
				origin_ + offset,
				lower_left_corner_ + s * horizontal_ + t * vertical_ - origin_ - offset
			);
		}

	private:
		Point3 origin_;
		Point3 lower_left_corner_;
		Vec3 horizontal_;
		Vec3 vertical_;
		Vec3 u_, v_, w_;
		ValType lens_radius_;
	};
}

#endif // !CAMERA_H
