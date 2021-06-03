#include "color.h"

constexpr RayTracing::color::ValType MAX = 255.999;

void RayTracing::write_color(std::ostream& out, color pixel_color)
{
    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(MAX * pixel_color.x()) << ' '
        << static_cast<int>(MAX * pixel_color.y()) << ' '
        << static_cast<int>(MAX * pixel_color.z()) << '\n';
}
