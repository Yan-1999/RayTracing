#pragma once

#ifndef ISOTROPIC_H
#define ISOTROPIC_H

#include "material.h"
#include "../hit/hit.h"
#include "../texture/solid_color.h"

namespace RayTracing
{

	class Isotropic :
		public Material
	{
	public:
		Isotropic(Color c) : albedo_(std::make_shared<SolidColor>(c)) {}
		Isotropic(std::shared_ptr<Texture> a) : albedo_(a) {}

		virtual bool scatter(
			const Ray& r_in, const HitRecord& rec, Color& attenuation,
			Ray& scattered)const override 
		{
			scattered = Ray(rec.p_, Vec3::RandomInUnitSphere(), r_in.time());
			attenuation = albedo_->value(rec.u_, rec.v_, rec.p_);
			return true;
		}

	public:
		std::shared_ptr<Texture> albedo_;
	};

}
#endif // !ISOTROPIC_H
