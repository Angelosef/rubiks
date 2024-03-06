#include"testHeaders.h"

#include"../headers/search2.h"
#include"../headers/rubikOverload.h"
#include<iostream>

void search2Test()
{
    rubikProblem myProblem;
    bool solved;
    general::node solutionNode;

    solutionNode = general::bestFirstSearch(&myProblem, orderFunc, solved);

    if(!solved)
    {
        std::cout << "couldn't solve the problem\n";
    }

    else
    {
        std::cout << "problem solved\n";

        std::vector<general::node*> solution = general::getSolution(solutionNode);
        std::cout << "size " << solution.size() << std::endl;

        
        for(int i=solution.size()-2; i>=0; i += -1)
        {
            rubikState* statePtr = dynamic_cast<rubikState*> (&*solution[i]->nodeState);
            rubikAction* actionPtr = dynamic_cast<rubikAction*> (&*solution[i]->nodeAction);

            std::cout << "action " << (int)actionPtr->theAction << std::endl;
            std::cout << "cost " << solution[i]->cost << std::endl;

            //std::cout << "state\n";
            //statePtr->cube.print();
        }
        
    }

    std::cout << "program ended smoothly\n";
}
