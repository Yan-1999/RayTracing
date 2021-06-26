#pragma once
#ifndef CUSTOM_H
#define CUSTOM_H

#include "raytracing.h"

RayTracing::HittableList MyWorld()
{
	RayTracing::HittableList objects;

	auto light = std::make_shared<RayTracing::DiffuseLight>(
		RayTracing::Color(10, 10, 10));
	auto lamb = std::make_shared<RayTracing::Lambertian>(
		RayTracing::Color(0.48, 0.83, 0.53));
	auto lamb1 = std::make_shared<RayTracing::Lambertian>(
		RayTracing::Color(0.7, 0.3, 0.1));
	auto metal = std::make_shared<RayTracing::Metal>(
		RayTracing::Color(0.8, 0.8, 0.9),
		1.0);
	auto dielectric = std::make_shared<RayTracing::Dielectric>(
		1.5);

	objects.add(std::make_shared<RayTracing::Sphere>(
		RayTracing::Point3(200, 500, 500),
		100,
		light));
	objects.add(std::make_shared<RayTracing::Sphere>(
		RayTracing::Point3(500, 300, 0),
		50,
		lamb1));
	objects.add(std::make_shared<RayTracing::Sphere>(
		RayTracing::Point3(100, 300, 250),
		20,
		dielectric));
	objects.add(std::make_shared<RayTracing::Box>(
		RayTracing::Point3(100, 200, 100),
		RayTracing::Point3(200, 300, 200),
		metal));


	RayTracing::HittableList boxes;
	const int boxes_per_side = 20;
	for (int i = 0; i < boxes_per_side; i++)
	{
		for (int j = 0; j < boxes_per_side; j++)
		{
			auto g_texture = ((i + j) % 2) ? lamb : lamb1;
			auto w = 100.0;
			auto x0 = -1000.0 + i * w;
			auto z0 = -1000.0 + j * w;
			auto y0 = 0.0;
			auto x1 = x0 + w;
			auto y1 = RayTracing::random_val(1, 101);
			auto z1 = z0 + w;

			boxes.add(std::make_shared<RayTracing::Box>(
				RayTracing::Point3(x0, y0, z0), RayTracing::Point3(x1, y1, z1),
				g_texture));
		}
	}
	objects.add(std::make_shared<RayTracing::BVHNode>(boxes, 0, 1));
	return objects;
}

RayTracing::Camera MyCamera()
{
	return RayTracing::Camera(
		RayTracing::Point3(500, 300, -600),
		RayTracing::Point3(300, 300, 0),
		RayTracing::Vec3(0, 1, 0),
		40, 1, 0, 10, 0, 1);
}

RayTracing::Color MyBackground()
{
	return RayTracing::Color(0.1, 0.3, 0.7);
}

#endif // !CUSTOM_H
