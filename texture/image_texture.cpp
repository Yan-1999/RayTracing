#include "image_texture.h"

#include <iostream>

#include <opencv2/imgcodecs/imgcodecs.hpp>

RayTracing::ImageTexture::ImageTexture(const char* filename)
{
	auto components_per_pixel = bytes_per_pixel;

	data_ = cv::imread(filename);

	if (data_.empty()) 
	{
		std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
		width = height = 0;
	}

	bytes_per_scanline = bytes_per_pixel * width;
	height = data_.rows;
	width = data_.cols;
}

RayTracing::Color RayTracing::ImageTexture::value(ValType u, ValType v,
	const Vec3& p) const
{
	// If we have no texture data_, then return solid cyan as a debugging aid.
	if (data_.empty())
	{
		return Color(0, 1, 1);
	}

	// Clamp input texture coordinates to [0,1] x [1,0]
	u = std::clamp(u, 0.0, 1.0);
	v = 1.0 - std::clamp(v, 0.0, 1.0);  // Flip V to image coordinates

	auto i = static_cast<int>(u * width);
	auto j = static_cast<int>(v * height);

	// Clamp integer mapping, since actual coordinates should be less than 1.0
	if (i >= width)
	{
		i = width - 1;
	};
	if (j >= height)
	{
		j = height - 1;
	};

	const auto color_scale = 1.0 / 255.0;
	cv::Vec3b pixel = data_.at<cv::Vec3b>(j, i);

	return Color(color_scale * pixel[2], color_scale * pixel[1],
		color_scale * pixel[0]);
}
