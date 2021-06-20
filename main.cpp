#include <fstream>

#include "vec3/color.h"
#include "vec3/vec3.h"
#include "hit/hit.h"
#include "hit/hittable_list.h"
#include "hit/sphere.h"
#include "ray/camera.h"
#include "ray/ray.h"
#include "util.h"


RayTracing::Color ray_color(const RayTracing::Ray& r,
	const RayTracing::Hittable& world, int depth)
{
	RayTracing::HitRecord rec;
	if (depth <= 0)
	{
		return RayTracing::Color(0, 0, 0);
	}
	if (world.hit(r, 0.001, RayTracing::infinity, rec))
	{
		RayTracing::Point3 target = rec.p_ + rec.normal_ +
			RayTracing::Vec3::RandomUnitVector();
		return 0.5 * ray_color(RayTracing::Ray(rec.p_, target - rec.p_), world,
			depth - 1);
	}
	RayTracing::Vec3 unit_direction = r.direction().unit();
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * RayTracing::Color(1.0, 1.0, 1.0) + t *
		RayTracing::Color(0.5, 0.7, 1.0);
}

int main()
{
	// Image
	const auto aspect_ratio = 16.0 / 9.0;
	const int image_width = 400;
	const int image_height = static_cast<int>(image_width / aspect_ratio);
	const int samples_per_pixel = 100;
	const int max_depth = 50;

	// World
	RayTracing::HittableList world;
	world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point3(0, 0, -1), 0.5));
	world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point3(0, -100.5, -1), 100));

	// Camera
	RayTracing::Camera cam;

	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = RayTracing::Point3(0, 0, 0);
	auto horizontal = RayTracing::Vec3(viewport_width, 0, 0);
	auto vertical = RayTracing::Vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2
		- RayTracing::Vec3(0, 0, focal_length);

	// Render
	std::fstream fstr("img.ppm", std::ios_base::in | std::ios_base::out | std::ios_base::trunc);
	fstr << "P3\n" << image_width << " " << image_height << "\n255\n";

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {
			RayTracing::Color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + RayTracing::random_val()) / (image_width - 1);
				auto v = (j + RayTracing::random_val()) / (image_height - 1);
				RayTracing::Ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color(fstr, pixel_color, samples_per_pixel);
		}
	}

	std::cerr << "\nDone.\n";
}
