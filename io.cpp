#include <fstream>
#include "game_type.h"
using namespace std;
const int increasesize = 3;
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
        ls[pos++] = shape(temp_ls);
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
            char temp;
            fin >> temp;
            game.board[i][j] = temp;
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

//NEW COES START
void moveIntake(int &flag,shape &shapetest){
    char c;
    this_thread::sleep_for( chrono::duration<int, std::milli>( 100 ) ); //sleep();
    while (flag){ //for ever loop
        c = getchar(); //input
        if ('d'==c && shapetest.x != 15)
            shapetest.x+=1;
        else if ('a'== c && shapetest.x != 0)
            shapetest.x-=1;
        else if ('w' == c) {
            shapetest.SetRotation(shapetest.i+1);
        }
        else if ('s' == c) {
            shapetest.SetRotation(shapetest.i-1);
        }
        else if ('e' == c)
            flag = 0;

    }
}

void boardPrinter(int &flag,shape &shapetest,games game){
    while (flag){ //for ever loop
            int xIdx = 0, yIdx = 0;
            for (int s1 = 0; s1 < Maxheight;++s1) {
                for (int s2 = 0; s2 < MaxWidth; ++s2) {
                    if ((s1 == shapetest.y && s2 == shapetest.x) || (s1 == shapetest.y && s2 == shapetest.x+1) || (s1 == shapetest.y && s2 == shapetest.x+2) || (s1 == shapetest.y+1 && s2 == shapetest.x) || (s1 == shapetest.y+1 && s2 == shapetest.x+1) || (s1 == shapetest.y+1 && s2 == shapetest.x+2) || (s1 == shapetest.y+2 && s2 == shapetest.x) || (s1 == shapetest.y+2 && s2 == shapetest.x+1) || (s1 == shapetest.y+2 && s2 == shapetest.x+2)) {
                            cout<<shapetest.board[yIdx][xIdx];
                            xIdx+=1;
                            if (xIdx>2) {
                                yIdx+=1;
                                xIdx=0;
                            }

                    }
                    else {
                        cout<<game.board[s1][s2];
                    }
                }
                cout<<endl;
            }
            shapetest.y += 1;
            this_thread::sleep_for( chrono::duration<int, std::milli>( 1000 ) );
        cout <<  "\033[17A";
        for(int i=0;i<17;i++){
            cout << "\033[K" << endl;
        }
        cout <<  "\033[17A";
    }
}
//NEW CODES START END

void game_main(games &game){
    keyboard kb;
    kb.off();

    //NEW CODES START
    int flag(1);
    thread th1(moveIntake,ref(flag),ref(shapetest));
    thread th2(boardPrinter,ref(flag),ref(shapetest),ref(game));
    th1.join();
    th2.join();
    //NEW CODES END
    kb.off();
}
