#include"testHeaders.h"

#include"../headers/rubics.h"
#include"../headers/searchAlgo.h"
#include<iostream>

/*
0 top -> white
1 bottom -> light blue
3 right -> letters
4 left -> dark blue
2 front -> blue
5 back -> really light blue
*/

void solve_test1()
{
    rubicsCube myCube;

    myCube.doAction(rubicsCube::actions::frontCW);
    myCube.doAction(rubicsCube::actions::topCW);
    myCube.doAction(rubicsCube::actions::rightCW);
    //myCube.doAction(rubicsCube::actions::bottomCW);
    //myCube.doAction(rubicsCube::actions::frontCW); 

    //myCube.shuffle(3); 

    std::cout << "unsolved cube\n";
    myCube.print();

    bool solved;
    node solution = alphaStar(myCube, solved);

    if(solved)
    {
        std::cout << "solved cube\n";
        std::vector<node> solutionPath = getSolution(solution);
        std::cout << "got solution\n";

        for(int i=solutionPath.size()-2; i>=0; i += -1)
        {
            std::cout << solutionPath[i].action << std::endl;
            myCube.doAction(solutionPath[i].action);
            //myCube.print();
        }
        std::cout << std::endl;
    }

    else
    {
        std::cout << "could not solve the cube\n";
    }

    std::cout << "ended smoothly\n";
}
