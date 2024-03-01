#include"testHeaders.h"

#include"../headers/rubics.h"
#include<iostream>

/*
0 top -> white
1 bottom -> light blue
3 right -> letters
4 left -> dark blue
2 front -> blue
5 back -> really light blue
*/

void test2()
{
    rubicsCube myCube;

    std::cout << "starting state:\n";
    myCube.print();

    myCube.doAction(rubicsCube::actions::topCW);
    std::cout << "rotating top face CW\n";
    myCube.print();

    myCube.doAction(rubicsCube::actions::rightCW);
    std::cout << "rotating right face CW\n";
    myCube.print();

    myCube.doAction(rubicsCube::actions::frontCW);
    std::cout << "rotating front face CW\n";
    myCube.print();

    std::cout << "estimated cost to solve " << myCube.estimatedCostToSolve() << std::endl;
    
    std::cout << "performing an 100 move shuffle\n";
    myCube.shuffle(100);
    myCube.print();
    
    std::cout << "estimated cost to solve " << myCube.estimatedCostToSolve() << std::endl;

    std::cout << "ended smoothly\n";
}
