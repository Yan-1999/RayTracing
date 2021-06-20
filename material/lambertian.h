#pragma once

#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"

namespace RayTracing
{

	class Lambertian :public Material
	{
    public:
        Lambertian(const Color& a) : albedo_(a) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const override;

    public:
        Color albedo_;
	};

}

#endif

