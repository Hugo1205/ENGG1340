#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <cstring>
#include <unistd.h>
#include <termios.h>
#define Maxheight 17
#define MaxWidth 18
#define shapesize 3
struct games{
    int board[Maxheight][MaxWidth];
    int score;
};
class keyboard{ //a class for easy management of input method
    private:
        struct termios setting; // a variable storing the orginal setting
    public:
        void off();
        void on();
        keyboard();
};
void keyboard::off(){ //turn off echo for input and cancell the need of enter for input
    struct termios t=setting;
    t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what we want it to do
    t.c_lflag &= ~ECHO;
    t.c_lflag |= ECHONL;
    tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
}
void keyboard::on(){//turn the setting back to the orginal
    tcsetattr(STDIN_FILENO, TCSANOW, &setting); //Apply the orginal settings
}
keyboard::keyboard(){// a constructor to init. the setting variable
    tcgetattr(STDIN_FILENO, &setting); //get the current terminal I/O structure
}
class shape{
    public:
        char (*board)[shapesize];//declare of the board
        void setroation(int number); //rotation function of the board
        void printboard();
        void operator=(shape const &a);
        shape(char p[][shapesize]); //a constructor for the shape when provided a char array
        shape(); //empty constructor
        ~shape();//deconstructor for the shape
    private:
        int i;

};
void shape::setroation(int number){
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
void shape::printboard(){
    for(int i=0;i<shapesize;i++){ //print the board
        for(int j=0;j<shapesize;j++){
            std::cout << this->board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void shape::operator=(shape const &a){
    memcpy(this->board,a.board,shapesize*shapesize*sizeof(char)); //copy board
    this->i = a.i;//copy i
}
shape::shape(char p[][shapesize]){
    this->i = 0; //set i to 0
    this->board = new char [shapesize][shapesize]; //allocate memory for the board
    memcpy(this->board,p,shapesize*shapesize*sizeof(char)); //copy memory data to board
}
shape::shape(){
    this->board = new char [shapesize][shapesize]; //allocate memory for the board
    this->i = 0; //set i to 0
}
shape::~shape() {
    delete [] this->board; //deconstructor realise the memory holding by the board when the class is distory
}

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
