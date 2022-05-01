#include "io.h"
mutex mut;
using namespace std;
void GrowthList(Shape * &ls,int &size,int n){
    Shape * new_ls = new Shape[size+n]; //create a new list with added length
    if(ls != nullptr){
        for(int i=0;i<size;i++){
            new_ls[i] = ls[i]; //copy data from the old list to new list
        }
        delete [] ls; //delete the old list
    }
    ls = new_ls; //set the pointer point to the new list
    size += n; // give the new size
}

int GetShape(Shape * &ls){
    int size(0),pos(0);//init. size and pos
    char temp; //create a temp char. for indicating begin of a shape
    ifstream fin;
    fin.open("./dependence/shapels.txt");
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
            GrowthList(ls,size,increasesize);
        }
        ls[pos++] = Shape(temp_ls);
    }
    return pos;
}

int ReadGameFromFile(Games &game, std::string fname){
    ifstream fin;
    fname = "./saves/" + fname;
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

int WriteGameToFile(Games &game, string fname){
    ofstream fout;
    fname = "./saves/" + fname;
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
void MoveInTake(int &flag,Shape &shape,Games & game, int &userend){
    char c;
    while (userend){ //for ever loop
        //input
        cin >> c;
        c = tolower(c); //to make it work for both upper and lower cases
        while(!mut.try_lock());
        if(flag && userend){
            if ('d'==c && shape.x != 15){
                if(shape.x<15){
                    for(int i=0;i<3;i++){
                        if(shape.y+i<Maxheight && shape.y+i>=0){
                            if(game.board[shape.y+i][shape.x+1] != '0')
                                return;
                        }
                    }
                }
                shape.x+=1;
            }else if ('a'== c && shape.x != 0){
                if(shape.x>0){
                    for(int i=0;i<3;i++){
                        if(shape.y+i<Maxheight && shape.y+i>=0){
                            if(game.board[shape.y+i][shape.x+1] != '0')
                                return;
                        }
                    }
                }
                shape.x-=1;
            }else if ('w' == c) {
                shape.SetRotation(shape.i+1);
            }
            else if ('s' == c) {
                shape.SetRotation(shape.i-1);
            }else if ('e' == c){
                flag = 0;
                userend = 0;
            }
        }
        mut.unlock();
    }
}

void BoardPrinter(int &flag, Shape & shape,Games &game,int &userend,int &contin, Shape * &ls, int &len){
    while (userend){ //for ever loop
        while(flag){
            while(!mut.try_lock());
            int xIdx = 0, yIdx = 0;
            for (int s1 = 0; s1 < Maxheight;++s1) {
                for (int s2 = 0; s2 < MaxWidth; ++s2) {
                    if ((s1 == shape.y && s2 == shape.x) || (s1 == shape.y && s2 == shape.x+1) || (s1 == shape.y && s2 == shape.x+2) || (s1 == shape.y+1 && s2 == shape.x) || (s1 == shape.y+1 && s2 == shape.x+1) || (s1 == shape.y+1 && s2 == shape.x+2) || (s1 == shape.y+2 && s2 == shape.x) || (s1 == shape.y+2 && s2 == shape.x+1) || (s1 == shape.y+2 && s2 == shape.x+2)) {
                        if(shape.board[yIdx][xIdx] != '0'){
                            cout<<shape.board[yIdx][xIdx];    //FIX IN MAIN
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
            if(Contact(game,shape)){
                ShapeToBoard(game,shape);
                RemoveMatches(game);
                contin = !(shape.y<0);
                if(contin){
                    shape = ls[rand()%len];
                }else{
                    cout << "game over press e to exit!" << endl;
                    mut.unlock();
                    return;
                }
            }else
                shape.y += 1;
            mut.unlock();
            this_thread::sleep_for(chrono::duration<int, std::milli>( 300 ) );
            while(!mut.try_lock());
            cout <<  "\033[18A";
            for(int i=0;i<18;i++){
                cout << "\033[K" << endl;
            }
            cout <<  "\033[18A";
            mut.unlock();
        }
    }
}
//NEW CODES END

