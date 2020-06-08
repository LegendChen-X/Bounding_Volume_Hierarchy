#include "insert_triangle_into_box.h"

double maximum(double a,double b,double c,double d)
{
    double buff = a > b ? a : b;
    double buff_s = buff > c ? buff : c;
    return buff_s > d ? buff : d;
}

double minimum(double a,double b,double c,double d)
{
    double buff = a < b ? a : b;
    double buff_s = buff < c ? buff : c;
    return buff_s < d ? buff : d;
}

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
    for(int i=0;i<3;++i)
    {
        B.min_corner[i] = minimum(a[i],b[i],c[i],B.min_corner[i]);
        B.max_corner[i] = maximum(a[i],b[i],c[i],B.max_corner[i]);
    }
}
