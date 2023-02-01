# Part 1

## Video Demo

[Video Demo]([https://youtube.com](https://www.youtube.com/watch?v=05fASRKdF6k)).

## Minimum Requirements

### Completed

List all the features completed.

1. Generate game board with rows & column numbers displayed correctly
2. Spawn game objects randomly in board
3. Allow user to adjust board dimensions & number of zombies
4. Spawn alien & zombie in the board, with alien being in the center

### To Do

List all the features not yet done. Remove this section if there is no incomplete requirements.

1. Allow alien & zombie to move & attack
2. Allow user to input commands
3. Save & load game file
4. Make game run on turn-based basis
5. Assign reasonable attributes to alien & zombie's stats

## Additional Features

Describe the additional features that has been implemented.

## Contributions

List down the contribution of each group members.

### Ashley Sim Ci Hui

1. Randomly generate game board
2. Allow user to adjust board dimensions & number of zombies
3. Spawn alien in the center of board

### Chin Shuang Ying

1. Spawn game objects randomly in board
2. Spawn zombies in board

## Problems Encountered & Solutions

Describe the problems encountered and provide the solutions / plan for the solutions.

PROBLEM 1:
Board could not be resized after user updated the board dimensions in settings.

SOLUTION:
After some experimenting, we realized that this was because of the default values for the board dimensions in the Board class, which were set to 5 rows and 9 columns using the code Board(int dimX = 9, int dimY = 5);. The solution we came up with was to create a public defaultX & defaultY variable and setting them as the default values for the board. Then, the values stored by the variables would be changed to the value from the user input, thereby updating the X and Y dimensions of the board.

PROBLEM 2:
Zombie(s) would not spawn in the board.

SOLUTION:
Initially, we tried to spawn zombies in using a for loop in the init function of the Board class. We then realized that we had to create separate classes for both alien and zombie and spawn them in using functions in their respective classes. Thus, we created the Alien and Zombie classes as well as the spawnZombie and spawnAlien functions in each class respectively. Instead of a for loop, the spawnZombie and spawnAlien functions determine the x and y coordinates of alien & zombie and then use the setObject function in the Board class to place them in the board.

PROBLEM 3:
Alien would spawn off-center when there were more/less than 5 rows in the board.

SOLUTION:
We realized that the setObject function in the Board class was using the code map_[5 - y][x - 1] = ch; which only centers the alien when there are exactly 5 rows in the board. Thus, we had to adjust the code to map_[dimY_ - y][x - 1] = ch; so that it could calculate the correct coordinates to place the alien in.
