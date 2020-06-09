#include "point_box_squared_distance.h"

double maximum(double a,double b,double c)
{
    double buff = a > b ? a : b;
    return buff > c ? buff : c;
}

/*
 https://stackoverflow.com/questions/5254838/calculating-distance-between-a-point-and-a-rectangular-box-nearest-point
*/
double point_box_squared_distance(
  const Eigen::RowVector3d & query,
  const BoundingBox & box)
{
    double x = maximum(box.min_corner[0] - query[0],query[0] - box.max_corner[0],0.0);
    double y = maximum(box.min_corner[1] - query[1],query[1] - box.max_corner[1],0.0);
    double z = maximum(box.min_corner[2] - query[2],query[2] - box.max_corner[2],0.0);
    return x * x + y * y + z * z;
}
