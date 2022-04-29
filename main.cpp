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
  games game;//Since it is a new game we create a new game with type games
  game_main(game); //This will be the part where the game process take places.
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
// small 3*3 board as our shape
// we first 

/*
*** *00
0*0 *00
0*0 *** 
0<= ref.x <= upperbound-2
0<= ref.y
when ref.y > upperbound.y-2 we just print part of the fig.
*/

/*
we check the bottom line every time the sharp drop, to see if it is attached to a block under
check lines see any line were filled -> if any move the borad one row down and generate a new empty line at the end
ref.y > upperbound.y-2 the play lose
*/

/*
This week we try to print the board and do the shape dropping and moving regarding the input.

Wasif will be doing:

function one tread:
2 parm one flag one is val for the hor. moving
you decrease the val if player press a
increase if player press d
if the player press e 
-> turn the flag to 0 which end the games
ignore cap look
fucntion on the other tread:
write the inital shape board -> write it inside the game_type.cpp -> game()

void h_val(int &flag,int &val) -> io.h and io.cpp


Hugo will be doing :
function on the other tread:
print board and shape droping
void printgame(int &flag,games game)
multi tread and input setup.

*/