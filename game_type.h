#include <iostream>
#include <string>
#define Maxheight 17
#define MaxWidth 18

struct games{
    int board[Maxheight][MaxWidth];
    int score;
};

games initgame();