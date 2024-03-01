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

void test1()
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
    
    std::cout << "ended smoothly\n";
}
