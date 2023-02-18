// ********************************************************* 
// Course: TCP1101 PROGRAMMING FUNDAMENTALS 
// Year: Trimester 1, 2022/23 (T2215) 
// Lab: TT8L 
// Names:   ASHLEY SIM CI HUI               | CHIN SHUANG YING 
// IDs:     1211101022                      | 1211102285
// Emails:  1211101022@student.mmu.edu.my   | 1211102285@student.mmu.edu.my
// Phones:  0149322912                      | 0166703743
// ********************************************************* 

#include "pf/helper.h"
#include <iostream>
#include <cstdlib> // for system()
#include <iomanip> // for setw()
#include <vector>
#include <string>
using namespace std;

//                                      //
//              BOARD code              //
//                                      //

class Board
{
private:
    vector<vector<char>> map_;
    int dimX_, dimY_; 

public:
    //default: 5 rows, 9 columns
    Board(int dimX = 9, int dimY = 5);

    void init(int dimX, int dimY);
    void updateBoard();
    void display() const;
    int getDimX() const;
    int getDimY() const;
    char getObject(int x, int y) const;
    void setObject(int x, int y, char ch);
    bool isEmpty(int x, int y) const;
    bool isInsideMap(int x, int y) const;
};

//initializes the board
Board::Board(int dimX, int dimY) {
    init(dimX, dimY);
}

//creates the board and resizes it
void Board::init(int dimX, int dimY) {
    dimX_ = dimX;
    dimY_ = dimY;

    // ^ - up
    // V - down
    // < - left
    // > - right
    // h - health
    // p - pod
    // r - rock
    char objects[] = {' ', ' ', ' ', '^', 'v', '<', '>', 'h', 'p', 'r'};
    int noOfObjects = 10; // number of objects in the objects array

    // create dynamic 2D array using vector
    map_.resize(dimY_); // create empty rows
    for (int i = 0; i < dimY_; ++i)
    {
        map_[i].resize(dimX_); // resize each row
    }

    // put random characters into the vector array
    for (int i = 0; i < dimY_; ++i)
    {
        for (int j = 0; j < dimX_; ++j)
        {
            int objNo = rand() % noOfObjects;
            map_[i][j] = objects[objNo];
        }
    }
}

//displays board itself for gameplay
void Board::display() const
{
    // comment this out during testing
    // system("cls"); // OR system("clear"); for Linux / MacOS
    system("cls");

    if (dimX_ >= 9)
    {
        for (int i = 0; i < ((dimX_ * 2 + 2) / 2 - 9); ++i)
        {
            cout << " ";
        }

        cout << ".: Alien vs Zombie :.";

        for (int i = 0; i < ((dimX_ * 2 + 2) / 2 - 10); ++i)
        {
            cout << " ";
        }
    }
    else if (dimX_ < 9)
    {
        cout << ".: Alien vs Zombie :.";
    }

    cout << endl;

    // for each row
    for (int i = 0; i < dimY_; ++i)
    {
        // display upper border of the row
        cout << "  ";
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "+-";
        }
        cout << "+" << endl;

        // display row number
        cout << setw(2) << (dimY_ - i);

        // display cell content and border of each column
        for (int j = 0; j < dimX_; ++j)
        {
            cout << "|" << map_[i][j];
        }
        cout << "|" << endl;
    }

    // display lower border of the last row
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << "+-";
    }
    cout << "+" << endl;

    // display column number
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        int digit = (j + 1) / 10;
        cout << " ";
        if (digit == 0)
            cout << " ";
        else
            cout << digit;
    }
    cout << endl;
    cout << "  ";
    for (int j = 0; j < dimX_; ++j)
    {
        cout << " " << (j + 1) % 10;
    }
    cout << endl
         << endl;
}

void Board::updateBoard() {
    int numRows {};
    int numColumns {};

    cout << "Board Settings" << endl;
    cout << "--------------" << endl;
    
    //ask user for custom rows and columns
    while (true) {
        cout << "Enter rows => ";
        cin >> numRows;

        //checks if num of rows is odd
        if ((numRows % 2) != 0)
            break;
        else {
            cout << "Number of rows must be odd." << endl;
            continue;
        }
    }

    while (true) {
        cout << "Enter columns => ";
        cin >> numColumns;

        if ((numColumns % 2) != 0)
            break;
        else
        {
            cout << "Number of columns must be odd." << endl;
            continue;
        }
    }

    dimX_ = numColumns;
    dimY_ = numRows;

    init(numColumns, numRows);
}

int Board::getDimX() const {
    return dimX_;
}

int Board::getDimY() const {
    return dimY_;
}

char Board::getObject(int x, int y) const {
    return map_[dimY_ - y][x - 1];
}

void Board::setObject(int x, int y, char ch) {
    map_[dimY_ - y][x - 1] = ch;
}

//checks if a specific coordinate is empty or not
bool Board::isEmpty(int x, int y) const {
    return map_[dimY_ - y][x-1] == ' ';
}

//checks if a specific coordinate is within the board range (?)
bool Board::isInsideMap(int x, int y) const {
    if ((0 < x) && (x <= dimX_) && (0 < y) && (y <= dimY_))
        return true;
    else
        return false;
}

//                                      //
//             ZOMBIE code              //
//                                      //

class Zombie
{
private:
    int x_, y_; // coordinates
    int life_, atk_, range_; // stats
    string direction_;

public:
    Zombie(int life = 100, int atk = 5, int range = 1);

    void init(int x, int y, int life, int atk, int range, string dir);
    int getX();
    int getY();
    int getLife();
    int getAtk();
    int getRange();
    string getDir();

    void decreaseLife(int life);
    
    void move(Board&board, string dir, int index);
    void changeDir(string dir);

    void displayStats();
    void spawnZombie(Board &board, char index);
};

Zombie::Zombie(int life, int atk, int range) {
}

void Zombie::init(int x, int y, int life, int atk, int range, string dir) {
    x_ = x;
    y_ = y;
    life_ = life;
    atk_ = atk;
    range_ = range;
    direction_ = dir;
}

int Zombie::getX() {
    return x_;
}

int Zombie::getY() {
    return y_;
}

int Zombie::getLife() {
    return life_;
}

int Zombie::getAtk() {
    return atk_;
}

int Zombie::getRange() {
    return range_;
}

string Zombie::getDir() {
    return direction_;
}

void Zombie::decreaseLife(int life) {
    life_ -= life;
}

void Zombie::move(Board &board, string dir, int index) {
    x_ = getX();
    y_ = getY();
    board.setObject(x_, y_, ' ');

    direction_ = dir;
    
    if (direction_ == "up")
        y_ += 1;
    else if (direction_ == "down")
        y_ -= 1;
    else if (direction_ == "left")
        x_ -= 1;
    else if (direction_ == "right")
        x_ += 1;

    char zomb = index + 49;
    board.setObject(x_, y_, zomb);
}

void Zombie::changeDir(string dir) {
    direction_ = dir;
}

void Zombie::displayStats() {
    cout << "Life " << life_ << ", Attack " << atk_ << ", Range " << range_ << endl;
}

void Zombie::spawnZombie(Board &board, char index) {
    // x_ = rand() % (board.getDimX()) + 1;
    // y_ = rand() % (board.getDimY()) + 1;
    board.setObject(x_, y_, index);
}

//                                      //
//              ALIEN code              //
//                                      //

class Alien
{
private:
    int x_, y_;
    int life_, atk_;
    string direction_;

public:
    Alien(int life = 100, int atk = 0);

    void init(int x, int y, int life, int atk, string dir);

    int getX();
    int getY();
    int getLife();
    int getAtk();
    string getDir();

    void increaseLife(int life);
    void decreaseLife(int life);
    void increaseAtk(int atk);
    
    void move(Board &board, string dir);
    void changeDir(string dir);

    void displayStats();
    void spawnAlien(Board &board);
};

Alien::Alien(int life, int atk) {
}

void Alien::init(int x, int y, int life, int atk, string dir) {
    x_ = x;
    y_ = y;
    life_ = life;
    atk_ = atk;
    direction_ = dir;
}

int Alien::getX() {
    return x_;
}

int Alien::getY() {
    return y_;
}

int Alien::getLife() {
    return life_;
}

int Alien::getAtk() {
    return atk_;
}

string Alien::getDir() {
    return direction_;
}

void Alien::increaseLife(int life) {
    life_ += life;
}

void Alien::decreaseLife(int life) {
    life_ -= life;
}

void Alien::increaseAtk(int atk) {
    atk_ += atk;
}

void Alien::move(Board &board, string dir) {
    x_ = getX();
    y_ = getY();
    board.setObject(x_, y_, '.');

    direction_ = dir;
    
    if (direction_ == "up")
        y_ += 1;
    else if (direction_ == "down")
        y_ -= 1;
    else if (direction_ == "left")
        x_ -= 1;
    else if (direction_ == "right")
        x_ += 1;

    board.setObject(x_, y_, 'A');
}

void Alien::changeDir(string dir) {
    direction_ = dir;
}

void Alien::displayStats() {
    cout << "Alien    : Life " << life_ << ", Attack " << atk_ << endl;
}

void Alien::spawnAlien(Board &board) {
    board.setObject(x_, y_, 'A');
}

//                                      //
//              MAIN code               //
//                                      //

int boardSetX() {
    int numColumns;
    
    //ask user for custom rows and columns
    while (true) {
        cout << "Enter columns => ";
        cin >> numColumns;

        if ((numColumns % 2) != 0)
            break;
        else
        {
            cout << "Number of columns must be odd." << endl;
            continue;
        }
    }

    cout << endl;

    return numColumns;
}

int boardSetY() {
    int numRows;

    cout << "Board Settings" << endl;
    cout << "--------------" << endl;

    while (true) {
        cout << "Enter rows => ";
        cin >> numRows;

        //checks if num of rows is odd
        if ((numRows % 2) != 0)
            break;
        else {
            cout << "Number of rows must be odd." << endl;
            continue;
        }
    }

    return numRows;
}

int zombSettings() {
    int numZombies {};

    cout << "Zombie Settings" << endl;
    cout << "---------------" << endl;

    while (true)
    {
        cout << "Enter number of zombies => ";
        cin >> numZombies;

        if (numZombies < 1 || numZombies > 9)
        {
            cout << "Number of zombies must be between 1 to 9." << endl;
            continue;
        }
        else
            break;
    }

    cout << endl << endl;

    // totalZomb = numZombies;

    cout << "Settings Updated." << endl;
    pf::Pause();
    return numZombies;
}

bool gameSettings() {
    cout << "Default Game Settings" << endl;
    cout << "---------------------" << endl;
    cout << "Board Rows     : 5" << endl;
    cout << "Board Columns  : 9" << endl;
    cout << "Zombie Count   : 1" << endl << endl;
    
    while(true) {
        char confirmChange {};
        cout << "Do you wish to change the game settings (y/n)? => ";
        cin >> confirmChange;

        if (confirmChange == 'y') 
            return true;
        else if (confirmChange == 'n')
            return false;
        else {
            cout << "Invalid input. Please enter y/n." << endl;
            continue;
        }
    }
}

void encounterZombie(Board &board, vector<Zombie> &zombies, Alien &alien, char object) {
    int zombIndex = object - 49;
    if (zombies[zombIndex].getLife() > 0) {
        cout << "Alien attacks Zombie " << zombIndex + 1 << "." << endl;

        if (zombies[zombIndex].getLife() > alien.getAtk()) {
            zombies[zombIndex].decreaseLife(alien.getAtk());
            cout << "Zombie " << zombIndex + 1 << " receives a damage of " << alien.getAtk() << "." << endl;
        }
        else {
            int remainingLife = zombies[zombIndex].getLife();
            zombies[zombIndex].decreaseLife(remainingLife);
            cout << "Zombie " << zombIndex + 1 << " receives a damage of " << remainingLife << "." << endl;
        }
            
        if (zombies[zombIndex].getLife() > 0)
            cout << "Zombie " << zombIndex + 1 << " is still alive." << endl;
        else {
            cout << "Zombie " << zombIndex + 1 << " is defeated." << endl;
            board.setObject(zombies[zombIndex].getX(), zombies[zombIndex].getY(), ' ');
            }
        }
}

void encounterPod(Board &board, vector<Zombie> &zombies, int podX, int podY) {
    int distanceFromPod[zombies.size()];

    for (int i = 0; i < zombies.size(); i++) {
        distanceFromPod[i] = abs(zombies[i].getX() - podX) + abs(zombies[i].getY() - podY);
    }

    int smallestDistance = 100;
    int smallestIndex = 0;

    for (int i = 0; i < zombies.size(); i++) {
        if (distanceFromPod[i] < smallestDistance) {
            smallestDistance = distanceFromPod[i];
            smallestIndex = i;
        }
        else
            continue;
    }

    zombies[smallestIndex].decreaseLife(10);

    cout << "Zombie " << smallestIndex + 1 << " receives a damage of 10." << endl;
    
    if (zombies[smallestIndex].getLife() > 0)
        cout << "Zombie " << smallestIndex + 1 << " is still alive." << endl;
    else {
        cout << "Zombie " << smallestIndex + 1 << " is defeated." << endl;
        board.setObject(zombies[smallestIndex].getX(), zombies[smallestIndex].getY(), ' ');
    }
}

void reportObject (Alien &alien, char obj) {
    switch (obj)
    {
    case ' ':
        cout << "Alien finds an empty space." << endl << endl;
        break;

    case 'h':
        cout << "Alien finds a health pack." << endl;
        cout << "Alien's life is increased by 20." << endl << endl;
        alien.increaseLife(20);
        break;

    case 'p':
        cout << "Alien finds a pod." << endl << endl;
        // !! ADD !! code for pod to attack zombies
        break;

    case '.':
        cout << "Alien finds an empty space." << endl << endl;
        break;

    case '^':
        cout << "Alien finds an arrow." << endl << endl;
        break;

    case 'v':
        cout << "Alien finds an arrow." << endl << endl;
        break;

    case '<':
        cout << "Alien finds an arrow." << endl << endl;
        break;

    case '>':
        cout << "Alien finds an arrow." << endl << endl;
        break;

    case 'r':
        cout << "Alien stumbles upon a rock." << endl;
        break;
    }
}

void resetTrail(Board &board) {
    char objects[] = {' ', ' ', ' ', '^', 'v', '<', '>', 'h', 'p', 'r'};

    for (int i = 1; i <= board.getDimX(); i++) {
        for (int j = 1; j <= board.getDimY(); j++) {
            if (board.getObject(i, j) == '.') {
                int objIndex = rand() % sizeof(objects);
                board.setObject(i, j, objects[objIndex]);
            }
        }
    }
}

void commands(string cmd, Board &board, Alien &alien, vector<Zombie> &zombies, int totalZomb) {
    char objInFront;

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

                else if (objInFront == '^') {
                    cout << endl;
                    reportObject(alien, objInFront);

                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("up");
                    objInFront = board.getObject(alien.getX(), alien.getY() + 1);
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }
                else if (objInFront == 'v') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("down");
                    objInFront = board.getObject(alien.getX(), alien.getY() - 1);
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }
                else if (objInFront == '<') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("left");
                    objInFront = board.getObject(alien.getX() - 1, alien.getY());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }
                else if (objInFront == '>') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("right");
                    objInFront = board.getObject(alien.getX() + 1, alien.getY());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }

                else if (objInFront == 'r') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    char underRock[] = {' ', '^', 'v', '<', '>', 'h', 'p'};
                    char objUnderRock = underRock[rand() % 6];

                    board.setObject(alien.getX(), alien.getY() + 1, objUnderRock);

                    cout << "Alien discovers a";

                    switch (objUnderRock)
                    {
                    case ' ':
                        cout << "n empty space" << endl;
                        break;
                    
                    case '^':
                        cout << "n arrow";
                        break;
                        
                    case 'v':
                        cout << "n arrow";
                        break;

                    case '<':
                        cout << "n arrow";
                        break;
                        
                    case '>':
                        cout << "n arrow";
                        break;

                    case 'h':
                        cout << " health pack";
                        break;

                    case 'p':
                        cout << " a pod";
                        break;
                    }

                    cout <<  " beneath the rock." << endl;

                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    break;
                }
                else if (49 <= objInFront <= 58) {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    encounterZombie(board, zombies, alien, objInFront);

                    int zombIndex = objInFront - 49;
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    if (zombies[zombIndex].getLife() > 0)
                        break;
                    else if (zombies[zombIndex].getLife() == 0)
                        continue;
                }
            }
            if (board.isInsideMap(alien.getX(), alien.getY() + 1) == false)
                cout << "Alien has hit a border." << endl;
            break;
        }

        while (alien.getDir() == "down") {
            while (board.isInsideMap(alien.getX(), alien.getY() - 1) == true) {
                objInFront = board.getObject(alien.getX(), alien.getY() - 1);

                if (objInFront == ' ' || objInFront == 'h' ||
                    objInFront == 'p' || objInFront == '.') {
                    cout << endl;
                    reportObject(alien, objInFront);

                    if (objInFront == 'p') {
                        encounterPod(board, zombies, alien.getX(), alien.getY() - 1);
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

                else if (objInFront == '^') {
                    cout << endl;
                    reportObject(alien, objInFront);

                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("up");
                    objInFront = board.getObject(alien.getX(), alien.getY() + 1);
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }
                else if (objInFront == 'v') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("down");
                    objInFront = board.getObject(alien.getX(), alien.getY() - 1);
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }
                else if (objInFront == '<') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("left");
                    objInFront = board.getObject(alien.getX() - 1, alien.getY());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }
                else if (objInFront == '>') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("right");
                    objInFront = board.getObject(alien.getX() + 1, alien.getY());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }

                else if (objInFront == 'r') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    char underRock[] = {' ', '^', 'v', '<', '>', 'h', 'p'};
                    char objUnderRock = underRock[rand() % 6];

                    board.setObject(alien.getX(), alien.getY() - 1, objUnderRock);

                    cout << "Alien discovers a";

                    switch (objUnderRock)
                    {
                    case ' ':
                        cout << "n empty space" << endl;
                        break;
                    
                    case '^':
                        cout << "n arrow";
                        break;
                        
                    case 'v':
                        cout << "n arrow";
                        break;

                    case '<':
                        cout << "n arrow";
                        break;
                        
                    case '>':
                        cout << "n arrow";
                        break;

                    case 'h':
                        cout << " health pack";
                        break;

                    case 'p':
                        cout << " a pod";
                        break;
                    }

                    cout <<  " beneath the rock." << endl;

                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    break;
                }
                else if (49 <= objInFront <= 58) {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    encounterZombie(board, zombies, alien, objInFront);
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    break;
                }
            }
            if (board.isInsideMap(alien.getX(), alien.getY() - 1) == false)
                cout << "Alien has hit a border." << endl;
            break;
        }

        while (alien.getDir() == "left") {
            while (board.isInsideMap(alien.getX() - 1, alien.getY()) == true) {
                objInFront = board.getObject(alien.getX() - 1, alien.getY());

                if (objInFront == ' ' || objInFront == 'h' ||
                    objInFront == 'p' || objInFront == '.') {
                    cout << endl;
                    reportObject(alien, objInFront);

                    if (objInFront == 'p') {
                        encounterPod(board, zombies, alien.getX() - 1, alien.getY());
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

                else if (objInFront == '^') {
                    cout << endl;
                    reportObject(alien, objInFront);

                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("up");
                    objInFront = board.getObject(alien.getX(), alien.getY() + 1);
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }
                else if (objInFront == 'v') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("down");
                    objInFront = board.getObject(alien.getX(), alien.getY() - 1);
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }
                else if (objInFront == '<') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("left");
                    objInFront = board.getObject(alien.getX() - 1, alien.getY());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }
                else if (objInFront == '>') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("right");
                    objInFront = board.getObject(alien.getX() + 1, alien.getY());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }

                else if (objInFront == 'r') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    char underRock[] = {' ', '^', 'v', '<', '>', 'h', 'p'};
                    char objUnderRock = underRock[rand() % 6];

                    board.setObject(alien.getX() - 1, alien.getY(), objUnderRock);

                    cout << "Alien discovers a";

                    switch (objUnderRock)
                    {
                    case ' ':
                        cout << "n empty space" << endl;
                        break;
                    
                    case '^':
                        cout << "n arrow";
                        break;
                        
                    case 'v':
                        cout << "n arrow";
                        break;

                    case '<':
                        cout << "n arrow";
                        break;
                        
                    case '>':
                        cout << "n arrow";
                        break;

                    case 'h':
                        cout << " health pack";
                        break;

                    case 'p':
                        cout << " a pod";
                        break;
                    }

                    cout <<  " beneath the rock." << endl;

                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    break;
                }
                else if (49 <= objInFront <= 58) {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    encounterZombie(board, zombies, alien, objInFront);
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    break;
                }
            }
            if (board.isInsideMap(alien.getX() - 1, alien.getY()) == false)
                cout << "Alien has hit a border." << endl;
            break;
        }

        while (alien.getDir() == "right") {
            while (board.isInsideMap(alien.getX() + 1, alien.getY()) == true) {
                objInFront = board.getObject(alien.getX() + 1, alien.getY());

                if (objInFront == ' ' || objInFront == 'h' ||
                    objInFront == 'p' || objInFront == '.') {
                    cout << endl;
                    reportObject(alien, objInFront);

                    if (objInFront == 'p') {
                        encounterPod(board, zombies, alien.getX() + 1, alien.getY());
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

                else if (objInFront == '^') {
                    cout << endl;
                    reportObject(alien, objInFront);

                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("up");
                    objInFront = board.getObject(alien.getX(), alien.getY() + 1);
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }
                else if (objInFront == 'v') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("down");
                    objInFront = board.getObject(alien.getX(), alien.getY() - 1);
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }
                else if (objInFront == '<') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("left");
                    objInFront = board.getObject(alien.getX() - 1, alien.getY());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }
                else if (objInFront == '>') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    alien.move(board, alien.getDir());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    alien.changeDir("right");
                    objInFront = board.getObject(alien.getX() + 1, alien.getY());
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    continue;
                }

                else if (objInFront == 'r') {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    char underRock[] = {' ', '^', 'v', '<', '>', 'h', 'p'};
                    char objUnderRock = underRock[rand() % 6];

                    board.setObject(alien.getX() + 1, alien.getY(), objUnderRock);

                    cout << "Alien discovers a";

                    switch (objUnderRock)
                    {
                    case ' ':
                        cout << "n empty space" << endl;
                        break;
                    
                    case '^':
                        cout << "n arrow";
                        break;
                        
                    case 'v':
                        cout << "n arrow";
                        break;

                    case '<':
                        cout << "n arrow";
                        break;
                        
                    case '>':
                        cout << "n arrow";
                        break;

                    case 'h':
                        cout << " health pack";
                        break;

                    case 'p':
                        cout << " a pod";
                        break;
                    }

                    cout <<  " beneath the rock." << endl;

                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    break;
                }
                else if (49 <= objInFront <= 58) {
                    cout << endl;
                    reportObject(alien, objInFront);
                    
                    encounterZombie(board, zombies, alien, objInFront);
                    
                    pf::Pause();
                    board.display();
                    alien.displayStats();
                    for (int i = 0; i < totalZomb; i++) {
                        cout << "Zombie " << i + 1 << " : ";
                        zombies[i].displayStats();
                    }

                    break;
                }
            }
            if (board.isInsideMap(alien.getX() + 1, alien.getY()) == false)
                cout << "Alien has hit a border." << endl;
            break;
        }
    }

    else if (cmd == "arrow") {
        int arrowX, arrowY;
        char newArrow;
        string arrowDir;
        cout << "Enter row, column, and direction: ";
        cin >> arrowY >> arrowX >> arrowDir;

        // !! ADD !! exception for if arrow coordinates are more than the dimensions

        char objAtCoords = board.getObject(arrowX, arrowY);

        if (objAtCoords != '^' && objAtCoords != 'v' &&
            objAtCoords != '<' && objAtCoords != '>')
            cout << "The object at this coordinate is not an arrow." << endl;
        else {
            while (true) {
                if (arrowDir == "up") {
                    newArrow = '^';
                    break;
                    }
                else if (arrowDir == "down") {
                    newArrow = 'v';
                    break;
                }
                else if (arrowDir == "left") {
                    newArrow = '<';
                    break;
                }
                else if (arrowDir == "right") {
                    newArrow = '>';
                    break;
                }
                else {
                    cout << "Invalid input. Please type either up/down/left/right.";
                    continue;
                }
            }
            // change the arrow direction
            board.setObject(arrowX, arrowY, newArrow);
        }
        cout << "Arrow " << objAtCoords << " is switched to " << newArrow << "." << endl;
    }

    else if (cmd == "help") {
        cout << "up     - Alien to move up." << endl;
        cout << "down   - Alien to move down." << endl;
        cout << "left   - Alien to move left." << endl;
        cout << "right  - Alien to move right." << endl;
        cout << "arrow  - Switch the direction of an arrow object in the game board." << endl;
        cout << "help   - List and describe the commands that the player can use in the game." << endl;
        cout << "save   - Save the current game to a file." << endl;
        cout << "load   - Load a saved game from a file." << endl;
        cout << "quit   - Quit the game while still in play." << endl;
    }

    // !! ADD !! save function
    else if (cmd == "save") {

    }

    // !! ADD !! load function
    else if (cmd == "load") {

    }

    else if (cmd == "quit") {
        char confirmQuit;
        cout << "Are you sure? (y/n) => ";
        cin >> confirmQuit;

        while (true) {
            if (confirmQuit == 'y')
                exit(0);
            else if (confirmQuit == 'n')
                break;
            else {
                cout << "Please enter a valid command.";
                continue;
            }
        }
    }

    else {
        cout << "Please enter a valid command." << endl;
    }

    pf::Pause();
}

void zombieTurn(Board &board, Alien &alien, vector<Zombie> &zombies, int totalZomb, int turn) {
    for (int i = 0; i < totalZomb; i++) {
        if (i == turn)
            cout << "-> ";
        else
            cout << "   ";

        cout << "Zombie " << i + 1 << " : ";
        zombies[i].displayStats();
    }
    cout << endl;

    string dir[4] = {"up", "down", "left", "right"};
    bool validDir = false;

    int zombX = zombies[turn].getX();
    int zombY = zombies[turn].getY();

    while (validDir == false) {
        zombies[turn].changeDir(dir[rand() % 4]);

        if (zombies[turn].getDir() == "up")
            zombY += 1;
        else if (zombies[turn].getDir() == "down")
            zombY -= 1;
        else if (zombies[turn].getDir() == "left")
            zombX -= 1;
        else if (zombies[turn].getDir() == "right")
            zombX += 1;

        // !! ADD !! make zombie avoid other zombies
        if (board.isInsideMap(zombX, zombY) == true &&
            board.getObject(zombX, zombY) != 'A') {
            validDir = true;
            break;
        }
        else
            continue;
    }

    zombies[turn].move(board, zombies[turn].getDir(), turn);
    
    cout << "Zombie " << turn + 1 << " moves " << zombies[turn].getDir() << "." << endl;

    pf::Pause();

    board.display();

    cout << "   ";
    alien.displayStats();

    for (int i = 0; i < totalZomb; i++) {
        if (i == turn)
            cout << "-> ";
        else
            cout << "   ";

        cout << "Zombie " << i + 1 << " : ";
        zombies[i].displayStats();
    }
    cout << endl;

    int alienDistance = abs(alien.getX() - zombies[turn].getX()) +
                        abs(alien.getY() - zombies[turn].getY());

    if (alienDistance <= zombies[turn].getRange()) {
        alien.decreaseLife(zombies[turn].getAtk());
        cout << "Zombie " << turn + 1 << " attacks Alien." << endl;
        cout << "Alien receives a damage of " << zombies[turn].getAtk() << "." << endl << endl;
    }
    else {
        cout << "Zombie " << turn + 1 << " is unable to attack Alien." << endl;
        cout << "Alien is too far." << endl << endl;
    }
    pf::Pause();

    board.display();

    cout << "   ";
    alien.displayStats();

    for (int i = 0; i < totalZomb; i++) {
        if (i == turn)
            cout << "-> ";
        else
            cout << "   ";

        cout << "Zombie " << i + 1 << " : ";
        zombies[i].displayStats();
    }
    cout << endl;
    
    cout << "Zombie " << turn + 1 << "'s turn ends." << endl << endl;
    pf::Pause();
}

int main()
{
    // cout << "Assignment (Part 1)" << endl;
    // cout << "Let's Get Started!" << endl;
    // pf::Pause();

    Board board;

    int totalZomb = 1;

    if (gameSettings() == true) {
        board.init(boardSetX(), boardSetY());
        totalZomb = zombSettings();
    }

    vector<Zombie> zombies;

    for (int i = 0; i < totalZomb; i++) {
        //randomize values
        int x     = rand() % (board.getDimY()) + 1;
        int y     = rand() % (board.getDimY()) + 1;
        int life  = 100 + (rand() % (150 - 100 + 1));
        int atk   = 5 + (rand() % (15 - 5 + 1));
        int range = 1 + (rand() % (3 - 1 + 1));

        Zombie zombie;
        zombie.init(x, y, life, atk, range, "up");
        zombies.push_back(zombie);
    }

    //49 is the ascii value for '1'
    for (int i = 0; i < totalZomb; i++) {
        char zombNumb = i + 49;
        zombies[i].spawnZombie(board, zombNumb);
    }

    Alien alien;

    int alienX = (board.getDimX() + 1) / 2;
    int alienY = (board.getDimY() + 1) / 2;
    int alienLife = 100 + (rand() % (150 - 100 + 1));

    alien.init(alienX, alienY, alienLife, 20, "up");
    alien.spawnAlien(board);

    while (true) {
        board.display();

        cout << "-> ";
        alien.displayStats();

        for (int i = 0; i < totalZomb; i++) {
            cout << "   ";
            cout << "Zombie " << i + 1 << " : ";
            zombies[i].displayStats();
        }

        cout << endl;

        cout << alien.getX() << ", " << alien.getY() << endl;
        cout << alien.getDir() << endl;

        while (true) {
        string cmd;
        cout << "<command> ";
        cin >> cmd;

        if (cmd == "arrow" || cmd == "help" || cmd == "save" ||
            cmd == "load" || cmd == "quit") {
            commands(cmd, board, alien, zombies, totalZomb);

            board.display();

            cout << "-> ";
            alien.displayStats();

            for (int i = 0; i < totalZomb; i++) {
                cout << "   ";
                cout << "Zombie " << i + 1 << " : ";
                zombies[i].displayStats();
            }

            cout << endl;

            continue;
            }
        else { //starts alien's turn
            commands(cmd, board, alien, zombies, totalZomb);
            break;
        }

        }

        resetTrail(board);

        board.display();

        cout << "-> ";
        alien.displayStats();

        for (int i = 0; i < totalZomb; i++) {
            cout << "   ";
            cout << "Zombie " << i + 1 << " : ";
            zombies[i].displayStats();
        }
        cout << endl;

        cout << "Alien's turn ends. The trail has been reset." << endl << endl;

        pf::Pause();

        for (int i = 0; i < totalZomb; i++) {
            board.display();

            cout << "   ";
            alien.displayStats();

            zombieTurn(board, alien, zombies, totalZomb, i);
        }
    }

    cout << "Game Over!" << endl;
}
