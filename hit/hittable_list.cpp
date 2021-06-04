#include "hittable_list.h"

bool RayTracing::HittableList::hit(const Ray& r, ValType t_min, 
    ValType t_max, HitRecord& rec) const
{
    HitRecord temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : objects_)
    {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) 
        {
            hit_anything = true;
            closest_so_far = temp_rec.t_;
            rec = temp_rec;
        }
    }

    return hit_anything;
}
