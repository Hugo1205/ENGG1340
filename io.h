#include <fstream>
#include <unistd.h>
#include <termios.h>
#include "game_type.h"
#define increasesize 3
class keyboard{//a class for easy management of input method
    private:
        struct termios setting;// a variable storing the orginal setting
    public:
        void off();//turn off echo for input and cancell the need of enter for input
        void on();//turn the setting back to the orginal
        keyboard();// a constructor to init. the setting variable
};
void growthlist(shape * &ls,int &size,int n);
int getshape(shape *&ls);
int ReadGameFromFile(games &game, std::string fname); //return 1 if error occurs else 0
int WriteGameToFile(games &game, std::string fname); //return 1 if error occurs else 0