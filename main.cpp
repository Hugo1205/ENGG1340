#include <iostream>
#include <string>
#include <fstream>
//#include "io.h"
//#include "game_type.h"
using namespace std;

void menu ();
void checkOption (int option);
void readRules ();
void newGame ();
void loadGame ();

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

  checkOption (option);  //function to check option selected
}

void checkOption (int option) {
  if (option == 1) {
    newGame ();
  }
  else if (option == 2) {
    loadGame ();
  }
  else if (option == 3) {
    readRules ();
  }
}

void readRules () {
  ifstream fin;
  fin.open("gameRules.txt");
  if (fin.fail()) {
    cout<<"Error in file opening"<<endl;
    exit(1);   ///UNSURE IF TO PUT return 1 or exit(1) here!!
  }

  string line;
  while (getline(fin,line)) {
    cout<<line<<endl;
  }
  fin.close();
}

void newGame () {

}
void loadGame () {
  
}
