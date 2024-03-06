#include"../headers/search2.h"

#include<iostream>

int general::searchForState
(std::vector<general::node>& list, general::state& theState, bool& foundNode)
{
    foundNode = false;

    int index = 0;
    while(!foundNode && index < list.size())
    {
        std::shared_ptr<general::state> dummy = list[index].nodeState;

        if(theState.isEqual(*(list[index].nodeState)))
        {
            foundNode = true;
            return index;
        }
        index++;
    }

    return -1;
}

std::queue<std::shared_ptr<general::node>> general::expandNode
(general::problem* theProblem, general::node& theNode)
{
    std::queue<std::shared_ptr<general::node>> children;

    std::shared_ptr<general::state> current_state = theNode.nodeState;
    
    std::stack<std::shared_ptr<general::action>> availableActions;
    availableActions = theProblem->getActions(*current_state);

    while(!availableActions.empty())
    {
        std::shared_ptr<general::action> tryAction = availableActions.top();
        availableActions.pop();

        std::shared_ptr<general::state> newState;
        newState = theProblem->result(*current_state, *tryAction);

        int cost = theNode.cost + theProblem->actionCost(*current_state, *tryAction);

        std::shared_ptr<general::node> child (new general::node());
        
        child->cost = cost;
        child->nodeAction = std::move(tryAction);
        child->nodeState = std::move(newState);
        child->parent = std::make_shared<node>(theNode);

        children.push(child);
    }

    return children;
}

general::node general::bestFirstSearch
(general::problem* theProblem,
std::function<bool(const general::node&, const general::node&)> order, bool& solved)
{
    std::cout << "running bfs\n";
    std::shared_ptr<general::state> startingState;
    startingState = theProblem->initial();

    std::shared_ptr<general::node> start = std::make_shared<general::node>();
    start->parent = nullptr;
    start->cost = 0;
    start->nodeState = std::move(startingState);

    std::priority_queue<general::node, std::vector<general::node>,
    decltype(order)> frontier(order);
    
    frontier.push(*start.get());
    
    std::vector<general::node> reached;

    while(!frontier.empty())
    {
        
        general::node explorationNode = frontier.top();

        frontier.pop();

        if(theProblem->isGoal(*explorationNode.nodeState))
        {
            solved = true;
            return explorationNode;
        }

        std::queue<std::shared_ptr<general::node>> children;
        children = expandNode(theProblem, explorationNode);

        while(!children.empty())
        {
            general::node child = *children.front().get();
            children.pop();
            std::shared_ptr<general::state> newState = child.nodeState;

            bool found;
            int index = searchForState(reached, *newState, found);

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
    solved = false;
    return *start.get();
}

std::vector<general::node*> general::getSolution(general::node& goalNode)
{
    std::vector<node*> solution;

    solution.push_back(&goalNode);

    while(solution[solution.size()-1]->parent != nullptr)
    {
        node* lastNode = solution[solution.size()-1];
        solution.push_back(lastNode->parent.get());
    }

    return solution;
}




