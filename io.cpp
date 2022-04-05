#include <iostream>
#include <string>
#include <fstream>
#include "game_type.h"

int ReadGameFromFile(games &game, string fname){
    std::ifstream fin;
    fin.open(fname.c_str());
    if (fin.fail()){
        std::cout<<"Error in file opening" << std::endl;
        return 1;
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
    std::ofstream fout;
    fout.open(fname.c_str());
    if (fout.fail()){
        std::cout << "Error in file opening" << std::endl;
        return 1;
    }
    for(int i=0;i<Maxheight;i++){
        for(int j=0;j<MaxWidth;j++){
            fout << game.board[i][j] << " ";
        }
    }
    fout << game.score();
    fout.close();
    return 0;
}