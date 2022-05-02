#include "io.h"
Games::Games(){
    this->board = new char [Maxheight][MaxWidth];
    for(int i=0;i<Maxheight;i++){
        for(int j=0;j<MaxWidth;j++){
            this->board[i][j] = '0';
        }
    }
    this->score = 0;
}
Games::~Games(){
    delete [] this->board;
}
void Keyboard::off(){ //turn off echo for input and cancell the need of enter for input
    struct termios t=setting;
    t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what we want it to do
    t.c_lflag &= ~ECHO;
    t.c_lflag |= ECHONL;
    tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
}
void Keyboard::on(){//turn the setting back to the orginal
    tcsetattr(STDIN_FILENO, TCSANOW, &setting); //Apply the orginal settings
}
Keyboard::Keyboard(){// a constructor to init. the setting variable
    tcgetattr(STDIN_FILENO, &setting); //get the current terminal I/O structure
}
void Shape::SetRotation(int number){
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
void Shape::PrintBoard(){
    for(int i=0;i<shapesize;i++){ //print the board
        for(int j=0;j<shapesize;j++){
            std::cout << this->board[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
void Shape::operator=(Shape const &a){
    memcpy(this->board,a.board,shapesize*shapesize*sizeof(char)); //copy board
    this->i = a.i;//copy i
    this->x = a.x;
    this->y = a.y;
}
Shape::Shape(char p[][shapesize]){
    this->i = 0; //set i to 0
    this->x = 0;
    this->y = -2;
    this->board = new char [shapesize][shapesize]; //allocate memory for the board
    memcpy(this->board,p,shapesize*shapesize*sizeof(char)); //copy memory data to board
}
Shape::Shape(){
    this->board = new char [shapesize][shapesize]; //allocate memory for the board
    this->i = 0; //set i to 0
    this->x = 0;
    this->y = -2;
}
Shape::~Shape() {
    if(this->board != nullptr)
        delete [] this->board; //deconstructor realise the memory holding by the board when the class is distory
}

void RemoveMatches (Games &game) {
    char tempo[Maxheight][MaxWidth];
    int xIdx = Maxheight-1;
    for (int i = Maxheight - 1; i >= 0; --i) {
        int counter = 0;
        for (int j = 0; j < MaxWidth; ++j) {
            if (game.board[i][j] == 'x') {
                counter += 1;
            }
        }
        if (counter < MaxWidth) {
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
bool Contact(Games &game, Shape &shape){
    if(shape.y+2 == Maxheight-1)
        return true;
    for(int i=0;i<3;i++){
        if(shape.y+i+1>=0 && shape.y+i+1<Maxheight){
            for(int j=0;j<3;j++){
                if (shape.board[i][j] !='0' && game.board[shape.y+i+1][shape.x+j]!= '0')
                    return true;
            }
        }
    }
    return false;
}
void ShapeToBoard(Games &game, Shape &shape) {   //to be used to add the shape into the main board
  int xIdx = 0, yIdx = 0;
  for (int s1 = 0; s1 < Maxheight;++s1) {
    for (int s2 = 0; s2 < MaxWidth; ++s2) {
      if ((s1 == shape.y && s2 == shape.x) || (s1 == shape.y && s2 == shape.x+1) || (s1 == shape.y && s2 == shape.x+2) || (s1 == shape.y+1 && s2 == shape.x) || (s1 == shape.y+1 && s2 == shape.x+1) || (s1 == shape.y+1 && s2 == shape.x+2) || (s1 == shape.y+2 && s2 == shape.x) || (s1 == shape.y+2 && s2 == shape.x+1) || (s1 == shape.y+2 && s2 == shape.x+2)) {
        if(shape.board[yIdx][xIdx] != '0' && game.board[s1][s2]=='0'){
          game.board[s1][s2] = shape.board[yIdx][xIdx];    //FIX IN MAIN
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

//Function: main function that loads the keyboard function as well as initiates
//          the functions to move shapes and print board and shape
//Input: it takes in input of game class by reference
//Output: it modifies the board by saving shapes to board as well as removing matches lines
//        in the board.
int GameMain(Games &game){
    int len;
    Keyboard kb;
    Shape * ls = nullptr;
    srand(time(NULL));
    kb.off();
    len = GetShape(ls);
    int flag(1),userend(1),contin(1);
    while (flag){
        Shape temp;
        temp = ls[rand()%len];
        thread th1(MoveInTake,ref(flag),ref(temp),ref(game),ref(userend));
        thread th2(BoardPrinter,ref(flag),ref(temp),ref(game),ref(userend),ref(contin),ref(ls),ref(len));
        th1.join();
        th2.join();

    }
    delete [] ls;
    kb.on();
    if (contin) //if it is stop by the user
        return 1;
    return 0;
}
