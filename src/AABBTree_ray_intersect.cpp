#include "AABBTree.h"

// See AABBTree.h for API
bool AABBTree::ray_intersect(
  const Ray& ray,
  const double min_t,
  const double max_t,
  double & t,
  std::shared_ptr<Object> & descendant) const 
{
    t = 0;
    if(!ray_intersect_box(ray, this->box, min_t, max_t)) return false;
    
    double left_t;
    double right_t;
    
    std::shared_ptr<Object> left_descendant;
    std::shared_ptr<Object> right_descendant;
    
    bool left_hit = this->left && this->left->ray_intersect(ray, min_t, max_t, left_t, left_descendant);
    bool right_hit = this->right && this->right->ray_intersect(ray, min_t, max_t, right_t, right_descendant);
    
    if(left_hit && !left_descendant) left_descendant = this->left;
    
    if(right_hit && !right_descendant) right_descendant = this->right;
    
    if(left_hit && right_hit)
    {
        if(left_t < right_t)
        {
            t = left_t;
            descendant = left_descendant;
        }
        else
        {
            t = right_t;
            descendant = right_descendant;
        }
    }
    else if(left_hit && !right_hit)
    {
        t = left_t;
        descendant = left_descendant;
    }
    else if(!left_hit && right_hit)
    {
        t = right_t;
        descendant = right_descendant;
    }
    else return false;
    
    return true;
}

