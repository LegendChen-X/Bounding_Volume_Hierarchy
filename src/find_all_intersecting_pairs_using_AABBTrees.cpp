#include "find_all_intersecting_pairs_using_AABBTrees.h"
#include "box_box_intersect.h"
// Hint: use a list as a queue
#include <list>

void find_all_intersecting_pairs_using_AABBTrees(
  const std::shared_ptr<AABBTree> & rootA,
  const std::shared_ptr<AABBTree> & rootB,
  std::vector<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object> > > &
    leaf_pairs)
{
    std::list<std::pair<std::shared_ptr<Object>,std::shared_ptr<Object>>> queue;
    if(box_box_intersect(rootA->box,rootB->box)) queue.emplace_back(rootA,rootB);
    
    while(!queue.empty())
    {
        std::shared_ptr<Object> ObjectA = queue.front().first;
        std::shared_ptr<Object> ObjectB = queue.front().second;
        queue.pop_front();
        
        std::shared_ptr<AABBTree> nodeA = std::dynamic_pointer_cast<AABBTree>(ObjectA);
        std::shared_ptr<AABBTree> nodeB = std::dynamic_pointer_cast<AABBTree>(ObjectB);
        
        if(!nodeA && !nodeB)
        {
            leaf_pairs.emplace_back(ObjectA,ObjectB);
        }
        else if(!nodeA)
        {
            if(box_box_intersect(ObjectA->box,nodeB->left->box))
                queue.emplace_back(ObjectA,nodeB->left);
            if(box_box_intersect(ObjectA->box,nodeB->right->box))
                queue.emplace_back(ObjectA,nodeB->right);
        }
        else if(!nodeB)
        {
            if(box_box_intersect(nodeA->left->box,ObjectB->box))
                queue.emplace_back(nodeA->left,ObjectB);
            if(box_box_intersect(nodeA->right->box,ObjectB->box))
                queue.emplace_back(nodeA->right,ObjectB);
        }
        else
        {
            if(box_box_intersect(nodeA->left->box,nodeB->left->box))
                queue.emplace_back(nodeA->left,nodeB->left);
            if(box_box_intersect(nodeA->left->box,nodeB->right->box))
                queue.emplace_back(nodeA->left,nodeB->right);
            if(box_box_intersect(nodeA->right->box,nodeB->left->box))
            queue.emplace_back(nodeA->right,nodeB->left);
            if(box_box_intersect(nodeA->right->box,nodeB->right->box))
            queue.emplace_back(nodeA->right,nodeB->right);
        }
    }
}
