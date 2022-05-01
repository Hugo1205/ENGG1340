#include "io.h"
mutex mut;
using namespace std;
void growthlist(shape * &ls,int &size,int n){
    shape * new_ls = new shape[size+n]; //create a new list with added length
    if(ls != nullptr){
        for(int i=0;i<size;i++){
            new_ls[i] = ls[i]; //copy data from the old list to new list
        }
        delete [] ls; //delete the old list
    }
    ls = new_ls; //set the pointer point to the new list
    size += n; // give the new size
}

int getshape(shape * &ls){
    int size(0),pos(0);//init. size and pos
    char temp; //create a temp char. for indicating begin of a shape
    ifstream fin;
    fin.open("shapels.txt");
    if (fin.fail()){
        return -1; //if no unable to open file return -1 for error control
    }
    while (fin >> temp){//in this loop get data from the txt to a char array then append the shape ls
        char temp_ls[shapesize][shapesize];
        for(int i=0;i<shapesize;i++){
            for(int j=0;j<shapesize;j++){
                fin >> temp_ls[i][j];
            }
        }
        if (pos>=size){
            growthlist(ls,size,increasesize);
        }
        ls[pos++] = shape(temp_ls);
    }
    return pos;
}

int ReadGameFromFile(games &game, std::string fname){
    ifstream fin;
    fin.open(fname.c_str());
    if (fin.fail()){
        cout<<"Error in file opening" << endl;
        return 1; //return 1 instead of exit(1) to prevent shutting program down
    }
    for(int i=0;i<Maxheight;i++){
        for(int j=0;j<MaxWidth;j++){
            char temp;
            fin >> temp;
            game.board[i][j] = temp;
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
            fout << game.board[i][j];
        }
        fout << endl;
    }
    fout << game.score << endl;
    fout.close();
    return 0;
}
//NEW COES START
void moveIntake(int &flag,shape &shapetest,games & game, int &userend){
    char c;
    while (!userend){ //for ever loop
        //input
        cin >> c;
        c = tolower(c); //to make it work for both upper and lower cases
        while(mut.try_lock());
        if ('d'==c && shapetest.x != 15){
            for(int i=0;i<3;i++){
                if(game.board[shapetest.y+i][shapetest.x+1] != '0')
                    return;
            }
            shapetest.x+=1;
        }else if ('a'== c && shapetest.x != 0)
            shapetest.x-=1;
        else if ('w' == c) {
            shapetest.SetRotation(shapetest.i+1);
        }
        else if ('s' == c) {
            shapetest.SetRotation(shapetest.i-1);
        }
        else if ('e' == c){
            flag = 0;
            userend = 1;
        }
        mut.unlock();
    }
}

void boardPrinter(int &flag, shape & shapetest,games &game,int &failend,int &userend){
    while (!userend){ //for ever loop
        while(flag){
            while(mut.try_lock());
            int xIdx = 0, yIdx = 0;
            for (int s1 = 0; s1 < Maxheight;++s1) {
                for (int s2 = 0; s2 < MaxWidth; ++s2) {
                    if ((s1 == shapetest.y && s2 == shapetest.x) || (s1 == shapetest.y && s2 == shapetest.x+1) || (s1 == shapetest.y && s2 == shapetest.x+2) || (s1 == shapetest.y+1 && s2 == shapetest.x) || (s1 == shapetest.y+1 && s2 == shapetest.x+1) || (s1 == shapetest.y+1 && s2 == shapetest.x+2) || (s1 == shapetest.y+2 && s2 == shapetest.x) || (s1 == shapetest.y+2 && s2 == shapetest.x+1) || (s1 == shapetest.y+2 && s2 == shapetest.x+2)) {
                        if(shapetest.board[yIdx][xIdx] != '0'){
                            cout<<shapetest.board[yIdx][xIdx];    //FIX IN MAIN
                        }
                        else {
                            cout<<game.board[s1][s2];
                        }
                        xIdx+=1;
                        if (xIdx>2) {
                            yIdx+=1;
                            xIdx=0;
                        }
                        }
                        else {
                            cout<<game.board[s1][s2];
                        }
                }
                cout<<endl;
            }
            shapetest.y += 1;
            cout<<game.score<<endl;
            mut.unlock();
            this_thread::sleep_for(chrono::duration<int, std::milli>( 500 ) );
            while(mut.try_lock());
            cout <<  "\033[18A";
            for(int i=0;i<18;i++){
                cout << "\033[K" << endl;
            }
            cout <<  "\033[18A";
            if(contact(game,shapetest)){
                failend = (shapetest.y<0);
                if (failend){
                    cout << "game over press e to exit!";
                }
                shapeToBoard(game,shapetest);
                removeMatches(game);
                flag = 0;
            }
        }
        mut.unlock();
    }
}
//NEW CODES END
void setNewShape(shape & shapetest,shape * &ls,int len, int &flag, int &userend){
    while(!userend){
        if(!flag){
            while (mut.try_lock());
            shapetest = ls[rand()%len];
            flag = 1;
            mut.unlock();
        }
        this_thread::sleep_for(chrono::duration<int, std::milli>(100) );
    }
}
int game_main(games &game){
    //NEW CODES START
    //call the shapefuntion here to initiate shape
    // **code here** //
    //i used this in my previous code-
    //char test[shapesize][shapesize] = {{'*','*','*'},{'0','*','0'},{'0','*','0'}};
    //shape shapetest(test);
    int len;
    keyboard kb;
    shape * ls = nullptr;
    srand(time(NULL));
    kb.off();
    len = getshape(ls);
    int flag(1),failend(0),userend(0);
    while (flag){
        shape temp;
        temp = ls[rand()%len];
        thread th1(moveIntake,ref(flag),ref(temp),ref(game),ref(userend));
        thread th2(boardPrinter,ref(flag),ref(temp),ref(game),ref(failend),ref(userend));
        thread th3(setNewShape,ref(temp),ref(ls),ref(len),ref(flag),ref(userend));
        th1.join();
        th2.join();
        th3.join();
    }
    delete [] ls;
    kb.on();
    if (failend) //if it is stop by failend
        return 0;
//NEW CODES END
    return 1;
}
