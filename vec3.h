#pragma once

#ifndef VEC_H
#define VEC_H

#include <cassert>
#include <cmath>
#include <iostream>

constexpr int VEC_DIMENTION = 3;

namespace RayTracing
{

	class vec3
	{
	public:
		using type = double;

		vec3() : e{ 0, 0, 0 } {};
		vec3(type x, type y, type z) : e{ x, y, z } {};

		type x() { return e[0]; }
		type y() { return e[1]; }
		type z() { return e[2]; }

		vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
		type operator[](size_t i)
		{
			assert(0 <= i && i < VEC_DIMENTION);
			return e[i];
		}
		const type operator[](size_t i) const
		{
			assert(0 <= i && i < VEC_DIMENTION);
			return e[i];
		}

		inline vec3& operator+=(const vec3& v);
		inline vec3& operator*=(const type t);
		vec3& operator/=(const type t) { return *this *= 1 / t; }

		vec3 operator+(const vec3& v)
		{
			return vec3(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
		}
		vec3 operator-(const vec3& v)
		{
			return vec3(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
		}
		vec3 operator*(const vec3& v)
		{
			return vec3(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]);
		}
		vec3 operator*(type t)
		{
			return vec3(t * e[0], t * e[1], t * e[2]);
		}
		vec3 operator/(type t)
		{
			return this->operator*(1 / t);
		}

		type dot(const vec3& v)
		{
			return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2];
		}
		vec3 cross(const vec3& v)
		{
			return vec3(e[1] * v.e[2] - e[2] * v.e[1],
				e[2] * v.e[0] - e[0] * v.e[2],
				e[0] * v.e[1] - e[1] * v.e[0]);
		}
		vec3 unit()
		{
			return this->operator/(this->length());
		}

		type length() const
		{
			return std::sqrt(length_squared());
		}
		type length_squared() const {
			type x = e[0], y = e[1], z = e[2];
			return x * x + y * y + z * z;
		}

	private:
		type e[VEC_DIMENTION];
	};

	inline std::ostream& operator<<(std::ostream& out, const vec3& v);
	inline vec3 operator*(vec3::type t, const vec3& v);

	using point3 = vec3;   // 3D point
}

#endif // !VEC_H
