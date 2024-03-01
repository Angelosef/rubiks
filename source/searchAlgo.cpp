#include"../headers/searchAlgo.h"
#include"../headers/rubics.h"

#include<functional>
#include<queue>
#include <memory>
#include<iostream>

int searchForState(std::vector<node>& list, rubicsCube& cube, bool& foundNode)
{
    foundNode = false;

    int index = 0;
    while(!foundNode && index < list.size())
    {
        if(cube.isEqual(list[index].state))
        {
            foundNode = true;
            return index;
        }
        index++;
    }

    return -1;
}

std::queue<node> expand(const node& branching_node)
{
    std::queue<node> children;

    rubicsCube current_state = branching_node.state;

    for (int i = 0; i < current_state.numberOfActions; i++)
    {
        rubicsCube changed_state = current_state;
        rubicsCube::actions action = static_cast<rubicsCube::actions>(i);
        changed_state.doAction(action);

        node* child = new node;
        child->state = changed_state;
        child->parent = std::make_shared<node>(branching_node);
        child->action = action;
        child->cost = branching_node.cost + current_state.actionCost(action);

        children.push(*child);
    }

    return children;
}

struct CompareFunction {
    bool operator()(const node& lhs, const node& rhs) const {
        // Your custom comparison function based on 'f'
        // Return true if lhs should be ordered before rhs
        // Return false otherwise

        return ( lhs.cost + lhs.state.estimatedCostToSolve() )
        > ( rhs.cost + rhs.state.estimatedCostToSolve() );
    }
};

node alphaStar (rubicsCube startingState, bool& foundSolution)
{
    node* start = new node;
    start->state = startingState;
    start->parent = nullptr;

    std::priority_queue<node, std::vector<node>, CompareFunction> frontier;
    frontier.push(*start);

    std::vector<node> reached;

    while(!frontier.empty())
    {
        node explorationNode = frontier.top();
        frontier.pop();

        if(explorationNode.state.isGoal())
        {
            foundSolution = true;
            return explorationNode;
        }

        std::queue<node> children = expand(explorationNode);
        while(!children.empty())
        {
            node child = children.front();
            children.pop();
            rubicsCube newState = child.state;
            
            bool found;
            int index = searchForState(reached, newState, found);

            if (!found)
            {
                reached.push_back(child);
                frontier.push(child);
            }

            else if(child.cost < reached[index].cost)
            {
                reached.erase(reached.begin() + index);
                reached.push_back(child);
                frontier.push(child);
            }

        }
    }
    foundSolution = false;
    return *start;
}

std::vector<node> getSolution(node& goalNode)
{
    std::vector<node> solution;

    solution.push_back(goalNode);

    while(solution[solution.size()-1].parent != nullptr)
    {
        node lastNode = solution[solution.size()-1];
        solution.push_back(*lastNode.parent);
    }

    return solution;
}


