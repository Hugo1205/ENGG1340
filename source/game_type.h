#ifndef __Game__
#define __Game__
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
class Games{
    public:
        char (*board)[MaxWidth];
        int score;
        Games();
        ~Games();
};
class Keyboard{//a class for easy management of input method
    private:
        struct termios setting;// a variable storing the orginal setting
    public:
        void off();//turn off echo for input and cancell the need of enter for input
        void on();//turn the setting back to the orginal
        Keyboard();// a constructor to init. the setting variable
};
class Shape{
    public:
        char (*board)[shapesize]; // a pointer to a 2D array that represent the board
        int x,y; //location ref to the larger game board
        void SetRotation(int number); //rotation function of the board
        void PrintBoard();//print the board
        void operator=(Shape const &a); //operator = when dealing with shape
        Shape(char p[][shapesize]); //a constructor for the shape when provided a char array
        Shape(); //empty constructor
        ~Shape();//deconstructor for the shape
        int i;
};

void RemoveMatches (Games &game);
bool Contact(Games &game, Shape &shape);
void ShapeToBoard(Games &game, Shape &shape);
int GameMain(Games &game);
#endif