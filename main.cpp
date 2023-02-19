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
#include <fstream>
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
    char objects[] = {' ', ' ', '^', 'v', '<', '>', 'h', 'p', 'r', 'b'};
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
    void changeX(int x);
    void changeY(int y);
    void changeDir(string dir);

    bool withinBorders(Board &board);
    char getObjInFront(Board &board);
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

void Zombie::changeX(int x) {
    x_ = x;
}

void Zombie::changeY(int y) {
    y_ = y;
}

void Zombie::changeDir(string dir) {
    direction_ = dir;
}

// returns true if space in front of zombie is within the map borders
// returns false if space in front of zombie is not within map borders
bool Zombie::withinBorders(Board &board) {
    if (direction_ == "up")
        return board.isInsideMap(x_, y_ + 1);
    else if (direction_ == "down")
        return board.isInsideMap(x_, y_ - 1);
    else if (direction_ == "left")
        return board.isInsideMap(x_ - 1, y_);
    else if (direction_ == "right")
        return board.isInsideMap(x_ + 1, y_);

    return 0;
}

char Zombie::getObjInFront(Board &board) {
    if (direction_ == "up")
        return board.getObject(x_, y_ + 1);
    else if (direction_ == "down")
        return board.getObject(x_, y_ - 1);
    else if (direction_ == "left")
        return board.getObject(x_ - 1, y_);
    else if (direction_ == "right")
        return board.getObject(x_ + 1, y_);

    return 0;
}

void Zombie::displayStats() {
    cout << "Life " << life_ << ", Attack " << atk_ << ", Range " << range_ << endl;
}

void Zombie::spawnZombie(Board &board, char index) {
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
    void decreaseAtk(int atk);
    
    void move(Board &board, string dir);
    void changeDir(string dir);

    bool withinBorders(Board &board);
    char getObjInFront(Board &board);
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

void Alien::decreaseAtk(int atk) {
    atk_ -= atk;
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

// returns true if space in front of alien is within the map borders
// returns false if space in front of alien is not within map borders
bool Alien::withinBorders(Board &board) {
    if (direction_ == "up")
        return board.isInsideMap(x_, y_ + 1);
    else if (direction_ == "down")
        return board.isInsideMap(x_, y_ - 1);
    else if (direction_ == "left")
        return board.isInsideMap(x_ - 1, y_);
    else if (direction_ == "right")
        return board.isInsideMap(x_ + 1, y_);

    return 0;
}

char Alien::getObjInFront (Board &board) {
    if (direction_ == "up")
        return board.getObject(x_, y_ + 1);
    else if (direction_ == "down")
        return board.getObject(x_, y_ - 1);
    else if (direction_ == "left")
        return board.getObject(x_ - 1, y_);
    else if (direction_ == "right")
        return board.getObject(x_ + 1, y_);

    return 0;
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

void displayAllStats(Board &board, Alien&alien, vector<Zombie> &zombies, int totalZomb) {
    board.display();

    cout << "-> ";
    alien.displayStats();
    for (int i = 0; i < totalZomb; i++) {
        cout << "   ";
        cout << "Zombie " << i + 1 << " : ";
        zombies[i].displayStats();
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

//switches alien's direction based on arrow direction
void encounterArrow(Board &board, Alien&alien, vector<Zombie> zombies, int totalZomb, char object) {
    alien.increaseAtk(20);
    alien.move(board, alien.getDir());

    pf::Pause();
    displayAllStats(board, alien, zombies, totalZomb);
    
    switch (object)
    {
    case '^':
        alien.changeDir("up");
        break;

    case 'v':
        alien.changeDir("down");
        break;

    case '<':
        alien.changeDir("left");
        break;
        
    case '>':
        alien.changeDir("right");
        break;
    }
}

void encounterPod(Board &board, vector<Zombie> &zombies, Alien alien, int totalZomb) {
    int podX = alien.getX();
    int podY = alien.getY();
    
    int distanceFromPod;
    int smallestDistance = 100;
    int smallestIndex = 0;

    for (int i = 0; i < totalZomb; i++) {
        distanceFromPod = abs(zombies[i].getX() - podX) + abs(zombies[i].getY() - podY);

        if (distanceFromPod < smallestDistance) {
            smallestDistance = distanceFromPod;
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

void encounterRock(Board &board, Alien &alien) {
    string alienDir = alien.getDir();

    char underRock[] = {' ', '^', 'v', '<', '>', 'h', 'p', 'b'};
    char objUnderRock = underRock[rand() % 7];

    int rockX = alien.getX();
    int rockY = alien.getY();

    if (alienDir == "up")
        rockY += 1;
    else if (alienDir == "down")
        rockY -= 1;
    else if (alienDir == "left")
        rockX -= 1;
    else if (alienDir == "right")
        rockX += 1;

    board.setObject(rockX, rockY, objUnderRock);

    cout << "Alien discovers a";

    switch (objUnderRock)
    {
    case ' ':
        cout << "n empty space";
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
        cout << " pod";
        break;

    case 'b':
        cout << " bomb";
        break;
    }

    cout <<  " beneath the rock." << endl;
}

void encounterBomb(Board &board, vector<Zombie> &zombies, Alien alien, int zombIndex, string trigger) {
    int bombX, bombY;

    if (trigger == "alien") {
        bombX = alien.getX();
        bombY = alien.getY();
    }
    else if (trigger == "zombie") {
        bombX = zombies[zombIndex].getX();
        bombY = zombies[zombIndex].getY();
    }

    for (int i = bombX - 1; i < bombX + 2; i++) {
        for (int j = bombY - 1; j < bombY + 2; j++) {
            if (board.isInsideMap(i, j) == false)
                continue;

            switch (board.getObject(i, j))
            {
            case 'A':
                alien.decreaseLife(10);
                cout << "Alien takes 10 damage." << endl;
                continue;

            case '1':
                zombies[0].decreaseLife(10);
                cout << "Zombie 1 takes 10 damage." << endl;
                continue;
            case '2':
                zombies[1].decreaseLife(10);
                cout << "Zombie 2 takes 10 damage." << endl;
                continue;
            case '3':
                zombies[2].decreaseLife(10);
                cout << "Zombie 3 takes 10 damage." << endl;
                continue;
            case '4':
                zombies[3].decreaseLife(10);
                cout << "Zombie 4 takes 10 damage." << endl;
                continue;
            case '5':
                zombies[4].decreaseLife(10);
                cout << "Zombie 5 takes 10 damage." << endl;
                continue;
            case '6':
                zombies[5].decreaseLife(10);
                cout << "Zombie 6 takes 10 damage." << endl;
                continue;
            case '7':
                zombies[6].decreaseLife(10);
                cout << "Zombie 7 takes 10 damage." << endl;
                continue;
            case '8':
                zombies[7].decreaseLife(10);
                cout << "Zombie 8 takes 10 damage." << endl;
                continue;
            case '9':
                zombies[8].decreaseLife(10);
                cout << "Zombie 9 takes 10 damage." << endl;
                continue;

            case '^':
                board.setObject(i, j, ' ');
                continue;
            case 'v':
                board.setObject(i, j, ' ');
                continue;
            case '<':
                board.setObject(i, j, ' ');
                continue;
            case '>':
                board.setObject(i, j, ' ');
                continue;
            case 'h':
                board.setObject(i, j, ' ');
                continue;
            case 'p':
                board.setObject(i, j, ' ');
                continue;

            case 'r': {
                char underRock[] = {' ', '^', 'v', '<', '>', 'h', 'p', 'b'};
                char objUnderRock = underRock[rand() % 7];
                board.setObject(i, j, objUnderRock);

                cout << "A rock was blown up." << endl;
                cout << "A";

                switch (objUnderRock)
                {
                case ' ':
                    cout << "n empty space";
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
                    cout << " pod";
                    break;

                case 'b':
                    cout << " bomb";
                    break;
                }
                cout <<  " was discovered beneath the rock." << endl;
                continue;
            }
            default:
                continue;
            }
        }
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

    case 'b':
        cout << "Alien finds a bomb." << endl;
        break;
    }
}

void resetTrail(Board &board) {
    char objects[] = {' ', ' ', '^', 'v', '<', '>', 'h', 'p', 'r', 'b'};

    for (int i = 1; i <= board.getDimX(); i++) {
        for (int j = 1; j <= board.getDimY(); j++) {
            if (board.getObject(i, j) == '.') {
                int objIndex = rand() % sizeof(objects);
                board.setObject(i, j, objects[objIndex]);
            }
        }
    }
}

void saveFile(Board &board, Alien &alien, vector<Zombie> &zombies, int totalZomb) {
    string saveFile;

    cout << "Enter the file name to save the current game: ";
    cin >> saveFile;
    
    ofstream fout(saveFile);

    // board dimensions
    fout << board.getDimX() << ' '
         << board.getDimY() << endl;

    // items in each coordinate
    // saved bottom to top, left to right
    for (int i = 1; i <= board.getDimX(); i++) {
        for (int j = 1; j <= board.getDimY(); j++) {
            fout << board.getObject(i, j) << endl;
        }
    }

    // alien stats
    fout << alien.getLife() << ' '
         << alien.getAtk() << ' '
         << alien.getDir() << endl;

    // zombie stats
    // saved zombie by zombie,
    // ex. zombie1's x y life atk range
    //          then only
    //     zombie2's x y life atk range
    for (int i = 0; i < totalZomb; i++) {
        fout << zombies[i].getX() << ' '
             << zombies[i].getY() << ' '
             << zombies[i].getLife() << ' '
             << zombies[i].getAtk() << ' '
             << zombies[i].getRange() << ' '
             << zombies[i].getDir() << endl;
    }

    fout.close();

    cout << "Game Saved" << endl;
}

void loadFile(Board &board, Alien&alien, vector<Zombie> &zombies, int totalZomb) {
    char confirmSave;

    cout << "Do you want to save the current game (y/n)? => ";
    cin >> confirmSave;

    if (confirmSave == 'y')
        saveFile(board, alien, zombies, totalZomb);
    
    string loadFile;
    cout << "Enter the file name to load: ";
    cin >> loadFile;

    ifstream fin(loadFile);

    if (fin.is_open()) {
        while (fin.good()) {
            // reads board dimensions
            int dimX, dimY;
            fin >> dimX >> dimY;
            board.init(dimX, dimY);

            // !! FIX !! can't read blank spaces
            // reads object in each coordinate
            for (int i = 1; i <= dimX; i++) {
                for (int j = 1; j <= dimY; j++) {
                    char obj;
                    fin >> obj;
                    board.setObject(i, j, obj);
                }
            }

            int alienLife, alienAtk, alienDir;
            fin >> alienLife >> alienAtk >> alienDir;

            int zombX, zombY, zombLife, zombAtk, zombRange;
            string zombDir;
            for (int i = 0; i < totalZomb; i++) {
                fin >> zombX >> zombY >> zombLife >> zombAtk >> zombRange;
                getline(fin, zombDir, '$');

                Zombie zombie;
                zombie.init(zombX, zombY, zombLife, zombAtk, zombRange, zombDir);
                zombies.push_back(zombie);
            }
        }
    }
    else
        cout << "Failed to open file." << endl;

    fin.close();
}

void commands(string cmd, Board &board, Alien &alien, vector<Zombie> &zombies, int totalZomb) {
    char objInFront;

    if (cmd == "up" || cmd == "down" || cmd == "left" || cmd == "right") {
        alien.changeDir(cmd);

        while (alien.withinBorders(board)) {
            cout << endl;
            reportObject(alien, alien.getObjInFront(board));

            if (alien.getObjInFront(board) == 'h' ||
                alien.getObjInFront(board) == ' ' ||
                alien.getObjInFront(board) == '.') { 

                alien.move(board, alien.getDir());
                pf::Pause();
                displayAllStats(board, alien, zombies, totalZomb);
                continue;
            }

            else if (alien.getObjInFront(board) == '^' ||
                     alien.getObjInFront(board) == 'v' ||
                     alien.getObjInFront(board) == '<' ||
                     alien.getObjInFront(board) == '>') {

                encounterArrow(board, alien, zombies, totalZomb, alien.getObjInFront(board));
                continue;
            }

            else if (alien.getObjInFront(board) == 'p') {
                alien.move(board, alien.getDir());
                encounterPod(board, zombies, alien, totalZomb);

                pf::Pause();
                displayAllStats(board, alien, zombies, totalZomb);
                continue;
            }

            else if (alien.getObjInFront(board) == 'r') {
                encounterRock(board, alien);
                break;
            }

            else if (alien.getObjInFront(board) == 'b') {
                alien.move(board, alien.getDir());
                encounterBomb(board, zombies, alien, 0, "alien");

                pf::Pause();
                displayAllStats(board, alien, zombies, totalZomb);
                continue;
            }

            else if (alien.getObjInFront(board) == '1' ||
                     alien.getObjInFront(board) == '2' ||
                     alien.getObjInFront(board) == '3' ||
                     alien.getObjInFront(board) == '4' ||
                     alien.getObjInFront(board) == '5' ||
                     alien.getObjInFront(board) == '6' ||
                     alien.getObjInFront(board) == '7' ||
                     alien.getObjInFront(board) == '8' ||
                     alien.getObjInFront(board) == '9') {
                encounterZombie(board, zombies, alien, alien.getObjInFront(board));

                int zombIndex = alien.getObjInFront(board) - 49;

                pf::Pause();
                displayAllStats(board, alien, zombies, totalZomb);

                if (zombies[zombIndex].getLife() > 0)
                    break;
                else if (zombies[zombIndex].getLife() == 0)
                    continue;
            }
            pf::Pause();
            displayAllStats(board, alien, zombies, totalZomb);
        }
        if (!alien.withinBorders(board))
            cout << endl << "Alien has hit a border." << endl;
    }

    else if (cmd == "arrow") {
        int arrowX, arrowY;
        char newArrow;
        char objAtCoords;
        string arrowDir;

        while (true) {
            cout << "Enter row, column, and direction: ";
            cin >> arrowY >> arrowX >> arrowDir;

            if (arrowX < 1 || arrowX > board.getDimX() ||
                arrowY < 1 || arrowY > board.getDimY()) {
                cout << "Invalid row and column. Please enter valid coordinates." << endl;
                continue;
            }

            objAtCoords = board.getObject(arrowX, arrowY);

            if (objAtCoords != '^' && objAtCoords != 'v' &&
                objAtCoords != '<' && objAtCoords != '>')
                cout << "The object at this coordinate is not an arrow." << endl;
            else {
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
                    cout << "Invalid input. Please type either up/down/left/right." << endl;
                    continue;
                }
            }
        }
        // change the arrow direction
        board.setObject(arrowX, arrowY, newArrow);

        cout << "Arrow " << objAtCoords << " is switched to " << newArrow << "." << endl;
        pf::Pause();
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
        pf::Pause();
    }

    // !! ADD !! save function
    else if (cmd == "save") {
        saveFile(board, alien, zombies, totalZomb);
    }

    // !! ADD !! load function
    else if (cmd == "load") {
        loadFile(board, alien, zombies, totalZomb);
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
                pf::Pause();
                continue;
            }
        }
    }

    else {
        cout << "Please enter a valid command." << endl;
        pf::Pause();
    }
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

    while (validDir == false) {
        zombies[turn].changeDir(dir[rand() % 4]);

        if (zombies[turn].withinBorders(board) == true &&
            zombies[turn].getObjInFront(board) != 'A' &&
            zombies[turn].getObjInFront(board) != '1' &&
            zombies[turn].getObjInFront(board) != '2' &&
            zombies[turn].getObjInFront(board) != '3' &&
            zombies[turn].getObjInFront(board) != '4' &&
            zombies[turn].getObjInFront(board) != '5' &&
            zombies[turn].getObjInFront(board) != '6' &&
            zombies[turn].getObjInFront(board) != '7' &&
            zombies[turn].getObjInFront(board) != '8' &&
            zombies[turn].getObjInFront(board) != '9') {

            validDir = true;
            break;
        }
        else
            continue;
    }

    if (zombies[turn].getObjInFront(board) == 'b') {
        zombies[turn].move(board, zombies[turn].getDir(), turn);
        cout << "Zombie " << turn + 1 << " moves " << zombies[turn].getDir() << "." << endl << endl;

        encounterBomb(board, zombies, alien, turn, "zombie");
    }
    else {
        zombies[turn].move(board, zombies[turn].getDir(), turn);
        cout << "Zombie " << turn + 1 << " moves " << zombies[turn].getDir() << "." << endl << endl;
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
    while (true) {
        Board board;

        int totalZomb = 1;

        if (gameSettings() == true) {
            board.init(boardSetX(), boardSetY());
            totalZomb = zombSettings();
        }

        vector<Zombie> zombies;

        //initializes firt zombie
        int x     = rand() % (board.getDimX()) + 1;
        int y     = rand() % (board.getDimY()) + 1;
        int life  = 100 + (rand() % (150 - 100 + 1));
        int atk   = 5 + (rand() % (15 - 5 + 1));
        int range = 1 + (rand() % (3 - 1 + 1));

        Zombie zombie;
        zombie.init(x, y, life, atk, range, "up");
        zombies.push_back(zombie);

        char zombNumb = 49;
        zombies[0].spawnZombie(board, zombNumb);

        //initializes all other zombies
        for (int j = 1; j < totalZomb; j++) {
            int x     = rand() % (board.getDimX()) + 1;
            int y     = rand() % (board.getDimY()) + 1;
            int life  = 100 + (rand() % (150 - 100 + 1));
            int atk   = 5 + (rand() % (15 - 5 + 1));
            int range = 1 + (rand() % (3 - 1 + 1));

            Zombie zombie;
            zombie.init(x, y, life, atk, range, "up");
            zombies.push_back(zombie);

            //makes sure zombie does not spawn in a space occupied by alien/other zombies
            char attemptedCoordinate = board.getObject(zombies[j].getX(), zombies[j].getY());

            while (attemptedCoordinate != '^' &&
                    attemptedCoordinate != 'v' &&
                    attemptedCoordinate != '<' &&
                    attemptedCoordinate != '>' &&
                    attemptedCoordinate != 'h' &&
                    attemptedCoordinate != 'p' &&
                    attemptedCoordinate != 'r' &&
                    attemptedCoordinate != ' ') {

                zombies[j].changeX(rand() % (board.getDimX()) + 1);
                zombies[j].changeY(rand() % (board.getDimY()) + 1);

                break;
            }
            char zombNumb = j + 49;
            zombies[j].spawnZombie(board, zombNumb);
        }

        Alien alien;

        int alienX = (board.getDimX() + 1) / 2;
        int alienY = (board.getDimY() + 1) / 2;

        alien.init(alienX, alienY, 100, 150, "up");
        alien.spawnAlien(board);

        //start of alien's turn
        while (true) {
            displayAllStats(board, alien, zombies, totalZomb);

            cout << endl;

            // runs command()
            while (true) {
                string cmd;
                cout << "<command> ";
                cin >> cmd;

                if (cmd != "up" && cmd != "down" &&
                    cmd != "left" && cmd != "right") {
                    commands(cmd, board, alien, zombies, totalZomb);

                    displayAllStats(board, alien, zombies, totalZomb);

                    cout << endl;

                    continue;
                    }
                else {
                    commands(cmd, board, alien, zombies, totalZomb);
                    break;
                }
            }

            resetTrail(board);

            alien.decreaseAtk(alien.getAtk());
            cout << endl << "Alien's turn ends. The trail has been reset." << endl << endl;

            int totalZombLife = 0;

            for (int i = 0; i < totalZomb; i++) {
                totalZombLife += zombies[i].getLife();
            }

            if (totalZombLife == 0) {
                displayAllStats(board, alien, zombies, totalZomb);
                cout << endl << "Alien wins." << endl;
                break;
            }
            
            pf::Pause();
            displayAllStats(board, alien, zombies, totalZomb);

            //start of zombie's turn
            for (int i = 0; i < totalZomb; i++) {
                board.display();

                cout << "   ";
                alien.displayStats();

                if (zombies[i].getLife() > 0)
                    zombieTurn(board, alien, zombies, totalZomb, i);
                else
                    continue;
            }

            //after zombie's turn, check if alien is still alive
            if (alien.getLife() == 0) {
                cout << "Zombie wins." << endl;
                break;
            }
            else
                continue;
        }

        while (true) {
            string confirmRestart;
            cout << "Play again (y/n)? => ";
            cin >> confirmRestart;

            if (confirmRestart == "y") {
                system("cls");
                break;
            }
            else if (confirmRestart == "n")
                exit(0);
            else {
                cout << "Please enter a valid command." << endl;
                continue;
            }
        }
        continue;
    }
}
