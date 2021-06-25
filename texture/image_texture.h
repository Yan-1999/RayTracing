/* Using Opencv */
#pragma once

#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include "texture.h"

#include <opencv2/core/mat.hpp>

namespace RayTracing
{

	class ImageTexture :public Texture
	{
	public:
		const static int bytes_per_pixel = 3;
		const static int cv_type = CV_8UC3;

		ImageTexture()
			: data_(), width(0), height(0), bytes_per_scanline(0) {}

		ImageTexture(const char* filename);

		virtual Color value(ValType u, ValType v, const Vec3& p) const override;

	private:
		cv::Mat data_;
		int width, height;
		int bytes_per_scanline;
	};

}
#endif // !IMAGE_TEXTURE_H
