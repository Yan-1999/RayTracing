#include "camera.h"

RayTracing::Camera::Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, ValType vfov, ValType aspect_ratio, ValType aperture, ValType focus_dist, ValType time0, ValType time1)
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
	time0_ = time0;
	time1_ = time1;
	aspect_ratio_ = aspect_ratio;
}
