#pragma once

#ifndef RAY_H
#define RAY_H

#include "vec3.h"

namespace RayTracing
{
    class Ray {
    public:
        using ValType = Vec3::ValType;

        Ray() {}
        Ray(const Point3& origin, const Vec3& direction)
            : orig_(origin), dir_(direction)
        {}

        Point3 origin() const { return orig_; }
        Vec3 direction() const { return dir_; }

        void at(Point3::ValType t, Point3& out) const
        {
            dir_.multiply(t, out);
            out += orig_;
        }
        Point3 at(Point3::ValType t) const
        {
            Point3 ret;
            at(t, ret);
            return ret;
        }

    public:
        Point3 orig_;
        Vec3 dir_;
    };
}

#endif
