#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <unistd.h>
#include <termios.h> //get more info tmr

#include <fstream>

using namespace std;
void off(void){
    struct termios t;
    tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
    t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
    t.c_lflag &= ~ECHO;
    t.c_lflag |= ECHONL;
    tcsetattr(STDIN_FILENO, TCSANOW, &t); //Apply the new settings
}

void foo(string &a,int &flag){
    char c;
    this_thread::sleep_for( chrono::duration<int, std::milli>( 100 ) ); //sleep();
    while (flag){ //for ever loop
        c = getchar(); //input
        if ('d'==c)
            a+=" ";
        else if ('a'==c && a!="")
            a.resize(a.size()-1);
        else if ('e' == c)
            flag = 0;
    }
}

void foo2(string &a,int &flag){
    string shape[3][3]={{"X","X","X"},{"0","X","0"},{"0","X","0"}};
    while (flag){ //for ever loop
        for(int i=0;i<1;i++){
            for (int k = 0; k < 3; ++k) {
                cout<<a;
                for (int j = 0; j < 3; ++j) {
                    cout<<shape[k][j];
                }
                cout<<endl;
            }
            //cout << a+"***" << endl;
            //cout << a+"0*0" << endl;
            //cout << a+"0*0" << endl;
            //cout << "\033[K" << endl;
            this_thread::sleep_for( chrono::duration<int, std::milli>( 1000 ) );
        }
        cout <<  "\033[3A";
        for(int i=0;i<3;i++){
            cout << "\033[K" << endl;
        }
        //cout <<  "\033[10A";
    }
}
int main(){
    //ifstream fin;
    //fin.open("shape.txt");
    //char shape={{'X','X','X'},{'0','X','0'},{'0','X','0'}};
    string a="";
    int flag(1);
    off();
    thread th1(foo,ref(a),ref(flag));
    //char arr={{''}}
    thread th2(foo2,ref(a),ref(flag));
    th1.join();
    th2.join();
    return 0;
}
