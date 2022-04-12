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

class shape
{
    public:
        char (*board)[shapesize];//declare of the board
        
        void setroation(int number){
            int target = (number-i)%4; //calc. how many rotation needed and perform the according rotation
            if (target == 0)
                return;
            char (*p)[shapesize] = new char [shapesize][shapesize];
            if (target == 1){
                for(int x=0;x<shapesize;x++){
                    for(int y=0;y<shapesize;y++){
                        p[x][y] = this->board[y][x];
                    }
                }
            }else if (target == 2){
                for(int x=0;x<shapesize;x++){
                    for(int y=0;y<shapesize;y++){
                        p[x][y] = this->board[shapesize-x-1][y];
                    }
                }
            }else{
                for(int x=0;x<shapesize;x++){
                    for(int y=0;y<shapesize;y++){
                        p[y][x] = this->board[shapesize-x-1][y];
                    }
                }
            }
            delete [] this->board;
            this->board = p;
        }
        void printboard(){
            for(int i=0;i<shapesize;i++){ //print the board
                for(int j=0;j<shapesize;j++){
                    std::cout << this->board[i][j] << " ";
                }
                std::cout << endl;
            }
        }
        void operator=(shape *a){
            memcpy(this->board,a->board,shapesize*shapesize*sizeof(char)); //when = to a pointor, copy the board and i
            this->i = a->i;
            delete a; //delete the orignal pointer afterwards
        }
        void operator=(shape a){
            memcpy(this->board,a.board,shapesize*shapesize*sizeof(char)); //copy board
            this->i = a.i;//copy i
        }
        shape(char p[][shapesize]){
            this->i = 0; //set i to 0
            this->board = new char [shapesize][shapesize]; //allocate memory for the board
            memcpy(this->board,p,shapesize*shapesize*sizeof(char)); //copy memory data to board
        }
        shape(){
            this->board = new char [shapesize][shapesize]; //allocate memory for the board
            this->i = 0; //set i to 0
        }
        ~shape() {
            delete [] this->board; //deconstructor realise the memory holding by the board when the class is distory
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