#include <atomic>
#include <fstream>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include "hit/hit.h"
#include "hit/hittable_list.h"
#include "hit/sphere.h"
#include "hit/moving_sphere.h"
#include "material/dielectric.h"
#include "material/lambertian.h"
#include "material/material.h"
#include "material/metal.h"
#include "ray/camera.h"
#include "ray/ray.h"
#include "texture/checker_texture.h"
#include "texture/solid_color.h"
#include "texture/noise_texture.h"
#include "util.h"
#include "vec3/color.h"
#include "vec3/vec3.h"

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
		RayTracing::Ray scattered;
		RayTracing::Color attenuation;
		if (rec.mat_ptr_->scatter(r, rec, attenuation, scattered))
			return attenuation * ray_color(scattered, world, depth - 1);
		return RayTracing::Color(0, 0, 0);
	}
	RayTracing::Vec3 unit_direction = r.dir_.unit();
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * RayTracing::Color(1.0, 1.0, 1.0) + t *
		RayTracing::Color(0.5, 0.7, 1.0);
}

RayTracing::HittableList random_scene() {
	RayTracing::HittableList world;

	auto checker = std::make_shared<RayTracing::CheckerTexture>(
		RayTracing::Color(0.2, 0.3, 0.1), RayTracing::Color(0.9, 0.9, 0.9));
	world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point3(0, -1000, 0), 1000,
		std::make_shared<RayTracing::Lambertian>(checker)));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = RayTracing::random_val();
			RayTracing::Point3 center(a + 0.9 * RayTracing::random_val(), 0.2,
				b + 0.9 * RayTracing::random_val());

			if ((center - RayTracing::Point3(4, 0.2, 0)).length() > 0.9) {
				std::shared_ptr<RayTracing::Material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = RayTracing::Color::random() *
						RayTracing::Color::random();
					sphere_material = std::make_shared<RayTracing::Lambertian>(
						albedo);
					world.add(std::make_shared<RayTracing::Sphere>(center, 0.2,
						sphere_material));
					auto center2 = center + RayTracing::Vec3(0,
						RayTracing::random_val(0, .5), 0);
					world.add(std::make_shared<RayTracing::MovingSphere>(
						center, center2, 0.0, 1.0, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = RayTracing::Color::random(0.5, 1);
					auto fuzz = RayTracing::random_val(0, 0.5);
					sphere_material = std::make_shared<RayTracing::Metal>(
						albedo, fuzz);
					world.add(std::make_shared<RayTracing::Sphere>(center, 0.2,
						sphere_material));
				}
				else {
					// glass
					sphere_material = std::make_shared<RayTracing::Dielectric>(1.5);
					world.add(std::make_shared<RayTracing::Sphere>(center, 0.2,
						sphere_material));
				}
			}
		}
	}

	auto material1 = std::make_shared<RayTracing::Dielectric>(1.5);
	world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point3(0, 1, 0),
		1.0, material1));

	auto material2 = std::make_shared<RayTracing::Lambertian>(RayTracing::Color(
		0.4, 0.2, 0.1));
	world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point3(-4, 1, 0),
		1.0, material2));

	auto material3 = std::make_shared<RayTracing::Metal>(RayTracing::Color(0.7,
		0.6, 0.5), 0.0);
	world.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point3(4, 1, 0),
		1.0, material3));

	return world;
}

RayTracing::HittableList two_spheres() 
{
	RayTracing::HittableList objects;

	auto checker = std::make_shared<RayTracing::CheckerTexture>(
		RayTracing::Color(0.2, 0.3, 0.1), RayTracing::Color(0.9, 0.9, 0.9));

	objects.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point3(0, -10, 0), 10,
		std::make_shared<RayTracing::Lambertian>(checker)));
	objects.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point3(0, 10, 0), 10,
		std::make_shared<RayTracing::Lambertian>(checker)));

	return objects;
}

RayTracing::HittableList two_perlin_spheres() 
{
	RayTracing::HittableList objects;

	auto pertext = std::make_shared<RayTracing::NoiseTexture>(4);
	objects.add(std::make_shared<RayTracing::Sphere>(
		RayTracing::Point3(0, -1000, 0), 1000, 
		std::make_shared<RayTracing::Lambertian>(pertext)));
	objects.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point3(0, 2, 0), 2,
		make_shared<RayTracing::Lambertian>(pertext)));

	return objects;
}

void write_color_to_mat(int j, int i, RayTracing::Color c, int samples_per_pixel,
	cv::Mat& mat)
{
	auto r = c.x();
	auto g = c.y();
	auto b = c.z();

	// Divide the color by the number of samples.
	auto scale = 1.0 / samples_per_pixel;
	r = std::sqrt(scale * r);
	g = std::sqrt(scale * g);
	b = std::sqrt(scale * b);

	// Write the translated [0,255] value of each color component.
	mat.at<cv::Vec3b>(j, i)[0] = static_cast<uchar>(256 * std::clamp(r, 0.0, 0.999));
	mat.at<cv::Vec3b>(j, i)[1] = static_cast<uchar>(256 * std::clamp(g, 0.0, 0.999));
	mat.at<cv::Vec3b>(j, i)[2] = static_cast<uchar>(256 * std::clamp(b, 0.0, 0.999));
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

	RayTracing::Point3 lookfrom;
	RayTracing::Point3 lookat;
	auto vfov = 40.0;
	auto aperture = 0.0;

	switch (0) {
	case 1:
		world = random_scene();
		lookfrom = RayTracing::Point3(13, 2, 3);
		lookat = RayTracing::Point3(0, 0, 0);
		vfov = 20.0;
		aperture = 0.1;
		break;

	case 2:
		world = two_spheres();
		lookfrom = RayTracing::Point3(13, 2, 3);
		lookat = RayTracing::Point3(0, 0, 0);
		vfov = 20.0;
		break;

	default:
	case 3:
		world = two_perlin_spheres();
		lookfrom = RayTracing::Point3(13, 2, 3);
		lookat = RayTracing::Point3(0, 0, 0);
		vfov = 20.0;
		break;
	}

	// Camera
	//RayTracing::Point3 lookfrom(13, 2, 3);
	//RayTracing::Point3 lookat(0, 0, 0);
	RayTracing::Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10;
	//auto aperture = 0.1;

	RayTracing::Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture,
		dist_to_focus, 0.0, 1.0);

	auto viewport_height = 2.0;
	auto viewport_width = aspect_ratio * viewport_height;
	auto focal_length = 1.0;

	auto origin = RayTracing::Point3(0, 0, 0);
	auto horizontal = RayTracing::Vec3(viewport_width, 0, 0);
	auto vertical = RayTracing::Vec3(0, viewport_height, 0);
	auto lower_left_corner = origin - horizontal / 2 - vertical / 2
		- RayTracing::Vec3(0, 0, focal_length);

	// Render
	cv::Mat img_mat(image_height, image_width, CV_8UC3);
	std::atomic<int> remaining = image_height;
#pragma omp parallel for num_threads(12)
	for (int j = image_height - 1; j >= 0; --j) {
		remaining--;
		std::cerr << "\rScanlines remaining: " << remaining << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {
			RayTracing::Color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + RayTracing::random_val()) / (image_width - 1);
				auto v = (j + RayTracing::random_val()) / (image_height - 1);
				RayTracing::Ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world, max_depth);
			}
			write_color_to_mat(image_height - 1 - j, i, pixel_color, samples_per_pixel, img_mat);
		}
	}
	cv::imwrite("img.jpg", img_mat);
	std::cerr << "\nDone.\n";
}
