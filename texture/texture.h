#pragma once

#ifndef TEXTURE_H
#define TEXTURE_H

#include "../vec3/color.h"

namespace RayTracing
{

class Texture
{
public:
	virtual Color value(ValType u, ValType v, const Point3& p) const = 0;
};

}

#endif // !TEXTURE_H
