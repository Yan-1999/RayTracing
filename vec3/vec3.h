#pragma once

#ifndef VEC_H
#define VEC_H

#include <cassert>
#include <cmath>
#include <iostream>

#include "../util.h"

constexpr int VEC_DIMENTION = 3;

namespace RayTracing
{

	class Vec3
	{
	public:

		Vec3() : e{ 0, 0, 0 } {};
		Vec3(ValType x, ValType y, ValType z) : e{ x, y, z } {};

		ValType x() { return e[0]; }
		ValType y() { return e[1]; }
		ValType z() { return e[2]; }

		void set(ValType x, ValType y, ValType z)
		{
			e[0] = x;
			e[1] = y;
			e[2] = z;
		}
		Vec3 operator-() const { return Vec3(-e[0], -e[1], -e[2]); }
		ValType operator[](size_t i)
		{
			assert(0 <= i && i < VEC_DIMENTION);
			return e[i];
		}
		const ValType operator[](size_t i) const
		{
			assert(0 <= i && i < VEC_DIMENTION);
			return e[i];
		}

		Vec3& operator+=(const Vec3& v);
		Vec3& operator-=(const Vec3& v);
		Vec3& operator*=(const ValType t);
		Vec3& operator/=(const ValType t) { return *this *= 1 / t; }

		void add(const Vec3& v, Vec3& out) const
		{
			out.set(e[0] + v.e[0], e[1] + v.e[1], e[2] + v.e[2]);
		}
		Vec3 operator+(const Vec3& v) const
		{
			Vec3 ret;
			add(v, ret);
			return ret;
		}
		void subtract(const Vec3& v, Vec3& out) const
		{
			out.set(e[0] - v.e[0], e[1] - v.e[1], e[2] - v.e[2]);
		}
		Vec3 operator-(const Vec3& v) const
		{
			Vec3 ret;
			subtract(v, ret);
			return ret;
		}
		void multiply(const Vec3& v, Vec3& out) const
		{
			out.set(e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2]);
		}
		Vec3 operator*(const Vec3& v) const
		{
			Vec3 ret;
			multiply(v, ret);
			return ret;
		}
		void multiply(ValType t, Vec3& out) const
		{
			out.set(t * e[0], t * e[1], t * e[2]);
		}
		Vec3 operator*(ValType t) const
		{
			Vec3 ret;
			multiply(t, ret);
			return ret;
		}
		void divide(ValType t, Vec3& out) const
		{
			multiply(1 / t, out);
		}
		Vec3 operator/(ValType t) const
		{
			return operator*(1 / t);
		}

		ValType dot(const Vec3& v) const
		{
			return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2];
		}
		void cross(const Vec3& v, Vec3& out) const
		{
			out.set(e[1] * v.e[2] - e[2] * v.e[1],
				e[2] * v.e[0] - e[0] * v.e[2],
				e[0] * v.e[1] - e[1] * v.e[0]);
		}
		Vec3 cross(const Vec3& v) const
		{
			Vec3 ret;
			cross(v, ret);
			return ret;
		}
		void unit(Vec3& out)
		{
			divide(length(), out);
		}
		Vec3 unit() const
		{
			return operator/(length());
		}

		ValType length() const
		{
			return std::sqrt(length_squared());
		}
		ValType length_squared() const {
			ValType x = e[0], y = e[1], z = e[2];
			return x * x + y * y + z * z;
		}

	private:
		ValType e[VEC_DIMENTION];
	};
	using Point3 = Vec3;   // 3D point

	std::ostream& operator<<(std::ostream& out, const RayTracing::Vec3& v);
	RayTracing::Vec3 operator*(RayTracing::ValType t, const
		RayTracing::Vec3& v);
}

#endif // !VEC_H
