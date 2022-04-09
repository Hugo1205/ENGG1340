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

games initgame(){  //initgame to initialize every games board
    games game;
    for(int i=0;i<Maxheight;i++){
        for(int j=0;j<MaxWidth;j++){
            game.board[i][j] = 0;
        }
    }
    game.score = 0;
    return game;
}
