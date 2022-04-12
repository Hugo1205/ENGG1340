#include <fstream>
#include "game_type.h"
class keyboard{//a class for easy management of input method
    private:
        struct termios setting;// a variable storing the orginal setting
    public:
        void off();//turn off echo for input and cancell the need of enter for input
        void on();//turn the setting back to the orginal
        keyboard();// a constructor to init. the setting variable
};
int ReadGameFromFile(games &game, std::string fname); //return 1 if error occurs else 0
int WriteGameToFile(games &game, std::string fname); //return 1 if error occurs else 0