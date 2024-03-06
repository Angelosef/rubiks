#ifndef SEARCH2_H
#define SEARCH2_H

#include<queue>
#include<stack>
#include<vector>
#include<functional>
#include<memory>

namespace general
{
    class state
    {
        public:
        virtual bool isEqual(state& otherState) = 0;
    };

    class action
    {
        public:
        virtual void doNothing() = 0;
    };

    struct node
    {
        std::shared_ptr<state> nodeState;
        std::shared_ptr<node> parent;
        int cost;
        std::shared_ptr<action> nodeAction;
    };

    class problem
    {
        public:
        virtual std::shared_ptr<state> initial() = 0;
        virtual bool isGoal(state& theState) = 0;
        virtual std::shared_ptr<state> result(state& theState, action& theAction) = 0;
        virtual int actionCost(state& theState, action& theAction) = 0;
        virtual std::stack<std::shared_ptr<action>> getActions(state& theState) = 0;
    };

    node bestFirstSearch
    (problem* theProblem,
    std::function<bool(const general::node&, const general::node&)> order, bool& solved);
    std::queue<std::shared_ptr<node>> expandNode(problem* theProblem, node& theNode);
    int searchForState(std::vector<node>& list, state& theState, bool& foundNode);
    std::vector<node*> getSolution(node& goalNode);

}

#endif
