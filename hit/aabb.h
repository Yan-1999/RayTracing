#ifndef AABB_H
#define AABB_H

#include "../ray/ray.h"
#include "../vec3/vec3.h"

namespace RayTracing
{

class AABB 
{
public:
    AABB() {}
    AABB(const Point3& a, const Point3& b) { minimum_ = a; maximum_ = b; }

    Point3 min() const { return minimum_; }
    Point3 max() const { return maximum_; }

    bool hit(const Ray& r, double t_min, double t_max) const;

    static AABB surrounding_box(AABB box0, AABB box1);

    Point3 minimum_;
    Point3 maximum_;
};

}


#endif