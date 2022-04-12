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

class shape{
    public:
        char (*board)[shapesize];
        void setroation(int number){
            int target = (number-i)%4;//find how many rotation need to be made
            char (*p)[shapesize] = new char [shapesize][shapesize]; //create a new board for rotation
            if (target == 1){ //using different formular for different rotation
                for(int x=0;x<shapesize;x++){
                    for(int y=0;y<shapesize;y++){
                        p[x][y] = board[y][x];
                    }
                }
            }else if (target == 2){
                for(int x=0;x<shapesize;x++){
                    for(int y=0;y<shapesize;y++){
                        p[x][y] = board[shapesize-x-1][y];
                    }
                }
            }else if(target == 3){
                for(int x=0;x<shapesize;x++){
                    for(int y=0;y<shapesize;y++){
                        p[y][x] = board[shapesize-x-1][y];
                    }
                }
            }else{
                return;
            }
            delete [] board; //release the memeory for the orginal board
            board = p;//setting the pointer to the new board
        }
        void printboard(){
            for(int i=0;i<shapesize;i++){
                for(int j=0;j<shapesize;j++){
                    std::cout << this->board[i][j] << " ";
                }
                std::cout << std::endl;
            }
        }
        shape(char p[][shapesize]){
            i = 0; //setting the rotation indicator to 0 when the class in constructed
            board = new char [shapesize][shapesize]; //alocate memory for the board
            memcpy(board,p,shapesize*shapesize*sizeof(char));//copy memory data from the given array to the board
        };
        ~shape() {
            delete [] board;
        }
    private:
        int i;

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