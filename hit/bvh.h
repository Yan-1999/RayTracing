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

    BVHNode(const HittableList& list, ValType time0, ValType time1)
        : BVHNode(list.objects(), 0, list.objects().size(), time0, time1)
    {}

    BVHNode(
        const std::vector<std::shared_ptr<Hittable>>& src_objects,
        size_t start, size_t end, ValType time0, ValType time1);

    virtual bool hit(
        const Ray& r, ValType t_min, ValType t_max, HitRecord& rec) const
        override;

    virtual bool bounding_box(ValType time0, ValType time1, AABB& output_box)
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

bool box_compare(const std::shared_ptr<RayTracing::Hittable>& a,
    const std::shared_ptr<RayTracing::Hittable>& b, size_t axis);
bool box_x_compare(const std::shared_ptr<RayTracing::Hittable>& a,
    const std::shared_ptr<RayTracing::Hittable>& b);
bool box_y_compare(const std::shared_ptr<RayTracing::Hittable>& a,
    const std::shared_ptr<RayTracing::Hittable>& b);
bool box_z_compare(const std::shared_ptr<RayTracing::Hittable>& a,
    const std::shared_ptr<RayTracing::Hittable>& b);


}
#endif
