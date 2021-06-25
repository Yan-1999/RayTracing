#pragma once

#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include "material.h"
#include "../texture/texture.h"
#include "../texture/solid_color.h"

namespace RayTracing
{
	class DiffuseLight :public Material
	{
	public:
		DiffuseLight(std::shared_ptr<Texture> a) : emit_(a) {}
		DiffuseLight(Color c) : emit_(std::make_shared<SolidColor>(c))
		{}

		virtual bool scatter(
			const Ray& r_in, const HitRecord& rec, Color& attenuation,
			Ray& scattered) const override {
			return false;
		}

		virtual Color emitted(ValType u, ValType v, const Point3& p) const
			override
		{
			return emit_->value(u, v, p);
		}

	public:
		std::shared_ptr<Texture> emit_;
	};
}

#endif // !DIFFUSE_LIGHT_H
