#include "ray_intersect_triangle.h"

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
    
    Eigen::Vector3d c_a = A;
    Eigen::Vector3d c_b = B;
    Eigen::Vector3d c_c = C;
    
    double a = c_a[0] - c_b[0];
    double b = c_a[1] - c_b[1];
    double c = c_a[2] - c_b[2];
    double d = c_a[0] - c_c[0];
    double e = c_a[1] - c_c[1];
    double f = c_a[2] - c_c[2];
    double g = ray.direction[0];
    double h = ray.direction[1];
    double i = ray.direction[2];
    double j = c_a[0] - ray.origin[0];
    double k = c_a[1] - ray.origin[1];
    double l = c_a[2] - ray.origin[2];
    double M = a*(e*i-h*f) + b*(g*f-d*i) + c*(d*h-e*g);
    
    double beta = (j*(e*i-h*f) + k*(g*f-d*i) + l*(d*h-e*g)) / M;
    double gamma = (i*(a*k-j*b) + h*(j*c-a*l) + g*(b*l-k*c)) / M;
    double t_buff = -(f*(a*k-j*b) + e*(j*c-a*l) +d*(b*l-k*c)) / M;
    
    if(beta<0 || beta>1 || gamma<0 || gamma>1 || (beta+gamma)>1 || t_buff<min_t || t_buff>max_t) return false;
    
    t=t_buff;
    
    return true;
}
