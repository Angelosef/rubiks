#include"../headers/rubics.h"
#include<iostream>
#include<cstdlib>
#include<ctime>

rubicsCube::rubicsCube()
{
    this->reset();
}

void rubicsCube::reset()
{
    for (int face = 0; face < numberOfFaces; ++face)
    {
        for (int row = 0; row < sideLength; ++row)
        {
            for (int col = 0; col < sideLength; ++col)
            {
                cubeState[face][row][col] = face;
            }
        }
    }
}

void rubicsCube::setState(int*** cubeState)
{
    for (int face = 0; face < numberOfFaces; ++face)
    {
        for (int row = 0; row < sideLength; ++row)
        {
            for (int col = 0; col < sideLength; ++col)
            {
                this->cubeState[face][row][col] = cubeState[face][row][col];
            }
        }
    }
}

void rubicsCube::copyArray(int** array1, int** array2)
{
    for(int i=0;i<this->sideLength;i++)
    {
        *(array2[i]) = *(array1[i]);
    }
}

void rubicsCube::copyArray2(int** array1, int* array2)
{
    for(int i=0;i<this->sideLength;i++)
    {
        array2[i] = *(array1[i]);
    }
}

void rubicsCube::copyArray3(int* array1, int** array2)
{
    for(int i=0;i<this->sideLength;i++)
    {
        *(array2[i]) = array1[i];
    }
}

void rubicsCube::shift(int** array1, int** array2, int** array3, int** array4)
{
    int temp1[3];
    int temp2[3];
    int temp3[3];
    int temp4[3];

    this->copyArray2(array1, temp1);
    this->copyArray2(array2, temp2);
    this->copyArray2(array3, temp3);
    this->copyArray2(array4, temp4);
    
    this->copyArray3(temp1, array2);
    this->copyArray3(temp2, array3);
    this->copyArray3(temp3, array4);
    this->copyArray3(temp4, array1);
}

int** rubicsCube::horizSide(int face, int row)
{
    int** side = new int*[3];

    side[0] = &(this->cubeState[face][row][0]);
    side[1] = &(this->cubeState[face][row][1]);
    side[2] = &(this->cubeState[face][row][2]);

    return side;
}

int** rubicsCube::vertSide(int face, int column)
{
    int** side = new int*[3];

    side[0] = &(this->cubeState[face][0][column]);
    side[1] = &(this->cubeState[face][1][column]);
    side[2] = &(this->cubeState[face][2][column]);

    return side;
}

void rubicsCube::shiftFaceSquaresCW(int face)
{
    int** side1 = this->horizSide(face, 0);
    int** side2 = this->vertSide(face, 2);
    int** side3 = this->horizSide(face, 2);
    this->reverseSide(side3);
    int** side4 = this->vertSide(face, 0);
    this->reverseSide(side4);

    this->shift(side1, side2, side3, side4);

    delete[] side1;
    delete[] side2;
    delete[] side3;
    delete[] side4;
}

void rubicsCube::reverseSide(int** array)
{
    int* temp[3];

    for(int i=0;i<this->sideLength;i++)
    {
        temp[i] = array[i];
    }

    array[0] = temp[2];
    array[2] = temp[0];
}

void rubicsCube::topFaceCW()
{
    this->shiftFaceSquaresCW(top);

    int** side1 = this->horizSide(back, 0);
    int** side2 = this->horizSide(right, 0);
    int** side3 = this->horizSide(front, 0);
    int** side4 = this->horizSide(left, 0);

    this->shift(side1, side2, side3, side4);

    delete[] side1;
    delete[] side2;
    delete[] side3;
    delete[] side4;
}

void rubicsCube::bottomFaceCW()
{
    this->shiftFaceSquaresCW(bottom);

    int** side1 = this->horizSide(back, 2);
    int** side2 = this->horizSide(left, 2);
    int** side3 = this->horizSide(front, 2);
    int** side4 = this->horizSide(right, 2);

    this->shift(side1, side2, side3, side4);

    delete[] side1;
    delete[] side2;
    delete[] side3;
    delete[] side4;
}

void rubicsCube::leftFaceCW()
{
    this->shiftFaceSquaresCW(left);

    int** side1 = this->vertSide(top, 0);
    int** side2 = this->vertSide(front, 0);
    int** side3 = this->vertSide(bottom, 2);
    this->reverseSide(side3);
    int** side4 = this->vertSide(back, 2);
    this->reverseSide(side4);

    this->shift(side1, side2, side3, side4);

    delete[] side1;
    delete[] side2;
    delete[] side3;
    delete[] side4;
}

void rubicsCube::rightFaceCW()
{
    this->shiftFaceSquaresCW(right);

    int** side1 = this->vertSide(top, 2);
    this->reverseSide(side1);
    int** side2 = this->vertSide(back, 0);
    int** side3 = this->vertSide(bottom, 0);
    int** side4 = this->vertSide(front, 2);
    this->reverseSide(side4);

    this->shift(side1, side2, side3, side4);

    delete[] side1;
    delete[] side2;
    delete[] side3;
    delete[] side4;
}

void rubicsCube::frontFaceCW()
{
    this->shiftFaceSquaresCW(front);

    int** side1 = this->horizSide(top, 2);
    int** side2 = this->vertSide(right, 0);
    int** side3 = this->horizSide(bottom, 2);
    int** side4 = this->vertSide(left, 2);
    this->reverseSide(side4);

    this->shift(side1, side2, side3, side4);

    delete[] side1;
    delete[] side2;
    delete[] side3;
    delete[] side4;
}

void rubicsCube::backFaceCW()
{
    this->shiftFaceSquaresCW(back);

    int** side1 = this->horizSide(top, 0);
    this->reverseSide(side1);
    int** side2 = this->vertSide(left, 0);
    int** side3 = this->horizSide(bottom, 0);
    this->reverseSide(side3);
    int** side4 = this->vertSide(right, 2);
    this->reverseSide(side4);

    this->shift(side1, side2, side3, side4);

    delete[] side1;
    delete[] side2;
    delete[] side3;
    delete[] side4;
}

void rubicsCube::doAction(rubicsCube::actions performedAction)
{
    if(performedAction == this->actions::backCW)
    {
        this->backFaceCW();
    }

    else if(performedAction == this->actions::bottomCW)
    {
        this->bottomFaceCW();
    }

    
    else if(performedAction == this->actions::frontCW)
    {
        this->frontFaceCW();
    }

    
    else if(performedAction == this->actions::leftCW)
    {
        this->leftFaceCW();
    }

    
    else if(performedAction == this->actions::rightCW)
    {
        this->rightFaceCW();
    }

    
    else if(performedAction == this->actions::topCW)
    {
        this->topFaceCW();
    }
}

int rubicsCube::actionCost(actions performedAction)
{
    return 1;
}

int rubicsCube::estimatedCostToSolve() const
{
    int counter = 0;

    for(int face=0;face<this->numberOfFaces;face++)
    {
        for(int row = 0;row<this->sideLength;row++)
        {
            for(int column=0;column<this->sideLength;column++)
            {
                if(this->cubeState[face][row][column] != face)
                {
                    counter++;
                }
            }
        }
    }

    return counter;
}

void rubicsCube::shuffle(int numberOfRotations)
{
    srand(static_cast<unsigned int>(time(nullptr)));

    for(int i=0;i<numberOfRotations;i++)
    {
        int randomMove = rand() % this->numberOfActions;
        this->doAction((actions)randomMove);
    }
}

bool rubicsCube::isGoal()
{
    return (this->estimatedCostToSolve() == 0);
}

void rubicsCube::printFace(int face)
{
    for(int row=0;row<this->sideLength;row++)
    {
        for(int column=0;column<this->sideLength;column++)
        {
            std::cout << cubeState[face][row][column] << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void rubicsCube::print()
{
    std::cout << "Cube State:" << std::endl << std::endl;

    std::cout << "top face (" << this->faces::top << ")" << std::endl;
    this->printFace(faces::top);

    std::cout << "bottom face (" << this->faces::bottom << ")" << std::endl;
    this->printFace(faces::bottom);

    std::cout << "right face (" << this->faces::right << ")" << std::endl;
    this->printFace(faces::right);
    
    std::cout << "left face (" << this->faces::left << ")" << std::endl;
    this->printFace(faces::left);
    
    std::cout << "front face (" << this->faces::front << ")" << std::endl;
    this->printFace(faces::front);
    
    std::cout << "back face (" << this->faces::back << ")" << std::endl;
    this->printFace(faces::back);

}

bool rubicsCube::isEqual(rubicsCube& otherCube)
{
    bool checkequality = true;

    for (int face = 0; face < numberOfFaces; ++face)
    {
        for (int row = 0; row < sideLength; ++row)
        {
            for (int col = 0; col < sideLength; ++col)
            {
                if(this->cubeState[face][row][col] != otherCube.cubeState[face][row][col])
                {
                    checkequality = false;
                }
            }
        }
    }

    return checkequality;

}

