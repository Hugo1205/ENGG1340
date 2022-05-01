#ifndef __io__
#define __io__
#include <fstream>
#include <vector>
#include "game_type.h"
using namespace std;
const int increasesize = 3;
void growthlist(shape * &ls,int &size,int n);
int getshape(shape *&ls);
int ReadGameFromFile(games &game, std::string fname); //return 1 if error occurs else 0
int WriteGameToFile(games &game, std::string fname); //return 1 if error occurs else 0
void moveIntake(int &flag,shape &shapetest, games &game, int &userend);
void boardPrinter(int &flag,shape & shapetest,games &game, int &userend,shape * &ls, int & len);
int game_main(games &game);
#endif 