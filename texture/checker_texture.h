#pragma once

#ifndef CHECKER_TEXTURE_H
#define CHECKER_TEXTURE_H

#include <cmath>

#include "texture.h"
#include "solid_color.h"

namespace RayTracing
{

	class CheckerTexture :public Texture
	{
    public:
        CheckerTexture() {}

        CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd)
            : even_(even), odd_(odd) {}

        CheckerTexture(Color c1, Color c2)
            : even_(std::make_shared<SolidColor>(c1)), 
            odd_(std::make_shared<SolidColor>(c2)) {}

        virtual Color value(ValType u, ValType v, const Point3& p) const override {
            auto sines = std::sin(10 * p.x()) * std::sin(10 * p.y()) * std::sin(10 * p.z());
            if (sines < 0)
                return odd_->value(u, v, p);
            else
                return even_->value(u, v, p);
        }

    public:
        std::shared_ptr<Texture> odd_;
        std::shared_ptr<Texture> even_;
	};
}
#endif // !CHECKER_TEXTURE_H

