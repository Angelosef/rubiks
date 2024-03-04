#include"../headers/search2.h"

int general::searchForState
(std::vector<general::node>& list, general::state& theState, bool& foundNode)
{
    foundNode = false;

    int index = 0;
    while(!foundNode && index < list.size())
    {
        if(theState.isEqual(*list[index].nodeState))
        {
            foundNode = true;
            return index;
        }
        index++;
    }

    return -1;
}

std::queue<general::node*> general::expandNode
(general::problem* theProblem, general::node& theNode)
{
    std::queue<node*> children;

    general::state* current_state = theNode.nodeState;
    
    std::stack<general::action> availableActions = theProblem->getActions(*current_state);

    while(!availableActions.empty())
    {
        general::action* tryAction = &availableActions.top();
        availableActions.pop();

        general::state* newState = theProblem->result(*current_state, *tryAction);
        int cost = theNode.cost + theProblem->actionCost(*current_state, *tryAction);

        std::shared_ptr<general::node> child (new general::node());

        child->cost = cost;
        child->nodeAction = tryAction;
        child->nodeState = newState;
        child->parent = &theNode;

        children.push(child.get());
    }

    return children;
}

general::node* general::bestFirstSearch
(general::problem* theProblem,
std::function<bool(const general::node&, const general::node&)> order, bool& solved)
{
    general::state* startingState;
    startingState = theProblem->initial();

    std::shared_ptr<general::node> start = std::make_shared<general::node>();
    start->parent = nullptr;
    start->cost = 0;
    start->nodeState = startingState;
     
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
            return &explorationNode;
        }

        std::queue<general::node*> children = expandNode(theProblem, explorationNode);
        while(!children.empty())
        {
            general::node child = *children.front();
            children.pop();
            general::state* newState = child.nodeState;

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
    return start.get();
}
    


