#include "game_type.h"
games::games(){
    this->board = new char [Maxheight][MaxWidth];
    for(int i=0;i<Maxheight;i++){
        for(int j=0;j<MaxWidth;j++){
            this->board[i][j] = '0';
        }
    }
    this->score = 0;
}
games::~games(){
    delete [] this->board;
}
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
void shape::SetRotation(int number){
    if(this->board == nullptr)
        return;
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
    this->x = a.x;
    this->y = a.y;
}
shape::shape(char p[][shapesize]){
    this->i = 0; //set i to 0
    this->x = 0;
    this->y = -2;
    this->board = new char [shapesize][shapesize]; //allocate memory for the board
    memcpy(this->board,p,shapesize*shapesize*sizeof(char)); //copy memory data to board
}
shape::shape(){
    this->board = new char [shapesize][shapesize]; //allocate memory for the board
    this->i = 0; //set i to 0
    this->x = 0;
    this->y = -2;
}
shape::~shape() {
    if(this->board != nullptr)
        delete [] this->board; //deconstructor realise the memory holding by the board when the class is distory
}

void removeMatches (games &game) {
    char tempo[17][18];
    int xIdx = Maxheight-1;
    for (int i = Maxheight - 1; i >= 0; --i) {
        int counter = 0;
        for (int j = 0; j < MaxWidth; ++j) {
            if (game.board[i][j] == '*') {
                counter += 1;
            }
        }
        if (counter < 18) {
            for (int m = 0; m < MaxWidth; ++m) {
                tempo[xIdx][m] = game.board[i][m];
            }
            xIdx -= 1;
        }
    }
    while(xIdx >= 0) {
        for (int m = 0; m < MaxWidth; ++m) {
            tempo[xIdx][m] = '0';
        }
        xIdx -=1;
    }
    for (int i = 0; i < Maxheight; ++i) {
        for (int j = 0; j < MaxWidth; ++j) {
            game.board[i][j] = tempo[i][j];
        }
    }
    game.score += 1;
}
bool contact(games &game, shape &shapetest){
    if(shapetest.y+2 == Maxheight-1)
        return true;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if (game.board[shapetest.y+i][shapetest.x+j] !='0' && game.board[shapetest.y+i+1][shapetest.x+j]!= '0')
                return true;
        }
    }
    return false;
}
void shapeToBoard(games &game, shape &shapetest) {   //to be used to add the shape into the main board
  int xIdx = 0, yIdx = 0;
  for (int s1 = 0; s1 < Maxheight;++s1) {
    for (int s2 = 0; s2 < MaxWidth; ++s2) {
      if ((s1 == shapetest.y && s2 == shapetest.x) || (s1 == shapetest.y && s2 == shapetest.x+1) || (s1 == shapetest.y && s2 == shapetest.x+2) || (s1 == shapetest.y+1 && s2 == shapetest.x) || (s1 == shapetest.y+1 && s2 == shapetest.x+1) || (s1 == shapetest.y+1 && s2 == shapetest.x+2) || (s1 == shapetest.y+2 && s2 == shapetest.x) || (s1 == shapetest.y+2 && s2 == shapetest.x+1) || (s1 == shapetest.y+2 && s2 == shapetest.x+2)) {
        if(shapetest.board[yIdx][xIdx] != '0'){
          game.board[s1][s2] = shapetest.board[yIdx][xIdx];    //FIX IN MAIN
        }
        xIdx+=1;
        if (xIdx>2) {
          yIdx+=1;
          xIdx=0;
        }
      }
    }
  }
}
