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
    while (userend){ //for ever loop
        //input
        cin >> c;
        c = tolower(c); //to make it work for both upper and lower cases
        while(!mut.try_lock());
        if(flag && userend){
            if ('d'==c && shapetest.x != 15){
                if(shapetest.x<15){
                    for(int i=0;i<3;i++){
                        if(shapetest.y+i<Maxheight && shapetest.y+i>=0){
                            if(game.board[shapetest.y+i][shapetest.x+1] != '0')
                                return;
                        }
                    }
                }
                shapetest.x+=1;
            }else if ('a'== c && shapetest.x != 0){
                if(shapetest.x>0){
                    for(int i=0;i<3;i++){
                        if(shapetest.y+i<Maxheight && shapetest.y+i>=0){
                            if(game.board[shapetest.y+i][shapetest.x+1] != '0')
                                return;
                        }
                    }
                }
                shapetest.x-=1;
            }else if ('w' == c) {
                shapetest.SetRotation(shapetest.i+1);
            }
            else if ('s' == c) {
                shapetest.SetRotation(shapetest.i-1);
            }else if ('e' == c){
                flag = 0;
                userend = 0;
            }
        }
        mut.unlock();
    }
}

void boardPrinter(int &flag, shape & shapetest,games &game,int &userend, shape * &ls, int &len){
    while (userend){ //for ever loop
        while(flag){
            while(!mut.try_lock());
            int xIdx = 0, yIdx = 0;
            int failend(1);
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
            cout<<"score: " << game.score <<endl;
            if(contact(game,shapetest)){
                shapeToBoard(game,shapetest);
                removeMatches(game);
                failend = !(shapetest.y<0);
                if(failend){
                    flag = 0;
                    shapetest = ls[rand()%len];
                }else{
                    cout << "game over press e to exit!" << endl;
                    mut.unlock();
                    return;
                }
            }else
                shapetest.y += 1;
            mut.unlock();
            this_thread::sleep_for(chrono::duration<int, std::milli>( 300 ) );
            cout <<  "\033[18A";
            for(int i=0;i<18;i++){
                cout << "\033[K" << endl;
            }
            cout <<  "\033[18A";
            while(!mut.try_lock());
            if(userend)
                flag = failend;
            mut.unlock();
        }
    }
}
//NEW CODES END
int game_main(games &game){
    int len;
    keyboard kb;
    shape * ls = nullptr;
    srand(time(NULL));
    kb.off();
    len = getshape(ls);
    int flag(1),userend(1);
    while (flag){
        shape temp;
        temp = ls[rand()%len];
        thread th1(moveIntake,ref(flag),ref(temp),ref(game),ref(userend));
        thread th2(boardPrinter,ref(flag),ref(temp),ref(game),ref(userend),ref(ls),ref(len));
        th1.join();
        th2.join();
        
    }
    delete [] ls;
    kb.on();
    if (userend) //if it is stop by the user
        return 0;
    return 1;
}
