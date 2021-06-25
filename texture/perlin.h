#pragma once

#ifndef PERLIN_H
#define PERLIN_H

#include "../util.h"
#include "../vec3/vec3.h"

namespace RayTracing
{

	class Perlin
	{
	public:
		Perlin()
		{
			ranvec_ = new Vec3[point_count];
			for (int i = 0; i < point_count; ++i)
			{
				ranvec_[i] = Vec3::random(-1, 1).unit();
			}

			perm_x = perlin_generate_perm();
			perm_y = perlin_generate_perm();
			perm_z = perlin_generate_perm();
		}

		~Perlin()
		{
			delete[] ranvec_;
			delete[] perm_x;
			delete[] perm_y;
			delete[] perm_z;
		}

		ValType noise(const Point3& p) const;

		ValType turb(const Point3& p, int depth = 7) const;

	private:
		static const int point_count = 256;
		Vec3* ranvec_;
		int* perm_x;
		int* perm_y;
		int* perm_z;

		static int* perlin_generate_perm()
		{
			auto p = new int[point_count];

			for (int i = 0; i < Perlin::point_count; i++)
				p[i] = i;

			permute(p, point_count);

			return p;
		}

		static void permute(int* p, int n)
		{
			for (int i = n - 1; i > 0; i--)
			{
				int target = random_int(0, i);
				int tmp = p[i];
				p[i] = p[target];
				p[target] = tmp;
			}
		}

		static ValType trilinear_interp(ValType c[2][2][2], ValType u,
			ValType v, ValType w);

		static ValType perlin_interp(Vec3 c[2][2][2], ValType u, ValType v,
			ValType w);
	};
}
#endif // !PERLIN_H
