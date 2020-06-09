#include "point_AABBTree_squared_distance.h"
#include <queue> // std::priority_queue

/*
 https://en.cppreference.com/w/cpp/container/priority_queue
*/
typedef struct Compare
{
    bool operator()(std::pair<std::shared_ptr<AABBTree>,double> tree_1, std::pair<std::shared_ptr<AABBTree>,double> tree_2)
    {
        return tree_1.second > tree_2.second;
    }
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
    
    std::priority_queue<std::pair<std::shared_ptr<AABBTree>,double>,std::vector<std::pair<std::shared_ptr<AABBTree>,double>>,compare> queue;
    queue.emplace(root,point_box_squared_distance(query,root->box));
    
    while(!queue.empty())
    {
        double node_distance = queue.top().second;
        std::shared_ptr<AABBTree> node = queue.top().first;
        queue.pop();
        
        if(node_distance < sqrd)
        {
            std::shared_ptr<AABBTree> tree = std::dynamic_pointer_cast<AABBTree>(node);
            if(tree && tree->left) queue.emplace(std::static_pointer_cast<AABBTree>(tree->left), point_box_squared_distance(query,tree->left->box));
            if(tree && tree->right) queue.emplace(std::static_pointer_cast<AABBTree>(tree->right), point_box_squared_distance(query, tree->right->box));
            if(!tree->left && !tree->right)
            {
                double this_sqrd;
                std::shared_ptr<Object> this_descendant = NULL;
                if(node->point_squared_distance(query,min_sqrd,max_sqrd,this_sqrd,this_descendant) && this_sqrd < sqrd)
                {
                    sqrd = this_sqrd;
                    descendant = node;
                    return true;
                }
            }
        }
    }
    
    return false;
}
