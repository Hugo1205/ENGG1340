void loadGame () {
  games game;
  string fname;
  cout << "Input load file name:";
  cin >> fname;
  string temp = fname;
  ifstream fin;
  if(temp.find(".txt")==-1)//if the user do no add .txt we add it for them
    temp += ".txt";
  if(temp.find("./saves/")==-1)
    temp = "./saves/" + temp;
  fin.open(temp.c_str());
  while (fin.fail()) {
      cout<<"Enter an existing file name: ";
      cin>>fname;
      string temp = fname;
      if(temp.find(".txt")==-1)//if the user do no add .txt we add it for them
        temp += ".txt";
      if(temp.find("./saves/")==-1)
        temp = "./saves/" + temp;
      fin.open(temp.c_str());
  }
  //cout<<"outside while"<<fname<<endl;
  fin.close();
  //cout<<"after close"<<fname<<endl;
  if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
    fname += ".txt";
  ReadGameFromFile(game,fname);
  if(game_main(game)){
    cout << "Input save file name:";
    cin >> fname;
    if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
      fname += ".txt";
    WriteGameToFile(game,fname);
  }
}
