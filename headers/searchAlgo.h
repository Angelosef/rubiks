#ifndef SEARCH_ALGO_CPP
#define SEARCH_ALGO_CPP

#include"../headers/rubics.h"

#include<functional>
#include<queue>
#include<vector>
#include <memory>

struct node
{
    rubicsCube state;
    std::shared_ptr<node> parent;
    int cost;
    rubicsCube::actions action;
};

int searchForState(std::vector<node>& list, rubicsCube& cube, bool& foundNode);

std::queue<node> expand(const node& branching_node);

node alphaStar (rubicsCube startingState, bool& foundSolution);

std::vector<node> getSolution(node& goalNode);

#endif
