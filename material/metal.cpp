#include "metal.h"

#include "../hit/hit.h"

bool RayTracing::Metal::scatter(const Ray& r_in, const HitRecord& rec,
	Color& attenuation, Ray& scattered) const
{
	Vec3 reflected = r_in.direction().unit().reflect(rec.normal_);
	scattered = Ray(rec.p_, reflected + fuzz_ * Vec3::RandomInUnitSphere(),
		r_in.time());
	attenuation = albedo_;
	return (scattered.direction().dot(rec.normal_) > 0);
}
