#include"../headers/rubikOverload.h"

#include<memory>
#include<iostream>

void rubikAction::doNothing()
{

}

bool rubikState::isEqual(state& otherState)
{
    if(rubikState* otherRubikState = dynamic_cast<rubikState*>(&otherState))
    {
        return this->cube.isEqual(otherRubikState->cube);    
    }
    return false;
    
}

std::shared_ptr<general::state> rubikProblem::initial()
{
    std::shared_ptr<rubikState> startState (new rubikState());

    startState->cube.doAction(rubicsCube::actions::frontCW);
    startState->cube.doAction(rubicsCube::actions::topCW);
    startState->cube.doAction(rubicsCube::actions::rightCW);
    //startState->cube.doAction(rubicsCube::actions::bottomCW);

    return startState;
}

bool rubikProblem::isGoal(general::state& theState)
{
    
    if(rubikState* ptr = dynamic_cast<rubikState*> (&theState))
    {
    
        return ptr->cube.isGoal();
    }
    return false;
}

std::shared_ptr<general::state> rubikProblem::result
(general::state& theState, general::action& theAction)
{
    std::shared_ptr<rubikState> resultState (new rubikState());

    rubikState* statePtr = dynamic_cast<rubikState*> (&theState);
    rubikAction* actionPtr = dynamic_cast<rubikAction*> (&theAction);

    rubicsCube temp = statePtr->cube;
    temp.doAction(actionPtr->theAction);
    resultState->cube = temp;

    return resultState;
}

int rubikProblem::actionCost(general::state& theState, general::action& theAction)
{
    
    rubikState* statePtr = dynamic_cast<rubikState*> (&theState);
    rubikAction* actionPtr = dynamic_cast<rubikAction*> (&theAction);

    return statePtr->cube.actionCost(actionPtr->theAction);
}

std::stack<std::shared_ptr<general::action>> rubikProblem::getActions(general::state& theState)
{
    std::stack<std::shared_ptr<general::action>> generatedActions;
    rubikState* statePtr = dynamic_cast<rubikState*> (&theState);

    for(int i=0; i<statePtr->cube.numberOfActions; i++)
    {
        std::shared_ptr<rubikAction> action (new rubikAction);
        action->theAction = (rubicsCube::actions)i;

        generatedActions.push(action);
    }

    return generatedActions;
}

bool orderFunc(const general::node& node1, const general::node& node2)
{
    rubikState* statePtr1 = dynamic_cast<rubikState*> (node1.nodeState.get());
    rubikState* statePtr2 = dynamic_cast<rubikState*> (node2.nodeState.get());

    int value1 = node1.cost + statePtr1->cube.estimatedCostToSolve();
    int value2 = node2.cost + statePtr2->cube.estimatedCostToSolve();

    return value1 > value2;
}


