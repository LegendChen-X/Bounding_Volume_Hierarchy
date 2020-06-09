#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
    I = -1;
    sqrD = std::numeric_limits<double>::infinity();;
    
    for(int i=0;i<points.rows();++i)
    {
        double x = points(i,0) - query[0];
        double y = points(i,1) - query[1];
        double z = points(i,2) - query[2];
        double buff = x * x + y * y + z * z;
        if(buff < sqrD)
        {
            sqrD = buff;
            I = i;
        }
    }
}
