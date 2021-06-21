#include "vec3.h"

RayTracing::Vec3& RayTracing::Vec3::operator+=(const Vec3& v)
{
	e[0] += v.e[0];
	e[1] += v.e[1];
	e[2] += v.e[2];
	return *this;
}

RayTracing::Vec3& RayTracing::Vec3::operator-=(const Vec3& v)
{
	e[0] -= v.e[0];
	e[1] -= v.e[1];
	e[2] -= v.e[2];
	return *this;

}

RayTracing::Vec3& RayTracing::Vec3::operator*=(const ValType t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

RayTracing::Vec3 RayTracing::Vec3::reflect(const Vec3& n)
{
	return *this - 2 * dot(n) * n;
}

RayTracing::Vec3 RayTracing::Vec3::refract(const Vec3& n, ValType etai_over_etat) {
	auto cos_theta = fmin(operator-().dot(n), 1.0);
	Vec3 r_out_perp = etai_over_etat * operator+(cos_theta * n);
	Vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
	return r_out_perp + r_out_parallel;
}

std::ostream& RayTracing::operator<<(std::ostream& out, const RayTracing::Vec3&
	v)
{
	return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

RayTracing::Vec3 RayTracing::operator*(RayTracing::ValType t, const
	RayTracing::Vec3& v)
{
	return v * t;
}
