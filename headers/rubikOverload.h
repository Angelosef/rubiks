#ifndef RUBIK_OVERLOAD_H
#define RUBIK_OVERLOAD_H

#include"search2.h"
#include"rubics.h"

class rubikState : public general::state
{
    public:
    bool isEqual(state& otherState) override;

    public:
    rubicsCube cube;
};

class rubikAction : public general::action
{
    public:
    void doNothing() override;
    rubicsCube::actions theAction;
};

class rubikProblem : public general::problem
{
    public:
    std::shared_ptr<general::state> initial() override;
    bool isGoal(general::state& theState) override;
    std::shared_ptr<general::state> result(general::state& theState, general::action& theAction) override;
    int actionCost(general::state& theState, general::action& theAction) override;
    std::stack<std::shared_ptr<general::action>> getActions(general::state& theState) override;

    private:
    rubicsCube cube;
};

bool orderFunc(const general::node&, const general::node&);

#endif
