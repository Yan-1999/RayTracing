#include "material.h"

#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include <cmath>

namespace RayTracing
{
	class Dielectric :public Material
	{
	public:
		Dielectric(ValType index_of_refraction) : ir_(index_of_refraction) {}

		virtual bool scatter(
			const Ray& r_in, const HitRecord& rec, Color& attenuation, Ray& scattered
		) const override;

	public:
		ValType ir_; // Index of Refraction

	private:
		static ValType reflectance(ValType cosine, ValType ref_idx)
		{
			// Use Schlick's approximation for reflectance.
			auto r0 = (1 - ref_idx) / (1 + ref_idx);
			r0 = r0 * r0;
			return r0 + (1 - r0) * std::pow((1 - cosine), 5);
		}
	};
}

#endif // !DIELECTRIC_H
