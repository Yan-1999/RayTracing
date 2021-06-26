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
			ValType focus_dist,
			ValType time0,
			ValType time1
		);

		ValType aspect_ratio() { return aspect_ratio_; }

		Ray get_ray(ValType s, ValType t) const
		{
			Vec3 rd = lens_radius_ * Vec3::RandomInUnitDisk();
			Vec3 offset = u_ * rd.x() + v_ * rd.y();

			return Ray(
				origin_ + offset,
				lower_left_corner_ + s * horizontal_ + t * vertical_ - origin_ - offset,
				random_val(time0_, time1_)
			);
		}

	private:
		Point3 origin_;
		Point3 lower_left_corner_;
		Vec3 horizontal_;
		Vec3 vertical_;
		Vec3 u_, v_, w_;
		ValType lens_radius_;
		ValType time0_, time1_;
		ValType aspect_ratio_;
	};
}

#endif // !CAMERA_H
