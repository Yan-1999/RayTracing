#pragma once
#ifndef BVH_H
#define BVH_H

#include "hit.h"
#include "hittable_list.h"

namespace RayTracing
{

class BVHNode :public Hittable
{
public:
    BVHNode();

    BVHNode(const HittableList& list, double time0, double time1)
        : BVHNode(list.objects(), 0, list.objects().size(), time0, time1)
    {}

    BVHNode(
        const std::vector<std::shared_ptr<Hittable>>& src_objects,
        size_t start, size_t end, double time0, double time1);

    virtual bool hit(
        const Ray& r, double t_min, double t_max, HitRecord& rec) const
        override;

    virtual bool bounding_box(double time0, double time1, AABB& output_box)
        const override
    {
        output_box = box_;
        return true;
    }


public:
    std::shared_ptr<Hittable> left_;
    std::shared_ptr<Hittable> right_;
    AABB box_;
};

}
#endif
