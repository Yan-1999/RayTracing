#include "perlin.h"

#include <cstdlib>

RayTracing::ValType RayTracing::Perlin::noise(const Point3& p) const
{
	auto u = p.x() - floor(p.x());
	auto v = p.y() - floor(p.y());
	auto w = p.z() - floor(p.z());

	auto i = static_cast<int>(floor(p.x()));
	auto j = static_cast<int>(floor(p.y()));
	auto k = static_cast<int>(floor(p.z()));
	Vec3 c[2][2][2];

	for (int di = 0; di < 2; di++)
	{
		for (int dj = 0; dj < 2; dj++)
		{
			for (int dk = 0; dk < 2; dk++)
			{
				c[di][dj][dk] = ranvec_[
					perm_x[(i + di) & 255] ^
						perm_y[(j + dj) & 255] ^
						perm_z[(k + dk) & 255]
				];
			}
		}
	}

	return perlin_interp(c, u, v, w);
}

RayTracing::ValType RayTracing::Perlin::turb(const Point3& p, int depth) const
{
	auto accum = 0.0;
	auto temp_p = p;
	auto weight = 1.0;

	for (int i = 0; i < depth; i++)
	{
		accum += weight * noise(temp_p);
		weight *= 0.5;
		temp_p *= 2;
	}

	return std::abs(accum);
}

RayTracing::ValType RayTracing::Perlin::trilinear_interp(ValType c[2][2][2],
	ValType u, ValType v, ValType w)
{
	auto accum = 0.0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				accum += (i * u + (1 - i) * (1 - u)) *
					(j * v + (1 - j) * (1 - v)) *
					(k * w + (1 - k) * (1 - w)) * c[i][j][k];
			}
		}
	}
	return accum;
}

RayTracing::ValType RayTracing::Perlin::perlin_interp(Vec3 c[2][2][2],
	ValType u, ValType v, ValType w)
{
	auto uu = u * u * (3 - 2 * u);
	auto vv = v * v * (3 - 2 * v);
	auto ww = w * w * (3 - 2 * w);
	auto accum = 0.0;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			for (int k = 0; k < 2; k++) {
				Vec3 weight_v(u - i, v - j, w - k);
				accum += (i * uu + (1 - i) * (1 - uu))
					* (j * vv + (1 - j) * (1 - vv))
					* (k * ww + (1 - k) * (1 - ww))
					* c[i][j][k].dot(weight_v);
			}

		}

	}

	return accum;
}
