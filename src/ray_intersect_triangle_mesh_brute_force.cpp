#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
    hit_t = std::numeric_limits<double>::infinity();
    int flag = 0;
    
    for(int i=0;i<F.rows();++i)
    {
        int A = F(i,0);
        int B = F(i,1);
        int C = F(i,2);
        
        double t_buff;
        
        if(ray_intersect_triangle(ray,V.row(A),V.row(B),V.row(C),min_t,max_t,t_buff))
        {
            if(t_buff<hit_t)
            {
                flag = 1;
                hit_t = t_buff;
                hit_f = i;
            }
        }
    }
    
    if(flag) return true;
    
    return false;
}
