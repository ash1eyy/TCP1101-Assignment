# Alien vs. Zombie

Alien vs Zombie is a turn-based combat game in which the player controls Alien to defeat a group of Zombies. Prior to the game, the player can customize settings including game board dimensions and number of zombies. The player can also save a game into a file and load a game from a file.

[Video Demo](https://youtu.be/D17BrgxTpF0)

## Compilation Instructions

```
g++ pf\*.cpp main.cpp
```

## User Manual

The user will control Alien, represented by A. The goal of the game is to maneuver around the board with the help of arrow objects to eliminate the Zombies, represented by unique numbers from 1-9.

For a full list of commands, the user can type "help" into the command prompt.

The user can control Alien's movements by typing either up, down, left, or right into the command line. Alien will inflict damage to Zombies when it collides with them.

Alien will stop moving when it hits a rock, border, or hits a Zombie that survives the attack.

The game ends when either Alien is defeated or all zombies are defeated. Alien and Zombies will take turns to move. Once a Zombie is defeated, its turn is skipped.

There are different objects that can be interacted with in-game. There are arrows, represented by ^, v, <, and >, that can change the direction in which Alien is moving. The direction of these arrows can be changed using the "arrow" command.

There are health packs, represented by h, which replenish Alien's health.

There are pods, represented by p, which instantly inflict 10 damage to the closest Zombie when hit by Alien.

There are rocks, represented by r, which hide a random game object (arrow, health, or pod) beneath it that are revealed when the rock is hit by Alien.

There is also the additional object bomb, represented by b, which explodes when either Alien or Zombie steps on it. The bomb will inflict 10 damage to any characters within a 1 unit radius, as well as destroy all objects in a 1 unit radius. The exception is rock (r), which will simply break to reveal an object underneath.

## Progress Log

- [Part 1](PART1.md)
- [Part 2](PART2.md)

## Contributors

Please replace the following with your group members' names. 

- Ashley Sim Ci Hui
- Chin Shuang Ying
