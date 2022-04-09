#include <iostream>
#include <string>
#define Maxheight 17
#define MaxWidth 18
#define shapesize 3

struct games{
    int board[Maxheight][MaxWidth];
    int score;
};
struct shape{
    int board[shapesize][shapesize];
};

games initgame();