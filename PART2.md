# Part 2

## Video Demo

[Video Demo](https://youtu.be/D17BrgxTpF0)

## Minimum Requirements

### Completed

List all the features completed.

1. Generate game board with rows & column numbers displayed correctly
2. Spawn game objects randomly in board
3. Allow user to adjust board dimensions & number of zombies
4. Spawn alien & zombie in the board, with alien being in the center
5. Initialize alien and zombies' attributes
6. Alien's movement and attack
7. Zombies' movement and attack
8. Alien's interactions with game objects
9. Game controls
10. Save and load game file
11. Game flow

## Additional Features

A new game object, bomb, has been implemented, represented by "b" in the board. The bomb will inflict 10 damage to both Alien and Zombies if they are within a 1 unit radius of the bomb. 

The bomb will also destroy all nearby game objects within a 1 unit radius except for rock, which only breaks to reveal an object underneath.

## Contributions

List down the contribution of each group members.

### Ashley Sim Ci Hui

1. Generate game board
2. Allow user to adjust board dimensions & number of zombies
3. Spawn Alien in the center of board
4. Randomly initialize Alien and Zombies' attributes within a range
5. Alien moves continuously
6. Alien stops when hitting rock/border/Zombie that survives an attack
7. Implemented arrow, health, pod and rock objects
8. Implemented bomb object (additional feature)
9. Up, down, left, right, arrow, save and load commands
10. Alien and Zombie take turns to act
11. Make the game end when either Alien or all Zombies are defeated

### Chin Shuang Ying

1. Spawn game objects randomly in board
2. Spawn Zombies in board
3. Trail resets after Alien's turn
4. Zombies' movement
5. Save, load and quit commands

## Problems Encountered & Solutions

### Problem 1: Alien's movement

#### Description:

When encountering an arrow object, Alien would change direction. However, even after doing so, the objInFront variable would continue to record objects based on Alien's previous direction. This would cause Alien to sometimes move past borders or mistakenly detect objects.

This was caused by the following code:

```
if (cmd == "up" || cmd == "down" || cmd == "left" || cmd == "right") {
    alien.changeDir(cmd);

    while (alien.getDir() == "up") {
        while (board.isInsideMap(alien.getX(), alien.getY() + 1) == true) {
            objInFront = board.getObject(alien.getX(), alien.getY() + 1);

            if (objInFront == ' ' || objInFront == 'h' ||
                objInFront == 'p' || objInFront == '.') {
                cout << endl;
                reportObject(alien, objInFront);

                if (objInFront == 'p') {
                    encounterPod(board, zombies, alien.getX(), alien.getY() + 1);
                }

                alien.move(board, alien.getDir());
                
                pf::Pause();
                board.display();
                alien.displayStats();
                for (int i = 0; i < totalZomb; i++) {
                    cout << "Zombie " << i + 1 << " : ";
                    zombies[i].displayStats();
                }

                continue;
            }
```

In the code above, we can see that it is operating under the assumption that alien's direction is still "up" due to the while loop, and objInFront records the object 1 unit above Alien regardless of whether its direction has changed.

It was also caused by the fact that the Alien class did not contain a variable to store its direction.

#### Solution:

To fix this, two new functions were created in the Alien class: withinBorders() and getObjInFront(), which detected whether the space in front of Alien was within the board's borders, and returned the object in front of Alien respectively. Both used the parameter of Alien's current direction.

Instead of the while loop operating under the condition of Alien's direction, we instead made it operate based on the withinBorders() function.

```
if (cmd == "up" || cmd == "down" || cmd == "left" || cmd == "right") {
    alien.changeDir(cmd);

    while (alien.withinBorders(board)) {
        cout << endl;
        reportObject(alien, alien.getObjInFront(board));

        if (alien.getObjInFront(board) == '^' ||
            alien.getObjInFront(board) == 'v' ||
            alien.getObjInFront(board) == '<' ||
            alien.getObjInFront(board) == '>') {

            encounterArrow(board, alien, zombies, totalZomb, alien.getObjInFront(board));
            continue;
        }
```
If the object in front of Alien was an arrow, the encounterArrow() function would increase Alien's attack, move Alien forward by 1 unit based on the direction it was facing, and then finally change Alien's direction based on the arrow's direction. Then, the while loop would continue to detect the next object in front of Alien.

### Problem 2: Load function (1)

#### Description:

While there was no issue with saving the game data to an external file, there were many problems that we ran into with trying to read it. The following code was problematic because of the fact that we tried to use fin >> obj to read the objects in the board, resulting in the whitespaces not being correctly outputted into the game board after loading.

```
if (fin.is_open()) {
    while (fin.good()) {
        // reads board dimensions
        int dimX, dimY;
        fin >> dimX >> dimY;
        board.init(dimX, dimY);

        for (int i = 1; i <= dimX; i++) {
            for (int j = 1; j <= dimY; j++) {
                char obj;
                fin >> obj;
                board.setObject(i, j, obj);
            }
        }
```

#### Solution:

To remedy this, we simply changed the code
```fin >> obj``` to ```fin.get(obj)```.

```
if (fin.is_open()) {
    while (fin.good()) {
        // reads board dimensions
        int dimX, dimY;
        fin >> dimX >> dimY;
        board.init(dimX, dimY);

        for (int i = 1; i <= dimX; i++) {
            for (int j = 1; j <= dimY; j++) {
                char obj;
                fin.get(obj);
                board.setObject(i, j, obj);
    }
}
```

### Problem 3: Load function (2)

#### Description: 

To retrieve the Zombies' data from the external text file, we attempted to use the code below.

```
for (int i = 0; i < totalSavedZomb; i++) {
    int zombX, zombY, zombLife, zombAtk, zombRange;
    string zombDir;
    fin >> zombX >> zombY >> zombLife >> zombAtk >> zombRange;
    getline(fin, zombDir, ' ');

    Zombie zombie;
    zombie.init(zombX, zombY, zombLife, zombAtk, zombRange, zombDir);
    zombies.push_back(zombie);
}
```

However, this simply resulted in all the Zombies sharing the same attributes as the first Zombie. After some testing, we came to realize that it was because the Zombies' direction attribute was not being properly retrieved. It would start retrieving data from the direction all the way to the end of the file, causing an error.

#### Solution:

To remedy this, we actually had to change the save function to make it so that every direction string ended with the '$' character except for the last one.

```
for (int i = 0; i < totalZomb - 1; i++) {
    fout << zombies[i].getX() << ' '
         << zombies[i].getY() << ' '
         << zombies[i].getLife() << ' '
         << zombies[i].getAtk() << ' '
         << zombies[i].getRange() << ' '
         << zombies[i].getDir() << '$' << endl;
    }

    fout << zombies[totalZomb - 1].getX() << ' '
         << zombies[totalZomb - 1].getY() << ' '
         << zombies[totalZomb - 1].getLife() << ' '
         << zombies[totalZomb - 1].getAtk() << ' '
         << zombies[totalZomb - 1].getRange() << ' '
         << zombies[totalZomb - 1].getDir();
```

Then, '$' could be used as the delimiter in getline so that the program knew when to stop retrieving data.

```
for (int i = 0; i < totalSavedZomb; i++) {
    int zombX, zombY, zombLife, zombAtk, zombRange;
    string zombDir;
    fin >> zombX >> zombY >> zombLife >> zombAtk >> zombRange;
    getline(fin, zombDir, '$');

    Zombie zombie;
    zombie.init(zombX, zombY, zombLife, zombAtk, zombRange, zombDir);
    zombies.push_back(zombie);
}
```

However, we still aren't sure why the last direction string ending with a '$' character causes an error. It works fine without it though, so we just decided to let it be.
