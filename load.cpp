void loadGame () {
  games game;
  string fname;
  cout << "Input load file name:";
  cin >> fname;
  ifstream fin;
  if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
    fname += ".txt";
  fin.open(fname.c_str());
  while (fin.fail()) {
      cout<<"Enter an existing file name: ";
      cin>>fname;
      if(fname.find(".txt")==-1)//if the user do no add .txt we add it for them
        fname += ".txt";
      fin.open(fname.c_str());
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
