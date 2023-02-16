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

// !! FIX !! can't properly detect objects in board
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

public:
    Zombie(int life = 100, int atk = 5, int range = 1);

    void init(int x, int y, int life, int atk, int range);
    int getX();
    int getY();
    int getLife();
    int getAtk();
    int getRange();
    void displayStats();
    void spawnZombie(Board &board, char index);
};

Zombie::Zombie(int life, int atk, int range) {
}

void Zombie::init(int x, int y, int life, int atk, int range) {
    x_ = x;
    y_ = y;
    life_ = life;
    atk_ = atk;
    range_ = range;
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

public:
    Alien(int life = 100, int atk = 0);

    void init(int x, int y, int life, int atk);

    int getX();
    int getY();
    int getLife();
    int getAtk();

    void increaseLife(int life);
    void decreaseLife(int life);
    void increaseAtk(int atk);
    
    void moveUp(Board &board);
    void moveDown(Board &board);
    void moveLeft(Board &board);
    void moveRight(Board &board);

    void displayStats();
    void spawnAlien(Board &board);
};

Alien::Alien(int life, int atk) {
}

void Alien::init(int x, int y, int life, int atk) {
    x_ = x;
    y_ = y;
    life_ = life;
    atk_ = atk;
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

void Alien::increaseLife(int life) {
    life_ += life;
}

void Alien::decreaseLife(int life) {
    life_ -= life;
}

void Alien::increaseAtk(int atk) {
    atk_ += atk;
}

void Alien::moveUp(Board &board) {
    x_ = getX();
    y_ = getY();
    board.setObject(x_, y_, '.');

    y_ = y_ + 1;
    
    board.setObject(x_, y_, 'A');
}

void Alien::moveDown(Board &board) {
    x_ = getX();
    y_ = getY();
    board.setObject(x_, y_, '.');

    y_ = y_ - 1;
    
    board.setObject(x_, y_, 'A');
}

void Alien::moveLeft(Board &board) {
    x_ = getX();
    y_ = getY();
    board.setObject(x_, y_, '.');

    x_ = x_ - 1;
    
    board.setObject(x_, y_, 'A');
}

void Alien::moveRight(Board &board) {
    x_ = getX();
    y_ = getY();
    board.setObject(x_, y_, '.');

    x_ = x_ + 1;
    
    board.setObject(x_, y_, 'A');
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

    char confirmChange {};
    cout << "Do you wish to change the game settings (y/n)? => ";
    cin >> confirmChange;
    
    while(true) {
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

void reportObject(char obj, Alien &alien, Board &board) {
    switch (obj)
    {
    case '^':
        cout << "Alien finds an arrow." << endl;
        cout << "Alien's attack is increased by 20." << endl;
        alien.increaseAtk(20);
        break;

    case 'v':
        cout << "Alien finds an arrow." << endl;
        cout << "Alien's attack is increased by 20." << endl;
        alien.increaseAtk(20);
        break;

    case '<':
        cout << "Alien finds an arrow." << endl;
        cout << "Alien's attack is increased by 20." << endl;
        alien.increaseAtk(20);
        break;

    case '>':
        cout << "Alien finds an arrow." << endl;
        cout << "Alien's attack is increased by 20." << endl;
        alien.increaseAtk(20);
        break;
    
    case 'h':
        cout << "Alien finds a health pack." << endl;
        cout << "Alien's life is increased by 20." << endl;
        alien.increaseLife(20);
        break;

    case 'p':
        cout << "Alien finds a pod.";
        // !! ADD !! code to detect nearest zombie to the pod
        break;

    case 'r':
        cout << "Alien finds a rock.";
        // !! ADD !! code to break rock and spawn new object underneath
        break;

    case ' ':
        cout << "Alien finds an empty space.";
        break;

    default:
        break;
    }
}

void commands(Board &board, Alien &alien) {
    string cmd;
    cout << "<command> ";
    cin >> cmd;

    // !! ADD !! code for alien to move
    if (cmd == "up") {
        alien.moveUp(board);
        pf::Pause();
    }

    else if (cmd == "arrow") {
        int arrowX, arrowY;
        string arrowDir;
        cout << "Enter row, column, and direction: ";
        cin >> arrowY >> arrowX >> arrowDir;

        // !! ADD !! exception for if arrow coordinates are more than the dimensions

        char objAtCoords = board.getObject(arrowX, arrowY);

        if (objAtCoords != '^' && objAtCoords != 'v' &&
            objAtCoords != '<' && objAtCoords != '>')
            cout << "The object at this coordinate is not an arrow." << endl;
        else {
            char newArrow;

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
        pf::Pause();
    }
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
        zombie.init(x, y, life, atk, range);
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

    alien.init(alienX, alienY, alienLife, 0);
    alien.spawnAlien(board);

    while (true) {
        board.display();

        alien.displayStats();

        for (int i = 0; i < totalZomb; i++) {
            cout << "Zombie " << i + 1 << " : ";
            zombies[i].displayStats();
        }

        cout << endl;

        commands(board, alien);
    }

    // cout << endl << zombies[0].getX() << ", " << zombies[0].getY() << endl;
    // cout << board.getObject(5, 1);
}
