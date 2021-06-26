#include <atomic>
#include <fstream>

#include <boost/json.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>

#include "vec3/color.h"
#include "predef.h"
#include "renderer.h"

void write_color_to_mat(int j, int i, RayTracing::Color c, int samples_per_pixel,
	cv::Mat& mat)
{
	auto r = c.x();
	auto g = c.y();
	auto b = c.z();

	// Divide the color by the number of samples.
	auto scale = 1.0 / samples_per_pixel;
	r = std::sqrt(scale * r);
	g = std::sqrt(scale * g);
	b = std::sqrt(scale * b);

	// Write the translated [0,255] value of each color component.
	mat.at<cv::Vec3b>(j, i)[0] = static_cast<uchar>(256 * std::clamp(b, 0.0, 0.999));
	mat.at<cv::Vec3b>(j, i)[1] = static_cast<uchar>(256 * std::clamp(g, 0.0, 0.999));
	mat.at<cv::Vec3b>(j, i)[2] = static_cast<uchar>(256 * std::clamp(r, 0.0, 0.999));
}

int main()
{
	RayTracing::Renderer renderer(RayTracing::PredefinedWorld::final_scene(),
		RayTracing::PredefinedCamera::getPredefinedCamera(0));
	cv::Mat img_mat(renderer.image_height(), 
		renderer.image_width(), CV_8UC3);
	renderer.render(std::bind(write_color_to_mat,
		std::placeholders::_1,
		std::placeholders::_2,
		std::placeholders::_3,
		std::placeholders::_4,
		img_mat));
	cv::imwrite("img.jpg", img_mat);
	std::cerr << "\nDone.\n";
}
