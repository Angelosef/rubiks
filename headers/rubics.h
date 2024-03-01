#ifndef RUBICS_H
#define RUBICS_H

class rubicsCube
{
    public:
    //creates a solved cube
    rubicsCube();
    void setState(int*** cubeState);

    enum actions
    {
        topCW = 0,
        bottomCW,
        frontCW,
        rightCW,
        leftCW,
        backCW,
        numberOfActions
    };

    enum faces
    {
        top = 0,
        bottom,
        front,
        right,
        left,
        back,
        numberOfFaces
    };

    enum colorCode
    {
        topColor = 0,
        bottomColor,
        frontColor,
        rightColor,
        leftColor,
        backColor,
        numberOfColors
    };

    void doAction(actions performedAction);

    //returns 1
    int actionCost(actions performedAction);
    int estimatedCostToSolve() const;

    void shuffle(int numberOfRotations);
    bool isGoal();
    //resets the cube to the solved state
    void reset();
    void print();
    bool isEqual(rubicsCube& otherCube);
    
    private:
    static const int sideLength = 3;
    int cubeState[numberOfFaces][sideLength][sideLength];

    void shift(int** array1, int** array2, int** array3, int** array4);
    //copy from array1 to array2
    void copyArray(int** array1, int** array2);
    void copyArray2(int** array1, int* array2);
    void copyArray3(int* array1, int** array2);
    int** horizSide(int face, int row);
    int** vertSide(int face, int column);
    
    void shiftFaceSquaresCW(int face);
    void reverseSide(int** array);
    
    void topFaceCW();
    void bottomFaceCW();
    void leftFaceCW();
    void rightFaceCW();
    void frontFaceCW();
    void backFaceCW();

    void printFace(int face);
    
};

#endif
