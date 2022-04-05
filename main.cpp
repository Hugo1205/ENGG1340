#include "io.h"
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
  cout<<"4. Exit"<<endl;
  cout<<"Enter Option Number: ";
  cin>>option;
  while (option != 4) {
    if (option == 1 || option == 2 || option == 3){
      cout<<endl;
      checkOption (option);  //function to check option selected
      cout<<endl;
    }
    cout<<"Enter Option Number: ";
    cin>>option;
  }
  if (option == 4) {
    cout<<"Game Exited."<<endl;
  }
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

//Function: Reads the rules of the game from a file named gameRules.txt
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


//@hugo= FEEL FREE to make edits in the codes below.
// i am unsure what steps you want here so i just initiated fstreams 

//Function: Initiates a new board and starts the game

void newGame () {
  games game(initgame());//Since it is a new game we create a new game with type games
  
  //games(); //This will be the part where the game process take places.
  string fname; //after the game is done ask for the name of save file
  cin >> fname;
  WriteGameToFile(game,fname); //maybe add error dealing later
}

//Function: Reads the board from the last game and outputs
//          the result.
void loadGame () {
  ofstream fout;
  fout.open("gameBoard.txt");
  if (fout.fail()) {
    cout<<"Error in loadGame file opening"<<endl;
    exit(1);
  }

  ////CODES HERE/////

  fout.close();
}
