#pragma once

#ifndef HITTABLELIST_H
#define HITTABLELIST_H

#include <memory>
#include <vector>

#include "hit.h"

namespace RayTracing
{
	class HittableList :public Hittable

	{
    public:
        HittableList() {}
        HittableList(std::shared_ptr<Hittable> object) { add(object); }

        void clear() { objects_.clear(); }
        void add(std::shared_ptr<Hittable> object)
        { 
            objects_.push_back(object);
        }

        virtual bool hit(const Ray& r, ValType t_min, ValType t_max,
            HitRecord& rec) const override;

    private:
        std::vector<std::shared_ptr<Hittable>> objects_;
	};

}

#endif // !HITTABLELIST_H