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
#include <string>
#include <vector>
#include <cstdlib> // for system()
#include <ctime>   // for time() in srand( time(NULL) );
#include <iomanip> // for setw()

using namespace std;

//                                      //
//              BOARD code              //
//                                      //

int defaultX {9};
int defaultY {5};

class Board
{
private:
    vector<vector<char>> map_;
    int dimX_, dimY_; 

public:
    //default: 5 rows, 9 columns
    Board(int dimX = defaultX, int dimY = defaultY);

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
Board::Board(int dimX, int dimY)
{
    init(dimX, dimY);
}

//creates the board and resizes it
void Board::init(int dimX, int dimY)
{
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

void Board::updateBoard()
{
    int numRows {};
    int numColumns {};

    cout << "Board Settings" << endl;
    cout << "--------------" << endl;
    
    //ask user for custom rows and columns
    while (true)
    {
        cout << "Enter rows => ";
        cin >> numRows;

        //checks if num of rows is odd
        if ((numRows % 2) != 0)
            break;
        else
        {
            cout << "Number of rows must be odd." << endl;
            continue;
        }
    }

    while (true)
    {
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

    defaultX = numColumns;
    defaultY = numRows;

    init(numColumns, numRows);

    //dimX_ and dimY_ are changed here
}

int Board::getDimX() const
{
    return dimX_;
}

int Board::getDimY() const
{
    return dimY_;
}

char Board::getObject(int x, int y) const
{ 
    return map_[defaultY - y][x - 1];
}

void Board::setObject(int x, int y, char ch)
{
    map_[dimY_ - y][x - 1] = ch;
}

//locates coordinates of a specific object
void locateCoordinates()
{
    Board Board;
    int x1 = 1, y1 = 1;
    char ch1 = 'A';
    int x2 = 15, y2 = 1;
    char ch2 = 'B';
    int x3 = 15, y3 = 5;
    char ch3 = 'C';
    int x4 = 1, y4 = 5;
    char ch4 = 'D';
    int x5 = 7, y5 = 3;
    char ch5 = 'E';

    Board.setObject(x1, y1, ch1);
    Board.setObject(x2, y2, ch2);
    Board.setObject(x3, y3, ch3);
    Board.setObject(x4, y4, ch4);
    Board.setObject(x5, y5, ch5);

    Board.display();

    cout << "The object " << ch1 << " should be at column "
         << x1 << " and row " << y1 << endl;
    cout << "The object " << ch2 << " should be at column "
         << x2 << " and row " << y2 << endl;
    cout << "The object " << ch3 << " should be at column "
         << x3 << " and row " << y3 << endl;
    cout << "The object " << ch4 << " should be at column "
         << x4 << " and row " << y4 << endl;
    cout << "The object " << ch5 << " should be at column "
         << x5 << " and row " << y5 << endl;
}

//checks if a specific coordinate is empty or not
bool Board::isEmpty(int x, int y) const
{
    return map_[dimY_ - y][x-1] == ' ';
}

//checks if a specific coordinate is within the board range (?)
bool Board::isInsideMap(int x, int y) const
{
    if ((0 < x) && (x <= dimX_) && (0 < y) && (y <= dimY_))
        return true;
    else
        return false;
}

//                                      //
//             ZOMBIE code              //
//                                      //

int totalZomb {1};  //total number of zombies
int zombLife {rand() % (200 - 100 + 1) + 100};
int zombAtk {rand() % (5 - 1 + 1) + 1};
int zombRange {rand() % (3 - 1 + 1) + 1};

class Zombie
{
private:
    int x_, y_;                 //coordinates
    int life_, atk_, range_;    //stats

public:
    Zombie(int life = zombLife, int atk = zombAtk, int range = zombRange);
    void zombieInfo() const;
    void displayStats(int zombIndex) const;
    void spawnZombie(Board &board, char index);
    void minusHealth();
    void addHealth();
    void move();
};

Zombie::Zombie(int life, int atk, int range)
{
}

//displays an individual zombie's stats (life, atk, range)
//!! FIX !! zombie stats way too high
void Zombie::displayStats(int zombIndex) const
{
    cout << "Zombie " << zombIndex << " : ";
    cout << "Life " << life_ << ", ";
    cout << "Attack " << atk_ << ", ";
    cout << "Range " << range_ << endl;
}

void Zombie::spawnZombie(Board &board, char index)
{
    x_ = rand() % (board.getDimX()) + 1;
    y_ = rand() % (board.getDimY()) + 1;

    board.setObject(x_, y_, index);
}

//                                      //
//              ALIEN code              //
//                                      //

class Alien
{
private:
    int x_, y_;         //coordinates
    int life_, atk_;    //stats

public:
    Alien(int life = 100, int atk = 0);
    int getX() const;
    int getY() const;
    void displayStats() const;
    void spawnAlien(Board &board);
    void minusHealth();
    void addHealth();
    void move(Board &board, string cmd);
};

Alien::Alien(int life, int atk)
{
    Board board;
    spawnAlien(board);
}

int Alien::getX() const
{
    return x_;
}

int Alien::getY() const
{
    return y_;
}

// !! FIX !! life and atk stats are way too high
void Alien::displayStats() const
{
    cout << "Alien    : ";
    cout << "Life " << life_ << ", ";
    cout << "Attack " << atk_;
}

void Alien::spawnAlien(Board &board)
{
    x_ = (board.getDimX() + 1) / 2;
    y_ = (board.getDimY() + 1) / 2;

    board.setObject(x_, y_, 'A');
}

// !! FIX !! program literally just crashes after up/down/left/right???
void Alien::move(Board &board, string cmd)
{
    Alien alien;
    
    x_ = alien.getX();
    y_ = alien.getY();
    board.setObject(x_, y_, ' ');

    if (cmd == "up")
        y_ = y_ + 1;

    else if (cmd == "right")
        x_ = x_ + 1;

    else if (cmd == "left")
        x_ = x_ - 1;

    else if (cmd == "down")
        y_ = y_ - 1;
    
    board.setObject(x_, y_, 'A');
}

//                                      //
//              MAIN code               //
//                                      //

char confirmChange()
{
    char confirmChange {};
    cout << "Do you wish to change the game settings (y/n)? => ";
    cin >> confirmChange;

    return confirmChange;
}

//asks users to input num of rows, columns & zombies
void gameSettings()
{
    Board board;

    board.updateBoard();

    board.init(defaultX, defaultY);

    cout << endl;

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

    totalZomb = numZombies;

    cout << "Settings Updated." << endl;
    cout << "Press any key to continue . . . "; // how to make it continue?
}

//responds to user commands
void controls()
{
    Board board;
    Alien alien;

    alien.getX();
    alien.getY();

    string command;
    cout << "<command> ";
    cin >> command;

    if (command == "up")
    {
        alien.move(board, command);
        pf::Pause();
    }

    else if (command == "down")
    {
        alien.move(board, "down");
        pf::Pause();
    }

    else if (command == "left")
    {
        alien.move(board, "left");
        pf::Pause();
    }

    else if (command == "right")
    {
        alien.move(board, "left");
        pf::Pause();
    }

    else if (command == "arrow")
    {
        int arrowX, arrowY;
        cout << "Enter coordinates of the arrow object to switch." << endl;
        
        cout << "Row => ";
        cin >> arrowY;

        cout << "Column => ";
        cin >> arrowX;
        cout << endl;

        // seems to be issue with getObject function
        char objAtCoords = board.getObject(arrowX, arrowY);

        // !! FIX !! tells user object is not an arrow even when it is
        // check if object at coordinates is arrow or not
        if (objAtCoords != ('^' || 'v' || '<' || '>'))
            cout << "The object at this coordinate is not an arrow." << endl;
        else
        {
            string arrowDir;
            cout << "Enter direction to switch to. (up/down/left/right) => ";
            cin >> arrowDir;

            // translates user input into arrow char
            char newArrow;
            while (true)
            {
                if (arrowDir == "up")
                {
                    newArrow = '^';
                    break;
                }
                else if (arrowDir == "down")
                {
                    newArrow = 'v';
                    break;
                }
                else if (arrowDir == "left")
                {
                    newArrow = '<';
                    break;
                }
                else if (arrowDir == "right")
                {
                    newArrow = '>';
                    break;
                }
                else
                {
                    cout << "Invalid input. Please type either up/down/left/right.";
                    continue;
                }
            }

            // change the arrow direction
            board.setObject(arrowX, arrowY, newArrow);
        }

        pf::Pause();
    }

    else if (command == "help")
    {
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

    // !! ADD !! save feature
    // else if (command == "save")
    // !! ADD !! save feature
    // else if (command == "load")
    // !! FIX !! quit feature
    // else if (command == "quit")
    // {
    //     char confirmQuit;
    //     cout << "Are you sure? (y/n)";
    //     cin << confirmQuit;
    //     if (confirmQuit == 'y')
    //         exit()
    //     else if (choice == 'n')
            
    //     else 
    //         cout << "Please enter a valid command.";
    // }
    else
    {
        cout << "Please enter a valid command." << endl;
        pf::Pause();
    }
}

void displayStats(int totalZomb)
{
    Alien alien;
    Zombie zombie;

    alien.displayStats();
    cout << endl;

    for (int i = 1; i <= totalZomb; ++i)
    {
        zombie.displayStats(i);
    }
}

// !! ADD !! turn counter

int main()
{
    cout << "Assignment (Part 1)" << endl;
    cout << "Let's Get Started!" << endl;
    pf::Pause();

    cout << "Default Game Settings" << endl;
    cout << "---------------------" << endl;
    cout << "Board Rows     : " << defaultY << endl;
    cout << "Board Columns  : " << defaultX << endl;
    cout << "Zombie Count   : " << totalZomb << endl << endl;
    
    while(true)
    {
        char changeSettings = confirmChange();

        if (changeSettings == 'y')
        {
            gameSettings();
            break;
        }
        else if (changeSettings == 'n')
            break;
        else;
        {
            cout << "Invalid input. Please enter y/n." << endl;
            continue;
        }
    }
    
    Board board;
    Alien alien;
    Zombie zombie;
    
    alien.spawnAlien(board);

    //spawns zombies based on zombie count
    //49 is the ascii code for '1'
    for (int i = 49; i < totalZomb + 49; ++i)
    {
        char zombieNumb = i;
        zombie.spawnZombie(board, zombieNumb);
    }

    while(true)
    {
        board.display();

        displayStats(totalZomb);

        cout << endl << endl;

        controls();
        system("cls");
    }
}
