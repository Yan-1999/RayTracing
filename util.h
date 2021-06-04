#pragma once

#ifndef UTIL_H
#define UTIL_H


#ifdef _MSVC_LANG
#if _MSVC_LANG > 201703L
#define USING_STD_NUMBER
#elif __cplusplus > 201703L
#define USING_STD_NUMBER
#endif // _MSVC_LANG > 201703L
#endif // _MSVC_LANG

#include <limits>
#ifdef USING_STD_NUMBER
#include <numbers>
#endif // USING_STD_NUMBER
#include <random>

namespace RayTracing
{
	using ValType = double;

	constexpr ValType infinity = std::numeric_limits<ValType>::infinity();

#ifdef USING_STD_NUMBER
	constexpr ValType pi = std::numbers::pi_v<ValType>;
#else
	constexpr ValType pi = 3.1415926535897932385;
#endif // USING_STD_NUMBER

	constexpr ValType rad_per_deg = pi / 180.0;

	inline ValType degrees_to_radians(ValType degrees)
	{
		return degrees * rad_per_deg;
	}

	inline ValType rand_uni()
	{
		static std::uniform_real_distribution<ValType> distribution(0.0, 1.0);
		static std::ranlux24 generator;
		return distribution(generator);
	}
}

#endif // !UTIL_H
