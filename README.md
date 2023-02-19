# Alien vs. Zombie

Alien vs Zombie is a turn-based combat game in which the player controls Alien to defeat a group of Zombies. Prior to the game, the player can customize settings including game board dimensions and number of zombies. The player can also save a game into a file and load a game from a file.

You may add one signature screenshot of your program here or above the title. Check out [this tutorial](https://www.digitalocean.com/community/tutorials/markdown-markdown-images) to learn how to do it.

[Video Demo](https://www.youtube.com/watch?v=05fASRKdF6k).

## Compilation Instructions

g++ pf\\*.cpp main.cpp

## User Manual

The user will control Alien, represented by A. The goal of the game is to maneuver around the board with the help of arrow objects to eliminate the Zombies, represented by unique numbers from 1-9. The user can control Alien's movements by typing either up, down, left, or right into the command line. Alien will inflict damage to Zombies when it collides with them. Alien will stop moving when it hits a rock, border, or hits a Zombie that survives the attack. The game ends when either Alien is defeated or all zombies are defeated. Alien and Zombies will take turns to move. Once a Zombie is defeated, its turn is skipped. 

There are different objects that can be interacted with in-game. There are arrows, represented by ^, v, <, and >, that can change the direction in which Alien is moving. There are health packs, represented by h, which replenish Alien's health. There are pods, represented by p, which instantly inflict 10 damage to the closest Zombie when hit by Alien. There are rocks, represented by r, which hide a random game object (arrow, health, or pod) beneath it that are revealed when the rock is hit by Alien. There are bombs, represented by b, which instantly inflict 10 damage to both Alien and Zombies if they are within a 1 unit radius of the bomb. When the bomb explodes, it will also destroy all nearby game objects within a 1 unit radius except for rock, which only breaks to reveal an object underneath.

Please DO NOT change the Progress Log below. Leave it as it is.

## Progress Log

- [Part 1](PART1.md)
- [Part 2](PART2.md)

## Contributors

Please replace the following with your group members' names. 

- Ashley Sim Ci Hui
- Chin Shuang Ying


