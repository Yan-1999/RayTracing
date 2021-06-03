#include "vec3.h"

inline RayTracing::vec3& RayTracing::vec3::operator+=(const vec3& v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

inline RayTracing::vec3& RayTracing::vec3::operator*=(const type t)
{
	e[0] *= t;
	e[1] *= t;
	e[2] *= t;
	return *this;
}

std::ostream& RayTracing::operator<<(std::ostream& out, const vec3& v)
{
	return out << v[0] << ' ' << v[1] << ' ' << v[2];
}

RayTracing::vec3 RayTracing::operator*(vec3::type t, const vec3& v)
{
	return vec3(t * v[0], t * v[1], t * v[2]);
}
