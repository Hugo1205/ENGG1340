#include <fstream>
#include "game_type.h"

int ReadGameFromFile(games &game, std::string fname); //return 1 if error occurs else 0
int WriteGameToFile(games &game, std::string fname); //return 1 if error occurs else 0