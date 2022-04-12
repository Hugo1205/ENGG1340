#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <unistd.h>
//#include <termios.h> //get more info tmr
using namespace std;
void off(void){
    struct termios t;
    tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
    t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
    t.c_lflag &= ~ECHO;
    t.c_lflag |= ECHONL;
    tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
}

void foo(int &a,int &flag){
    char c;
    this_thread::sleep_for( chrono::duration<int, std::milli>( 100 ) ); //sleep();
    while (flag){ //for ever loop
        c = getchar(); //input
        if ('w'==c)
            a++;
        else if ('s'==c)
            a--;
        else if ('e' == c)
            flag = 0;
    }
}

void foo2(int &a,int &flag){
    while (flag){ //for ever loop
        for(int i=0;i<10;i++){
            cout << a << endl;
            this_thread::sleep_for( chrono::duration<int, std::milli>( 100 ) );
        }
        cout <<  "\033[10A";
        for(int i=0;i<10;i++){
            cout << "\033[K" << endl;
        }
        cout <<  "\033[10A";
    }
}
int main(){
    int a(0);
    int flag(1);
    off();
    thread th1(foo,ref(a),ref(flag));
    thread th2(foo2,ref(a),ref(flag));
    th1.join();
    th2.join();
    return 0;
}
