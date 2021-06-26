#include "dielectric.h"

#include "../hit/hit.h"

bool RayTracing::Dielectric::scatter(const Ray& r_in,
	const HitRecord& rec, Color& attenuation, Ray& scattered) const
{
	attenuation = Color(1.0, 1.0, 1.0);
	ValType refraction_ratio = rec.front_face_ ? (1.0 / ir_) : ir_;

	Vec3 unit_direction = r_in.direction().unit();
    ValType cos_theta = std::min(-unit_direction.dot(rec.normal_), 1.0);
    ValType sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    Vec3 direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_val())
    {
        direction = unit_direction.reflect(rec.normal_);
    }
    else
    {
        direction = unit_direction.refract(rec.normal_, refraction_ratio);
    }
    scattered = Ray(rec.p_, direction, r_in.time());
	return true;
}
