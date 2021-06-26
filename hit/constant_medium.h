#pragma once
#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include "hit.h"
#include "../material/material.h"
#include "../material/isotropic.h"
#include "../texture/texture.h"

namespace RayTracing
{

	class ConstantMedium : public Hittable
	{
	public:
		ConstantMedium(std::shared_ptr<Hittable> b, ValType d, 
			std::shared_ptr<Texture> a)
			: boundary(b),
			neg_inv_density(-1 / d),
			phase_function(std::make_shared<Isotropic>(a))
		{}

		ConstantMedium(std::shared_ptr<Hittable> b, ValType d, Color c)
			: boundary(b),
			neg_inv_density(-1 / d),
			phase_function(std::make_shared<Isotropic>(c))
		{}

		virtual bool hit(
			const Ray& r, ValType t_min, ValType t_max, HitRecord& rec)
			const override;

		virtual bool bounding_box(ValType time0, ValType time1, 
			AABB& output_box) const override 
		{
			return boundary->bounding_box(time0, time1, output_box);
		}

	public:
		std::shared_ptr<Hittable> boundary;
		std::shared_ptr<Material> phase_function;
		ValType neg_inv_density;
	};

}

#endif