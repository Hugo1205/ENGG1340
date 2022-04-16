#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <cstring>
#include <unistd.h>
#include <termios.h>
const int Maxheight = 17;
const int MaxWidth = 18;
const int shapesize = 3;
struct games{
    int board[Maxheight][MaxWidth];
    int score;
};
class keyboard{//a class for easy management of input method
    private:
        struct termios setting;// a variable storing the orginal setting
    public:
        void off();//turn off echo for input and cancell the need of enter for input
        void on();//turn the setting back to the orginal
        keyboard();// a constructor to init. the setting variable
};
class shape{
    public:
        char (*board)[shapesize]; // a pointer to a 2D array that represent the board
        int x,y; //location ref to the larger game board
        void setroation(int number); //rotation function of the board
        void printboard();//print the board
        void operator=(shape const &a); //operator = when dealing with shape
        shape(char p[][shapesize]); //a constructor for the shape when provided a char array
        shape(); //empty constructor
        ~shape();//deconstructor for the shape
        int i;
};

games initgame();

shape shapeList();

void game_main();