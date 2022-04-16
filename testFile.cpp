#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <termios.h> //get more info tmr
#include <cstring>
#define Maxheight 17
#define MaxWidth 18
#define shapesize 3
#include <fstream>

using namespace std;
struct games{
    char board[Maxheight][MaxWidth];
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
        int x,y; //location ref to the larger game board
        void setroation(int number); //rotation function of the board
        void printboard();
        void operator=(shape const &a);
        shape(char p[][shapesize]); //a constructor for the shape when provided a char array
        shape(); //empty constructor
        ~shape();//deconstructor for the shape
        int i;

};
void shape::setroation(int number){
    int target = (number-this->i)%4; //calc. how many rotation needed and perform the according rotation
    this->i = number%4;
    if (target == 0)
        return;
    char (*p)[shapesize] = new char [shapesize][shapesize];
    if (target == 1){
        for(int j=0;j<shapesize;j++){
            for(int k=0;k<shapesize;k++){
                p[shapesize-j-1][k] = this->board[k][j];
            }
        }
    }else if (target == 2){
        for(int j=0;j<shapesize;j++){
            for(int k=0;k<shapesize;k++){
                p[j][k] = this->board[shapesize-j-1][k];
            }
        }
    }else { //either -1 or 3
        for(int j=0;j<shapesize;j++){
            for(int k=0;k<shapesize;k++){
                p[k][j] = this->board[shapesize-j-1][k];
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
    this->x = 0;
    this->y = 0;
    this->board = new char [shapesize][shapesize]; //allocate memory for the board
    memcpy(this->board,p,shapesize*shapesize*sizeof(char)); //copy memory data to board
}
shape::shape(){
    this->board = new char [shapesize][shapesize]; //allocate memory for the board
    this->i = 0; //set i to 0
    this->x = 0;
    this->y = 0;
}
shape::~shape() {
    delete [] this->board; //deconstructor realise the memory holding by the board when the class is distory
}

void foo(int &flag,shape &shapetest){
    char c;
    this_thread::sleep_for( chrono::duration<int, std::milli>( 100 ) ); //sleep();
    while (flag){ //for ever loop
        c = getchar(); //input
        if ('d'==c)
            shapetest.x+=1;
        else if ('a'==c && shapetest.x!=0)
            shapetest.x-=1;
        else if ('w'==c)
            shapetest.setroation(shapetest.i+1);
        else if ('s' == c)
            shapetest.setroation(shapetest.i-1);
        else if ('e' == c)
            flag = 0;
    }
}

void foo2(int &flag,shape &shapetest,games game){
    //string shape[3][3]={{"X","X","X"},{"0","X","0"},{"0","X","0"}};
    while (flag){ //for ever loop
        for(int i=0;i<6;i++){
            for (int k = 0; k < 3; ++k) {
                //cout<<"\033[1C"<<endl;
                for (int m = 0; m <shapetest.x; ++m) {
                    cout<<" ";
                }
                for (int m = 0;m < shapesize; ++m) {
                    cout<<shapetest.board[k][m];
                }
                cout<<endl;
            }
            //cout << a+"***" << endl;
            //cout << a+"0*0" << endl;
            //cout << a+"0*0" << endl;
            //cout << "\033[K" << endl;
            this_thread::sleep_for( chrono::duration<int, std::milli>( 100 ) );
        }
        cout <<  "\033[18A";
        for(int i=0;i<18;i++){
            cout << "\033[K" << endl;
        }
        cout <<  "\033[18A";
    }
}
int ReadGameFromFile(games &game, std::string fname){
    fstream fin;
    fin.open(fname);
    if (fin.fail()){
        cout<<"Error in file opening" << endl;
        return 1; //return 1 instead of exit(1) to prevent shutting program down
    }
    for(int i=0;i<Maxheight;i++){
        for(int j=0;j<MaxWidth;j++){
            char temp;
            fin >> temp;
            game.board[i][j] = temp;
        }
    }
    fin >> game.score;
    fin.close();
    return 0;
}
//printing main board
void printMainBoard(games game) {
    for (int i = 0; i < Maxheight; ++i) {
        for (int j = 0; j < MaxWidth; ++j) {
            cout<<game.board[i][j];
        }
        cout<<endl;
    }
}

int main(){
    keyboard kb;
    kb.off();
    char test[shapesize][shapesize] = {{'*','*','*'},{'0','*','0'},{'0','*','0'}};
    shape shapetest(test);
    games game;
    ReadGameFromFile(game,"gameboard.txt");
    //int a=shapetest.x;
    int flag(1);
    printMainBoard(game);
    //off();
    thread th1(foo,ref(flag),ref(shapetest));
    //char arr={{''}}
    thread th2(foo2,ref(flag),ref(shapetest),ref(game));
    th1.join();
    th2.join();
    kb.on();
    return 0;
}
