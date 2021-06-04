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
