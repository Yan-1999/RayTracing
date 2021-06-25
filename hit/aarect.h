#pragma once

#ifndef AARECT_H
#define AARECT_H

#include "hit.h"
#include "../Material/Material.h"

namespace RayTracing
{

	class XYRect :public Hittable
	{
	public:
		XYRect() {}

		XYRect(ValType x0, ValType x1, ValType y0, ValType y1, ValType k,
			std::shared_ptr<Material> mat)
			: x0_(x0), x1_(x1), y0_(y0), y1_(y1), k_(k), mp(mat) {};

		virtual bool hit(const Ray& r, ValType t_min, ValType t_max,
			HitRecord& rec) const override;

		virtual bool bounding_box(ValType time0, ValType time1,
			AABB& output_box) const override
		{
			// The bounding box must have non-zero width in each dimension,
			// so pad the Z dimension a small amount.
			output_box = AABB(Point3(x0_, y0_, k_ - 0.0001),
				Point3(x1_, y1_, k_ + 0.0001));
			return true;
		}

	public:
		std::shared_ptr<Material> mp;
		ValType x0_, x1_, y0_, y1_, k_;
	};

	class XZRect : public Hittable {
	public:
		XZRect() {}

		XZRect(ValType x0, ValType x1, ValType z0, ValType z1, ValType k,
			std::shared_ptr<Material> mat)
			: x0_(x0), x1_(x1), z0_(z0), z1_(z1), k_(k), mp_(mat) {};

		virtual bool hit(const Ray& r, ValType t_min, ValType t_max,
			HitRecord& rec) const override;

		virtual bool bounding_box(ValType time0, ValType time1, AABB& output_box)
			const override
		{
			// The bounding box must have non-zero width in each dimension, so pad the Y
			// dimension a small amount.
			output_box = AABB(Point3(x0_, k_ - 0.0001, z0_), Point3(x1_, k_ + 0.0001, z1_));
			return true;
		}

	public:
		std::shared_ptr<Material> mp_;
		ValType x0_, x1_, z0_, z1_, k_;
	};

	class YZRect : public Hittable {
	public:
		YZRect() {}

		YZRect(ValType y0, ValType y1, ValType z0, ValType z1, ValType k,
			std::shared_ptr<Material> mat)
			: y0_(y0), y1_(y1), z0_(z0), z1_(z1), k_(k), mp(mat) {};

		virtual bool hit(const Ray& r, ValType t_min, ValType t_max,
			HitRecord& rec) const override;

		virtual bool bounding_box(ValType time0, ValType time1, AABB& output_box)
			const override
		{
			// The bounding box must have non-zero width in each dimension, so pad the X
			// dimension a small amount.
			output_box = AABB(Point3(k_ - 0.0001, y0_, z0_), Point3(k_ + 0.0001, y1_, z1_));
			return true;
		}

	public:
		std::shared_ptr<Material> mp;
		ValType y0_, y1_, z0_, z1_, k_;
	};

}

#endif // !AARECT_H
