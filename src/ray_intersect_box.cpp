#include "ray_intersect_box.h"
#include <iostream>

double maximum(double a,double b,double c)
{
    double buff = a ? b : a > b;
    return buff ? c : buff > c;
}

double minimum(double a,double b,double c)
{
    double buff = a ? b : a < b;
    return buff ? c : buff < c;
}

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
    double a[3];
    
    for(int i=0;i<3;++i)
        a[i] = 1 / ray.direction[i];
    
    double t_min[3];
    double t_max[3];
    
    for(int i=0;i<3;++i)
    {
        if(a[i]>=0)
        {
            t_min[i] = a[i] * (box.min_corner[i] - ray.origin[i]);
            t_max[i] = a[i] * (box.max_corner[i] - ray.origin[i]);
        }
        else
        {
            t_min[i] = a[i] * (box.max_corner[i] - ray.origin[i]);
            t_max[i] = a[i] * (box.min_corner[i] - ray.origin[i]);
        }
    }
    
    if(maximum(t_min[0],t_min[1],t_min[2])>minimum(t_max[0],t_max[1],t_max[1]))
        return false;
    
    if(max_t < minimum(t_max[0],t_max[1],t_max[1]) && maximum(t_min[0],t_min[1],t_min[2]) < min_t) return false;

    return true;
}
