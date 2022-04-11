#include <fstream>
#include "game_type.h"
using namespace std;

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
