# ENGG1340
## Group information
- Group number: 74
- Member 1.
  * Wong Tsz Hin
  * UID- 3035927489
  * Github account: Hugo1205
- Member 2.
  * HUSSAIN Wasif Latif 
  * UID- 3035834577
  * Github account: wasiflatifhussain
            

## Description and Game Information:
### Game Name
# Tetris
           
* We will have a menu which will act as a loading screen, allowing the player to start new game, load pre-saved game, end a game, and display rules for the game.
* The game will have a rectangular 17 x 18 dimensional board, where, the player will have to fit randomly generated shapes, generated using rand() and srand() functions.
The rand() and srand() functions are used to pick up the shape and orientation from a set of pre-stored shapes.
#### Note that, the board is represented by 0's and any shape in the board is represented by x's
* The target of the player is to prevent a single column of tetris blocks from reaching the top edge of the rectangular border board.
* When the player successfully fits the tetris blocks in such a way that a horizontal row x's are formed at any row of the board, that row of x's are removed and replaced by a new row of 0's.
* The player can use the 'w/W' or 's/S' keys to change the rotation/orientation of the shape, while the 'a/A' or 'd/D' keys can be used to move the shape left or right along the board.
And the game continues on. The speed for drop of tetris blocks is kept constant for ease of player.

## Compilation and execution instructions:
To compile the program and play the game, please launch the linux terminal and enter the follow codes:
```
make game
./game
```

### Visual Representation of game in play: 
```
000000000000000000000000  
0                      0     
0    #                 0             
0    #                 0     
0    #                 0
0    #                 0
0       ####           0
0######################0
000000000000000000000000
```
This is a temporary visual representation of the game we plan to make.
Here, the 0s represent the board while the x's represent any of the shape blocks falling inside the board.
Notice that the last line at lower edge of the board has a line/row of x's,which will mean that this row will now get eliminated and all rows will now move one row down, and the game will continue.

###Game Lose Condition:
```
000000000000000000000000     
0  #                   0    
0  #                   0           
0  #                   0     
0  #                   0
0  #                   0
0  #    ####           0
0  #         ##########0
000000000000000000000000
```
If the player ends up having a single column of x's(tetris blocks) spanning from the lower edge of the board to the upper edge of the board, this will cause the player to lose the game. 

## Features and implementation of the coding requirements:
### 1. Generation of random game sets or events: 
   * The tetris block is randomly generated from a pre-made set which will contain all the shapes which can be generated to be used by the player during
a single game of tetris. Each time, a shape will be picked out of the set randomly, along with a random orientation, and the player has to fit the 
block into the rectangular n x m board.

#### 2. Data Structures usage:
   - Data strucutres used for representing the game board status. 
   Two-dimensional arrays used to represent x-y coordinates.
   Data structures for controlling tetris blocks(three dimensional arrays represenitng shapes, orientations and speed).
   
3. Dynamic Memory Management:
   - Memory is allocated to storing the game data and for storing the high score for the game. We will also be allocating memory to allow the player to save
load game and load it whenever they want to play the game. To save memory, we will overwrite existing memory to save new data. Furthermore, we will also only 
store a fixed number of shapes in a predefined array and rotate them during the game, instead of generating and storing a new shape everytime. This is likely 
to help save memory and manage the data better.
   

4. File input/output (e.g. for loading/saving game status)
   - .txt files used to store game status, so the player can save the game and load it back on if they want to.
   .txt files used to save game rules and load them if player clicks the rules tab on the loading screen
   
5. Program codes in multiple files
   - The I/O(input/output) and the game algorithm will be stored in separate files, and used simultaneoulsy during code execution.
