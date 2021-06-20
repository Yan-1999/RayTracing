#include "lambertian.h"

#include "../hit/hit.h"

bool RayTracing::Lambertian::scatter(const Ray& r_in,
    const HitRecord& rec, Color& attenuation, Ray& scattered) const 
{
    auto scatter_direction = rec.normal_ + RayTracing::Vec3::RandomUnitVector();
    if (scatter_direction.near_zero())
    {
        scatter_direction = rec.normal_;
    }
    scattered = Ray(rec.p_, scatter_direction);
    attenuation = albedo_;
    return true;
}
