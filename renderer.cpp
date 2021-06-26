#include "renderer.h"

#include <functional>

#include "hit/aarect.h"
#include "hit/box.h"
#include "hit/bvh.h"
#include "hit/constant_medium.h"
#include "hit/hit.h"
#include "hit/hittable_list.h"
#include "hit/rotate.h"
#include "hit/sphere.h"
#include "hit/translate.h"
#include "hit/moving_sphere.h"
#include "material/dielectric.h"
#include "material/diffuse_light.h"
#include "material/lambertian.h"
#include "material/material.h"
#include "material/metal.h"
#include "ray/camera.h"
#include "ray/ray.h"
#include "texture/checker_texture.h"
#include "texture/noise_texture.h"
#include "texture/solid_color.h"
#include "texture/image_texture.h"
#include "util.h"
#include "vec3/color.h"
#include "vec3/vec3.h"

RayTracing::HittableList RayTracing::PredefinedWorld::random_scene() {
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

RayTracing::HittableList RayTracing::PredefinedWorld::two_spheres()
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

RayTracing::HittableList RayTracing::PredefinedWorld::two_perlin_spheres()
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

RayTracing::HittableList RayTracing::PredefinedWorld::earth()
{
	auto earth_texture = std::make_shared<RayTracing::ImageTexture>("earthmap.jpg");
	auto earth_surface = std::make_shared<RayTracing::Lambertian>(earth_texture);
	auto globe = std::make_shared<RayTracing::Sphere>(RayTracing::Point3(0, 0, 0),
		2, earth_surface);

	return RayTracing::HittableList(globe);
}

RayTracing::HittableList RayTracing::PredefinedWorld::simple_light() {
	RayTracing::HittableList objects;

	auto pertext = std::make_shared<RayTracing::NoiseTexture>(4);
	objects.add(std::make_shared<RayTracing::Sphere>(
		RayTracing::Point3(0, -1000, 0), 1000,
		std::make_shared<RayTracing::Lambertian>(pertext)));
	objects.add(std::make_shared<RayTracing::Sphere>(RayTracing::Point3(0, 2, 0), 2,
		make_shared<RayTracing::Lambertian>(pertext)));

	auto difflight = std::make_shared<RayTracing::DiffuseLight>(
		RayTracing::Color(4, 4, 4));
	objects.add(make_shared<RayTracing::XYRect>(3, 5, 1, 3, -2, difflight));

	return objects;
}

RayTracing::HittableList RayTracing::PredefinedWorld::cornell_box() {
	RayTracing::HittableList objects;

	auto red = std::make_shared<RayTracing::Lambertian>(RayTracing::Color(.65, .05, .05));
	auto white = std::make_shared<RayTracing::Lambertian>(RayTracing::Color(.73, .73, .73));
	auto green = std::make_shared<RayTracing::Lambertian>(RayTracing::Color(.12, .45, .15));
	auto light = std::make_shared<RayTracing::DiffuseLight>(RayTracing::Color(15, 15, 15));

	objects.add(std::make_shared<RayTracing::YZRect>(0, 555, 0, 555, 555, green));
	objects.add(std::make_shared<RayTracing::YZRect>(0, 555, 0, 555, 0, red));
	objects.add(std::make_shared<RayTracing::XZRect>(213, 343, 227, 332, 554, light));
	objects.add(std::make_shared<RayTracing::XZRect>(0, 555, 0, 555, 0, white));
	objects.add(std::make_shared<RayTracing::XZRect>(0, 555, 0, 555, 555, white));
	objects.add(std::make_shared<RayTracing::XYRect>(0, 555, 0, 555, 555, white));

	std::shared_ptr<RayTracing::Hittable> box1 =
		std::make_shared<RayTracing::Box>(RayTracing::Point3(0, 0, 0),
			RayTracing::Point3(165, 330, 165), white);
	box1 = std::make_shared<RayTracing::RotateY>(box1, 15);
	box1 = std::make_shared<RayTracing::Translate>(box1, RayTracing::Vec3(265, 0, 295));
	objects.add(box1);

	std::shared_ptr<RayTracing::Hittable> box2 =
		std::make_shared<RayTracing::Box>(RayTracing::Point3(0, 0, 0),
			RayTracing::Point3(165, 165, 165), white);
	box2 = std::make_shared<RayTracing::RotateY>(box2, -18);
	box2 = std::make_shared<RayTracing::Translate>(box2, RayTracing::Vec3(130, 0, 65));
	objects.add(box2);


	return objects;
}

RayTracing::HittableList RayTracing::PredefinedWorld::cornell_smoke()
{
	RayTracing::HittableList objects;

	auto red = std::make_shared<RayTracing::Lambertian>(
		RayTracing::Color(.65, .05, .05));
	auto white = std::make_shared<RayTracing::Lambertian>(
		RayTracing::Color(.73, .73, .73));
	auto green = std::make_shared<RayTracing::Lambertian>(
		RayTracing::Color(.12, .45, .15));
	auto light = std::make_shared<RayTracing::DiffuseLight>(
		RayTracing::Color(7, 7, 7));

	objects.add(std::make_shared<RayTracing::YZRect>(0, 555, 0, 555, 555, green));
	objects.add(std::make_shared<RayTracing::YZRect>(0, 555, 0, 555, 0, red));
	objects.add(std::make_shared<RayTracing::XZRect>(113, 443, 127, 432, 554, light));
	objects.add(std::make_shared<RayTracing::XZRect>(0, 555, 0, 555, 555, white));
	objects.add(std::make_shared<RayTracing::XZRect>(0, 555, 0, 555, 0, white));
	objects.add(std::make_shared<RayTracing::XYRect>(0, 555, 0, 555, 555, white));

	std::shared_ptr<RayTracing::Hittable> box1 =
		std::make_shared<RayTracing::Box>(RayTracing::Point3(0, 0, 0),
			RayTracing::Point3(165, 330, 165), white);
	box1 = std::make_shared<RayTracing::RotateY>(box1, 15);
	box1 = std::make_shared<RayTracing::Translate>(box1,
		RayTracing::Vec3(265, 0, 295));

	std::shared_ptr<RayTracing::Hittable> box2 =
		std::make_shared<RayTracing::Box>(RayTracing::Point3(0, 0, 0),
			RayTracing::Point3(165, 165, 165), white);
	box2 = std::make_shared<RayTracing::RotateY>(box2, -18);
	box2 = std::make_shared<RayTracing::Translate>(box2,
		RayTracing::Vec3(130, 0, 65));

	objects.add(std::make_shared<RayTracing::ConstantMedium>(box1, 0.01,
		RayTracing::Color(0, 0, 0)));
	objects.add(std::make_shared<RayTracing::ConstantMedium>(box2, 0.01,
		RayTracing::Color(1, 1, 1)));

	return objects;
}

RayTracing::HittableList RayTracing::PredefinedWorld::final_scene()
{
	RayTracing::HittableList boxes1;
	auto ground = std::make_shared<RayTracing::Lambertian>(
		RayTracing::Color(0.48, 0.83, 0.53));

	const int boxes_per_side = 20;
	for (int i = 0; i < boxes_per_side; i++) {
		for (int j = 0; j < boxes_per_side; j++) {
			auto w = 100.0;
			auto x0 = -1000.0 + i * w;
			auto z0 = -1000.0 + j * w;
			auto y0 = 0.0;
			auto x1 = x0 + w;
			auto y1 = RayTracing::random_val(1, 101);
			auto z1 = z0 + w;

			boxes1.add(std::make_shared<RayTracing::Box>(
				RayTracing::Point3(x0, y0, z0), RayTracing::Point3(x1, y1, z1),
				ground));
		}
	}

	RayTracing::HittableList objects;

	objects.add(std::make_shared<RayTracing::BVHNode>(boxes1, 0, 1));

	auto light = std::make_shared<RayTracing::DiffuseLight>(
		RayTracing::Color(7, 7, 7));
	objects.add(std::make_shared<RayTracing::XZRect>(123, 423, 147, 412, 554,
		light));

	auto center1 = RayTracing::Point3(400, 400, 200);
	auto center2 = center1 + RayTracing::Vec3(30, 0, 0);
	auto moving_sphere_material = std::make_shared<RayTracing::Lambertian>(
		RayTracing::Color(0.7, 0.3, 0.1));
	objects.add(std::make_shared<RayTracing::MovingSphere>(center1, center2,
		0, 1, 50, moving_sphere_material));

	objects.add(std::make_shared<RayTracing::Sphere>(
		RayTracing::Point3(260, 150, 45), 50,
		std::make_shared<RayTracing::Dielectric>(1.5)));
	objects.add(std::make_shared<RayTracing::Sphere>(
		RayTracing::Point3(0, 150, 145), 50,
		std::make_shared<RayTracing::Metal>(RayTracing::Color(0.8, 0.8, 0.9),
			1.0)
		));

	auto boundary = std::make_shared<RayTracing::Sphere>(
		RayTracing::Point3(360, 150, 145), 70,
		std::make_shared<RayTracing::Dielectric>(1.5));
	objects.add(boundary);
	objects.add(std::make_shared<RayTracing::ConstantMedium>(boundary, 0.2,
		RayTracing::Color(0.2, 0.4, 0.9)));
	boundary = std::make_shared<RayTracing::Sphere>(RayTracing::Point3(0, 0, 0),
		5000, std::make_shared<RayTracing::Dielectric>(1.5));
	objects.add(std::make_shared<RayTracing::ConstantMedium>(boundary, .0001,
		RayTracing::Color(1, 1, 1)));

	auto emat = std::make_shared<RayTracing::Lambertian>(
		std::make_shared<RayTracing::ImageTexture>("earthmap.jpg"));
	objects.add(std::make_shared<RayTracing::Sphere>(
		RayTracing::Point3(400, 200, 400), 100, emat));
	auto pertext = std::make_shared<RayTracing::NoiseTexture>(0.1);
	objects.add(std::make_shared<RayTracing::Sphere>(
		RayTracing::Point3(220, 280, 300), 80,
		std::make_shared<RayTracing::Lambertian>(pertext)));

	RayTracing::HittableList boxes2;
	auto white = std::make_shared<RayTracing::Lambertian>(
		RayTracing::Color(.73, .73, .73));
	int ns = 1000;
	for (int j = 0; j < ns; j++) {
		boxes2.add(std::make_shared<RayTracing::Sphere>(
			RayTracing::Point3::random(0, 165), 10, white));
	}

	objects.add(std::make_shared<RayTracing::Translate>(
		std::make_shared<RayTracing::RotateY>(
			std::make_shared<RayTracing::BVHNode>(boxes2, 0.0, 1.0), 15),
		RayTracing::Vec3(-100, 270, 395)
		)
	);

	return objects;
}

RayTracing::Camera RayTracing::PredefinedCamera::getPredefinedCamera(size_t index)
{
	auto aspect_ratio = 16.0 / 9.0;
	RayTracing::Point3 lookfrom;
	RayTracing::Point3 lookat;
	auto vfov = 40.0;
	auto aperture = 0.0;
	RayTracing::Vec3 vup(0, 1, 0);
	auto dist_to_focus = 10;

	switch (index)
	{
	case 1:
		lookfrom = RayTracing::Point3(13, 2, 3);
		lookat = RayTracing::Point3(0, 0, 0);
		vfov = 20.0;
		aperture = 0.1;
		break;

	case 2: case 3: case 4:
		lookfrom = RayTracing::Point3(13, 2, 3);
		lookat = RayTracing::Point3(0, 0, 0);
		vfov = 20.0;
		break;

	case 5:
		lookfrom = RayTracing::Point3(26, 3, 6);
		lookat = RayTracing::Point3(0, 2, 0);
		vfov = 20.0;
		break;

	case 6:
		aspect_ratio = 1.0;
		lookfrom = RayTracing::Point3(278, 278, -800);
		lookat = RayTracing::Point3(278, 278, 0);
		vfov = 40.0;
		break;

	case 7:
		aspect_ratio = 1.0;
		lookfrom = RayTracing::Point3(278, 278, -800);
		lookat = RayTracing::Point3(278, 278, 0);
		vfov = 40.0;
		break;

	default:
	case 8:
		aspect_ratio = 1.0;
		lookfrom = RayTracing::Point3(478, 278, -600);
		lookat = RayTracing::Point3(278, 278, 0);
		vfov = 40.0;
		break;
	}
	return RayTracing::Camera(lookfrom, lookat, vup, vfov, aspect_ratio, aperture,
		dist_to_focus, 0.0, 1.0);
}

RayTracing::Color RayTracing::Renderer::ray_color(const RayTracing::Ray& r,
	int depth)
{
	RayTracing::HitRecord rec;
	if (depth <= 0)
	{
		return RayTracing::Color(0, 0, 0);
	}
	if (!world_.hit(r, 0.001, RayTracing::infinity, rec))
	{
		return background_;
	}
	RayTracing::Ray scattered;
	RayTracing::Color attenuation;
	RayTracing::Color emited = rec.mat_ptr_->emitted(rec.u_, rec.v_, rec.p_);
	if (!rec.mat_ptr_->scatter(r, rec, attenuation, scattered))
	{
		return emited;
	}
	return emited + attenuation * ray_color(scattered, depth - 1);
	RayTracing::Vec3 unit_direction = r.dir_.unit();
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * RayTracing::Color(1.0, 1.0, 1.0) + t *
		RayTracing::Color(0.5, 0.7, 1.0);
}

void RayTracing::Renderer::render(WritePixelRecall recall)
{
	int image_height_ = image_height();
	std::atomic<int> remaining = image_height_;
#pragma omp parallel for
	for (int j = image_height_ - 1; j >= 0; --j) {
		remaining--;
		std::cerr << "\rScanlines remaining: " << remaining << ' ' << std::flush;
		for (int i = 0; i < image_width_; ++i) {
			RayTracing::Color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel_; ++s) {
				auto u = (i + RayTracing::random_val()) / (image_width_ - 1);
				auto v = (j + RayTracing::random_val()) / (image_height_ - 1);
				RayTracing::Ray r = camera_.get_ray(u, v);
				pixel_color += ray_color(r, max_depth_);
			}
			recall(image_height_ - 1 - j, i, pixel_color, samples_per_pixel_);
		}
	}
}
