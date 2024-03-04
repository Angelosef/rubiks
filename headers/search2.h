#ifndef SEARCH2_H
#define SEARCH2_H

#include<queue>
#include<stack>
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
        state* nodeState;
        node* parent;
        int cost;
        action* nodeAction;
    };

    class problem
    {
        public:
        virtual state* initial() = 0;
        virtual bool isGoal(state& theState) = 0;
        virtual state* result(state& theState, action& theAction) = 0;
        virtual int actionCost(state& theState, action& theAction) = 0;
        virtual std::stack<action> getActions(state& theState) = 0;
    };

    node* bestFirstSearch
    (problem* theProblem,
    std::function<bool(const general::node&, const general::node&)> order, bool& solved);
    std::queue<node*> expandNode(problem* theProblem, node& theNode);
    int searchForState(std::vector<node>& list, state& theState, bool& foundNode);

}

#endif
