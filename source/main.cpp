#include "io.h"
#include <stdlib.h> //for srand and rand
#include <time.h> //for time(NULL)
using namespace std;

void Menu ();
void CheckOption (string & option);
void readRules ();
void newGame ();
void loadGame ();
int main () {
  Menu ();
  return 0;
}
void trim(string & s){
  while(isspace(s[0])){
      s = s.substr(1,s.size()-1);
  }
  while(isspace(s[s.size()-1])){
      s = s.substr(0,s.size()-1);
  }
}
void Menu () {
  string option;
  cout<<"Welcome to Tetris!"<<endl;
  cout<<"Select Option: "<<endl;
  cout<<"1. Start New Game"<<endl;
  cout<<"2. Last Game Status"<<endl;
  cout<<"3. Game Rules"<<endl;
  cout<<"4. Exit"<<endl;
  cout<<"Enter Option Number: ";
  cin>>option;
  trim(option);
  while (option != "4") {
    if (option == "1" || option == "2" || option == "3"){
      cout<<endl;
      CheckOption (option);  //function to check option selected
      cout<<endl;
    }
    cout<<"Enter Option Number: ";
    cin>>option;
    trim(option);
  }
  if (option == "4") {
    cout<<"Game Exited."<<endl;
  }
}

void CheckOption (string & option) {
  if (option == "1") {
    newGame ();
  }
  else if (option == "2") {
    loadGame ();
  }
  else if (option == "3") {
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
  Games game;//Since it is a new game we create a new game with type Games
  if(GameMain(game)){ //This will be the part where the game process take places.
    string fname; //after the game is done ask for the name of save file
    cout << "Input save file name:";
    cin >> fname;
    if(fname.find(".txt")==-1) //if the user do no add .txt we add it for them
      fname += ".txt";
    WriteGameToFile(game,fname);
  }
}

//Function: Reads the board from the last game and outputs
//          the result.

void loadGame () {
  games game;
  string fname;
  cout << "Input load file name:";
  cin >> fname;
  string temp = fname;
  ifstream fin;
  if(temp.find(".txt")==-1)//if the user do no add .txt we add it for them
    temp += ".txt";
  if(temp.find("./saves/")==-1)
    temp = "./saves/" + temp;
  fin.open(temp.c_str());
  while (fin.fail()) {
      cout<<"Enter an existing file name: ";
      cin>>fname;
      string temp = fname;
      if(temp.find(".txt")==-1)//if the user do no add .txt we add it for them
        temp += ".txt";
      if(temp.find("./saves/")==-1)
        temp = "./saves/" + temp;
      fin.open(temp.c_str());
  }
  //cout<<"outside while"<<fname<<endl;
  fin.close();
  //cout<<"after close"<<fname<<endl;
  if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
    fname += ".txt";
  ReadGameFromFile(game,fname);
  if(game_main(game)){
    cout << "Input save file name:";
    cin >> fname;
    if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
      fname += ".txt";
    WriteGameToFile(game,fname);
  }
}


/*
void loadGame () {
  Games game;
  string fname;
  cout << "Input load file name:";
  cin >> fname;
  ifstream fin;
  if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
    fname += ".txt";
  fin.open(fname.c_str());
  while (fin.fail()) {
      cout<<"Enter an existing file name: ";
      cin>>fname;
      if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
        fname += ".txt";
      fin.open(fname.c_str());
  }
  //cout<<"outside while"<<fname<<endl;
  fin.close();
  //cout<<"after close"<<fname<<endl;
  if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
    fname += ".txt";
  ReadGameFromFile(game,fname);
  if(GameMain(game)){
    cout << "Input save file name:";
    cin >> fname;
    if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
      fname += ".txt";
    WriteGameToFile(game,fname);
  }
}*/

//Function: Reads the board from the last game and outputs
//          the result.
/*void loadGame () {
  games game;
  string fname;
  cout << "Input load file name:";
  cin >> fname;
  if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
    fname += ".txt";
  ReadGameFromFile(game,fname);
  if(game_main(game)){
    cout << "Input save file name:";
    cin >> fname;
    if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
      fname += ".txt";
    WriteGameToFile(game,fname);
  }
}
*/
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
void printgame(int &flag,Games game)
multi tread and input setup.

*/
