#include "AABBTree.h"
#include "insert_box_into_box.h"
#include <math.h>

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
    int size = objects.size();
    
    if(size==0)
    {
        this->left = NULL;
        this->right = NULL;
    }
    else if(size==1)
    {
        this->left = objects[0];
        this->right = NULL;
    }
    else if(size==2)
    {
        this->left = objects[0];
        this->right = objects[1];
        insert_box_into_box(objects[0]->box, this->box);
        insert_box_into_box(objects[1]->box, this->box);
    }
    else
    {
        double distance_array[3][2];
        
        for(int i=0;i<3;++i)
        {
            double min_buff = std::numeric_limits<double>::infinity();
            double max_buff = -std::numeric_limits<double>::infinity();
            
            for(int j=0;j<size;++j)
            {
                double min = objects[j]->box.min_corner[i];
                double max = objects[j]->box.max_corner[i];
                
                if(min_buff > min) min_buff = min;
                if(max_buff<max) max_buff = max;
            }
            
            distance_array[i][0] = min_buff;
            distance_array[i][1] = max_buff;
        }
        
        int longest = -1;
        double max = -1;
        
        for(int i=0;i<3;++i)
        {
            double max_buff = fabs(distance_array[i][0] - distance_array[i][1]);
            if(max < max_buff)
            {
                max = max_buff;
                longest = i;
            }
        }
        
        double mid = (distance_array[longest][0] + distance_array[longest][1]) / 2.0;
        
        std::vector<std::shared_ptr<Object>> lefts;
        std::vector<std::shared_ptr<Object>> rights;
        
        for(int i=0;i<size;++i)
        {
            double position = (objects[i]->box.max_corner[longest]+objects[i]->box.min_corner[longest]) / 2.0;
            if(position<mid)
                lefts.push_back(objects[i]);
            else
                rights.push_back(objects[i]);
        }
        
        if(lefts.size() == 0 && rights.size() > 1)
        {
            lefts.push_back(rights.back());
            rights.pop_back();
        }
        else if(lefts.size() > 1 && rights.size() == 0)
        {
            rights.push_back(lefts.back());
            lefts.pop_back();
        }
        
        std::shared_ptr<AABBTree> left_child = std::make_shared<AABBTree>(lefts, a_depth+1);
        std::shared_ptr<AABBTree> right_child = std::make_shared<AABBTree>(rights, a_depth+1);
        
        this->left = std::dynamic_pointer_cast<Object>(left_child);
        this->right = std::dynamic_pointer_cast<Object>(right_child);
        
        insert_box_into_box(this->left->box, this->box);
        insert_box_into_box(this->right->box, this->box);
    }
    
}
