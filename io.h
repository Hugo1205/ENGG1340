#include <fstream>
#include "game_type.h"
#define increasesize 3

void growthlist(shape * &ls,int &size,int n);
int getshape(shape *&ls);
int ReadGameFromFile(games &game, std::string fname); //return 1 if error occurs else 0
int WriteGameToFile(games &game, std::string fname); //return 1 if error occurs else 0