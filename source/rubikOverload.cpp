#include"../headers/rubikOverload.h"

#include<memory>

bool rubikState::isEqual(state& otherState)
{
    rubikState* otherRubikState = dynamic_cast<rubikState*>(&otherState);
    return this->cube.isEqual(otherRubikState->cube);
}

general::state* rubikProblem::initial()
{
    std::shared_ptr<rubikState> startState (new rubikState());

    //up for changes
    startState->cube.shuffle(2);

    return startState.get();
}

bool rubikProblem::isGoal(general::state& theState)
{
    if(rubikState* ptr = dynamic_cast<rubikState*> (&theState))
    {
        return ptr->cube.isGoal();
    }
    return false;
}

general::state* rubikProblem::result(general::state& theState, general::action& theAction)
{
    std::shared_ptr<rubikState> resultState (new rubikState());

    rubikState* statePtr = dynamic_cast<rubikState*> (&theState);
    rubikAction* actionPtr = dynamic_cast<rubikAction*> (&theAction);

    rubicsCube temp = statePtr->cube;
    temp.doAction(actionPtr->theAction);
    resultState->cube = temp;

    return resultState.get();
}

int rubikProblem::actionCost(general::state& theState, general::action& theAction)
{
    
    rubikState* statePtr = dynamic_cast<rubikState*> (&theState);
    rubikAction* actionPtr = dynamic_cast<rubikAction*> (&theAction);

    return statePtr->cube.actionCost(actionPtr->theAction);
}

std::stack<general::action> rubikProblem::getActions(general::state& theState)
{
    std::stack<general::action> generatedActions;
    rubikState* statePtr = dynamic_cast<rubikState*> (&theState);

    general::action* act;

    for(int i=0; i<statePtr->cube.numberOfActions; i++)
    {
        rubikAction newAction;
        newAction.theAction = (rubicsCube::actions)i;

        generatedActions.push(newAction);
    }

    return generatedActions;
}

bool orderFunc(const general::node& node1, const general::node& node2)
{
    rubikState* statePtr1 = dynamic_cast<rubikState*> (node1.nodeState);
    rubikState* statePtr2 = dynamic_cast<rubikState*> (node2.nodeState);

    int value1 = node1.cost + statePtr1->cube.estimatedCostToSolve();
    int value2 = node2.cost + statePtr2->cube.estimatedCostToSolve();

    return value1 > value2;
}


