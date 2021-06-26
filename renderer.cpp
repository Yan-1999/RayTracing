#include "renderer.h"

#include "material/material.h"

RayTracing::Color RayTracing::Renderer::ray_color(const RayTracing::Ray& r,
	int depth)
{
	RayTracing::HitRecord rec;
	if (depth <= 0)
	{
		return RayTracing::Color(0, 0, 0);
	}
	if (!world_.hit(r, 0.001, RayTracing::infinity, rec))
	{
		return background_;
	}
	RayTracing::Ray scattered;
	RayTracing::Color attenuation;
	RayTracing::Color emited = rec.mat_ptr_->emitted(rec.u_, rec.v_, rec.p_);
	if (!rec.mat_ptr_->scatter(r, rec, attenuation, scattered))
	{
		return emited;
	}
	return emited + attenuation * ray_color(scattered, depth - 1);
	RayTracing::Vec3 unit_direction = r.dir_.unit();
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * RayTracing::Color(1.0, 1.0, 1.0) + t *
		RayTracing::Color(0.5, 0.7, 1.0);
}

void RayTracing::Renderer::render(WritePixelRecall recall)
{
	int image_height_ = image_height();
	std::atomic<int> remaining = image_height_;
#pragma omp parallel for
	for (int j = image_height_ - 1; j >= 0; --j) {
		remaining--;
		std::cerr << "\rScanlines remaining: " << remaining << ' ' << std::flush;
		for (int i = 0; i < image_width_; ++i) {
			RayTracing::Color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel_; ++s) {
				auto u = (i + RayTracing::random_val()) / (image_width_ - 1);
				auto v = (j + RayTracing::random_val()) / (image_height_ - 1);
				RayTracing::Ray r = camera_.get_ray(u, v);
				pixel_color += ray_color(r, max_depth_);
			}
			recall(image_height_ - 1 - j, i, pixel_color, samples_per_pixel_);
		}
	}
}
