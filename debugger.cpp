void shapeToBoard(games &game, shape shapeTest) {   //to be used to add the shape into the main board
  int xIdx = 0, yIdx = 0;
  for (int s1 = 0; s1 < Maxheight;++s1) {
    for (int s2 = 0; s2 < MaxWidth; ++s2) {
      if ((s1 == shapetest.y && s2 == shapetest.x) || (s1 == shapetest.y && s2 == shapetest.x+1) || (s1 == shapetest.y && s2 == shapetest.x+2) || (s1 == shapetest.y+1 && s2 == shapetest.x) || (s1 == shapetest.y+1 && s2 == shapetest.x+1) || (s1 == shapetest.y+1 && s2 == shapetest.x+2) || (s1 == shapetest.y+2 && s2 == shapetest.x) || (s1 == shapetest.y+2 && s2 == shapetest.x+1) || (s1 == shapetest.y+2 && s2 == shapetest.x+2)) {
        if(shapetest.board[yIdx][xIdx] != '0'){
          game.board[s1][s2] = shapetest.board[yIdx][xIdx];    //FIX IN MAIN
        }
        //else {
          //cout<<game.board[s1][s2];
        //}
        xIdx+=1;
        if (xIdx>2) {
          yIdx+=1;
          xIdx=0;
        }
      }
      //else {
        //cout<<game.board[s1][s2];
      //}
    }
    //cout<<endl;
  }
}
