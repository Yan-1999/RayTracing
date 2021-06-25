#pragma once

#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "../texture/solid_color.h"

namespace RayTracing
{

	class Lambertian :public Material
	{
    public:
        Lambertian(const Color& a) : albedo_(std::make_shared<SolidColor>(a)) {}
        Lambertian(std::shared_ptr<Texture> a) : albedo_(a) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const override;

    public:
        std::shared_ptr<Texture> albedo_;
	};

}

#endif

