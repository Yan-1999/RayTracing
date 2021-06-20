#pragma once
#include "material.h"


#ifndef METAL_H
#define METAL_H

namespace RayTracing
{
	class Metal :public Material
	{
    public:
        Metal(const Color& a, ValType f) : albedo_(a), fuzz_(f < 1 ? f : 1) {}

        virtual bool scatter(
            const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
        ) const override;

    public:
        Color albedo_;
        ValType fuzz_;
	};
}

#endif // !METAL_H


