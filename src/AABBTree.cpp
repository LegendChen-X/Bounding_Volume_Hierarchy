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
        insert_box_into_box(objects[0]->box, this->box);
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
        for(int i=0;i<size;++i)
            insert_box_into_box(objects[i]->box,this->box);
        
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
        
        double mid = (this->box.min_corner(longest)+this->box.max_corner(longest)) / 2.0;
        
        std::vector<std::shared_ptr<Object>> lefts;
        std::vector<std::shared_ptr<Object>> rights;
        
        for(int i=0;i<size;++i)
        {
            double center = (objects[i]->box.max_corner[longest]+objects[i]->box.min_corner[longest]) / 2.0;
            if(center < mid) lefts.push_back(objects[i]);
            else rights.push_back(objects[i]);
        }
        
        if(lefts.empty() && rights.size() > 1)
        {
            this->left = rights.back();
            rights.pop_back();
        }
        else if(lefts.size()==1) this->left = lefts[0];
        else if(lefts.size() > 1) this->left = std::make_shared<AABBTree>(lefts,a_depth+1);
        
        if(rights.empty() && lefts.size() > 1)
        {
            this->right = lefts.back();
            lefts.pop_back();
        }
        else if(rights.size()==1) this->right = rights[0];
        else if(rights.size() > 1) this->right = std::make_shared<AABBTree>(rights,a_depth+1);
    }
}
