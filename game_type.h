#include <iostream>
#include <string>
#define Maxheight 17
#define MaxWidth 18
#define shapesize 3

struct games{
    int board[Maxheight][MaxWidth];
    int score;
};

class shape{
    char (*board)[shapesize]; // a pointer to a 2D array that represent the board
    void setroation(int number); //rotation function of the board
    void printboard();//print the board
    shape(char p[][shapesize]); //a constructor for the shape
    ~shape();//deconstructor for the shape
};

games initgame();

shape shapeList();

void game_main();