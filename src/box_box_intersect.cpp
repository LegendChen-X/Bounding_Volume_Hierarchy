#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
    bool a = A.min_corner[0] < B.max_corner[0] && B.min_corner[0] < A.max_corner[0];
    bool b = A.min_corner[1] < B.max_corner[1] && B.min_corner[1] < A.max_corner[1];
    bool c = A.min_corner[2] < B.max_corner[2] && B.min_corner[2] < A.max_corner[2];
    
    return a & b & c;
}

