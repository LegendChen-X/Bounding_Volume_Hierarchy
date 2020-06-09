#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

/*
 https://en.cppreference.com/w/cpp/container/priority_queue
*/
typedef struct Compare()
{
    bool operator()
}compare;

bool point_AABBTree_squared_distance(
    const Eigen::RowVector3d & query,
    const std::shared_ptr<AABBTree> & root,
    const double min_sqrd,
    const double max_sqrd,
    double & sqrd,
    std::shared_ptr<Object> & descendant)
{
    sqrd = std::numeric_limits<double>::infinity();
    
    std::priority_queue<std::pair<std::shared_ptr<AABBTree>,double>,std::vector<std::pair<std::shared_ptr<AABBTree>,double>>,compare > queue;
    queue.emplace(root,point_box_squared_distance(query,root->box));
    return false;
    
}
