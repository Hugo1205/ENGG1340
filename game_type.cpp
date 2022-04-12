#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include "io.h"
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

shape shapeList(){
  shape shapeArray[8];  //this array will store all the shapes, first shape T, and the rotations for T
                        // then it will store shape L and all rotations for L
  shapeArray[0] = {{{'*','*','*'},{'0','*','0'},{'0','*','0'}}}; //main T shape
  shapeArray[1] = {{{'0','0','*'},{'*','*','*'},{'0','0','*'}}}; //T rotated 90 degrees
  shapeArray[2] = {{{'0','*','0'},{'0','*','0'},{'*','*','*'}}}; //T rotated 180 degrees
  shapeArray[3] = {{{'*','0','0'},{'*','*','*'},{'*','0','0'}}}; //T rotated 270 degrees

  shapeArray[4] = {{{'*','0','0'},{'*','0','0'},{'*','*','*'}}}; //main L shape
  shapeArray[5] = {{{'*','*','*'},{'*','0','0'},{'*','0','0'}}}; //L rotated 90 degrees
  shapeArray[6] = {{{'*','*','*'},{'0','0','*'},{'0','0','*'}}}; //L rotated 180 degrees
  shapeArray[7] = {{{'0','0','*'},{'0','0','*'},{'*','*','*'}}}; //L rotated 270 degrees

  return shapeArray;
}
void game_main(games &game){
    keyboard kb;
    kb.off();


    kb.off();
}