#pragma once

#ifndef  PREDEF_H
#define  PREDEF_H

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
		RayTracing::HittableList getPredefinedWorld(size_t index);
	}

	namespace PredefinedCamera
	{
		RayTracing::Camera getPredefinedCamera(size_t index);
	}

	namespace PredefinedBackground
	{
		RayTracing::Color getPredefinedBackground(size_t index);
	}
}

#endif // ! PREDEF_H
