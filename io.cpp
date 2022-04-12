#include <fstream>
#include <unistd.h>
#include <termios.h>
#include "game_type.h"
#define increasesize 3
using namespace std;

class keyboard{ //a class for easy management of input method
    private:
        struct termios setting; // a variable storing the orginal setting
    public:
        void off(){ //turn off echo for input and cancell the need of enter for input
            struct termios t=setting;
            t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what we want it to do
            t.c_lflag &= ~ECHO;
            t.c_lflag |= ECHONL;
            tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
        }
        void on(){//turn the setting back to the orginal
            tcsetattr(STDIN_FILENO, TCSANOW, &setting); //Apply the orginal settings
        }
        keyboard(){// a constructor to init. the setting variable
            tcgetattr(STDIN_FILENO, &setting); //get the current terminal I/O structure
        }
};
void growthlist(shape * &ls,int &size,int n){
    shape * new_ls = new shape[size+n]; //create a new list with added length
    for(int i=0;i<size;i++){
        new_ls[i] = ls[i]; //copy data from the old list to new list
    }
    delete [] ls; //delete the old list
    ls = new_ls; //set the pointer point to the new list 
    size += n; // give the new size
}
int getshape(shape *&ls){
    int size(increasesize),pos(0);//init. size and pos
    char temp; //create a temp char. for indicating begin of a shape
    ifstream fin;
    fin.open("shapels.txt");
    if (fin.fail()){
        return -1; //if no unable to open file return -1 for error control
    }
    while (fin >> temp){//in this loop get data from the txt to a char array then append the shape ls
        char temp_ls[shapesize][shapesize]; 
        for(int i=0;i<shapesize;i++){
            for(int j=0;j<shapesize;j++){
                fin >> temp_ls[i][j];
            }
        }
        if (pos>=size){
            growthlist(ls,size,increasesize);
        }
        ls[pos++] = new shape(temp_ls);
    }
    return pos;
}
int ReadGameFromFile(games &game, std::string fname){
    ifstream fin;
    fin.open(fname.c_str());
    if (fin.fail()){
        cout<<"Error in file opening" << endl;
        return 1; //return 1 instead of exit(1) to prevent shutting program down
    }
    for(int i=0;i<Maxheight;i++){
        for(int j=0;j<MaxWidth;j++){
            fin >> game.board[i][j];
        }
    }
    fin >> game.score;
    fin.close();
    return 0;
}

int WriteGameToFile(games &game, string fname){
    ofstream fout;
    fout.open(fname.c_str());
    if (fout.fail()){
        cout << "Error in file opening" << endl;
        return 1;//return 1 instead of exit(1) to prevent shutting program down
    }
    for(int i=0;i<Maxheight;i++){
        for(int j=0;j<MaxWidth;j++){
            fout << game.board[i][j] << " ";
        }
    }
    fout << game.score;
    fout.close();
    return 0;
}