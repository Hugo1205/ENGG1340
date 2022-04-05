#include <iostream>
#include <string>
#include <fstream>
#include "game_type.h"

int ReadGameFromFile(games &game, string fname); //return 1 if error occurs else 0
int WriteGameToFile(games &game, string fname); //return 1 if error occurs else 0