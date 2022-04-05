#include <iostream>
#include <string>
//#include "io.h"
//#include "game_type.h"
using namespace std;

void menu ();

int main () {
    menu ();
    return 0;
}

void menu () {
  int option;
  cout<<"Welcome to Tetris!"<<endl;
  cout<<"Select Option: "<<endl;
  cout<<"1. Start New Game"<<endl;
  cout<<"2. Last Game Status"<<endl;
  cout<<"3. Game Rules"<<endl;
  cout<<"Enter Option Number: ";
  cin>>option;
}
