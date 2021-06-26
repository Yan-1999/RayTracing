#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <functional>

#include "vec3/color.h"
#include "hit/hittable_list.h"
#include "ray/camera.h"

namespace RayTracing
{
	namespace PredefinedWorld
	{
		HittableList random_scene();

		HittableList two_spheres();

		HittableList two_perlin_spheres();

		HittableList earth();

		HittableList simple_light();

		HittableList cornell_box();

		HittableList cornell_smoke();

		HittableList final_scene();
	}

	namespace PredefinedCamera
	{
		RayTracing::Camera getPredefinedCamera(size_t index);
	}

	class Renderer
	{
		using WritePixelRecall = std::function<void(int, int,
			RayTracing::Color, int)>;

	public:
		Renderer(HittableList world, Camera camera,
			int image_width = 800, int samples_per_pixel = 100,
			Color background = Color(0, 0, 0), int max_depth = 50)
			:world_(world), camera_(camera), background_(background),
			image_width_(image_width), samples_per_pixel_(samples_per_pixel),
			max_depth_(max_depth)
		{}

		HittableList& world() { return world_; }
		Color& background() { return background_; }
		int image_width() { return image_width_; }
		int image_height()
		{
			return static_cast<int>(image_width_ / camera_.aspect_ratio());
		}

		void render(WritePixelRecall recall);

	private:
		Color ray_color(const Ray& r, int depth);

		HittableList world_;
		Camera camera_;
		Color background_;
		int image_width_;
		int samples_per_pixel_;
		int max_depth_;
	};

}

#endif // !SCENE_H
