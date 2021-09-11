#include <iostream>
#include<windows.h>

void clearCin();
void turn();
void draw_board();
bool gameover();

const int row = 3;
const int col = 3;

bool draw = false;

int x = 1;
int y = 1;

int player = 1;
char symbol = 'X';

int input{};

std::string line = " ---   ---   ---\n";

char table[row][col] = {                        //i would ideally like these to be empty or the same value (looks nicer)
{'1', '2', '3'},                                //but that makes it a pain to check for wincon so I'm not gonna bother
{'4', '5', '6'},                                //i could use the same method i already use and just ignore: ' '  but that would require a lot of extra unneccesary lines
{'7', '8', '9'}
};


int main()
{
    while (gameover() == false) {               //keeps the game going as long as gameover() returns false, meaning no wincon or draw has been reached
        draw_board();
        turn();
        gameover();
    }
    if (player == 2 && draw == false) {         //when gameover returns true it goes to check who won or if it was a draw,
        std::cout << "Player 1 wins! \n";       //1 and 2 are switched here, it's because i switch the player after every move and idk im too lazy to fix
    }
    else if (player == 1 && draw == false) {
        std::cout << "Player 2 wins!! \n";      //technically speaking the game is a solved draw,
    }                                           //but this outcome is the least likely, so player 2 gets an extra exclamation point for winning
    else
        std::cout << "It's a draw...\n";        //boo
}


void draw_board()                               //prints the board
{
    system("cls");                              //potentially unsafe(?) but idk how else to clear the console
                                                //not that clearing the console is a must, but it looks nice :)
    std::cout << line;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << "| " << table[i][j] << " | ";
        }
        std::cout << std::endl;
        std::cout << line;
    }

}

int getRandomNumber(double min, double max)
{
    static const double fraction = 1.0 / (static_cast <double> (RAND_MAX) + 1.0);
    return static_cast<double>(rand() * fraction * (max - min + 1) + min);
}


void turn()
{                                              //gets input, puts symbol corresponding to player turn in corresponding field (assuming conditions are met), or asks player to go again
    std::cout << "Input 0 to have the AI do a move for you! or\n";
                                               //this is still playing against the AI, you just have to input 0 every other turn, a bit clunky but less code-rewriting required from me haha
    std::cout << "Player " << player << " input a number from 1 to 9 to place your " << symbol << " : ";

    std::cin >> input;

    switch (input) {
    case 0:
        ai:
        x = getRandomNumber(0, 2);             //yes, the "AI" is just playing a random move :P
        y = getRandomNumber(0, 2);
        break;
    case 1:
        x = 0;
        y = 0;
        break;
    case 2:
        x = 0;
        y = 1;
        break;
    case 3:
        x = 0;
        y = 2;
        break;
    case 4:
        x = 1;
        y = 0;
        break;
    case 5:
        x = 1;
        y = 1;
        break;
    case 6:
        x = 1;
        y = 2;
        break;
    case 7:
        x = 2;
        y = 0;
        break;
    case 8:
        x = 2;
        y = 1;
        break;
    case 9:
        x = 2;
        y = 2;
        break;
    default:
        std::cout << "Invalid input, please try again\n";
        Sleep(2000);
        clearCin();
        turn();
    }


    if (player == 1 && table[x][y] != 'X' && table[x][y] != 'O') {
        table[x][y] = 'X';
        player = 2;
        symbol = 'O';
    }
    else if (player == 2 && table[x][y] != 'X' && table[x][y] != 'O') {
        table[x][y] = 'O';
        player = 1;
        symbol = 'X';
    }
    else {
        if (input == 0) {                       //prevents the AI from inputting into an already taken field
            goto ai;
        }
        std::cout << "Field is already taken, try again\n";
        Sleep(1500);
        turn();
    }

    draw_board();                               //call this again to show the move that was just done before next turn

}


bool gameover()
{                               //gets called once after every turn to check if a wincon/draw has been reached, and if so returns gameover == true

    for (int i = 0; i < 3; i++)                 //checks for the 6 possible straight line wins
        if (table[i][0] == table[i][1] && table[i][0] == table[i][2] || table[0][i] == table[1][i] && table[0][i] == table[2][i])
            return true;

    if (table[0][0] == table[1][1] && table[0][0] == table[2][2] || table[0][2] == table[1][1] && table[0][2] == table[2][0]) //cheks for the two possible diagonal wins
        return true;

    for (int i = 0; i < 3; i++)                 //if there are still empty squares, and no wincon has been reached, keep going
        for (int j = 0; j < 3; j++)
            if (table[i][j] != 'X' && table[i][j] != 'O')
                return false;

    draw = true;                                //(else) if all squares are taken, the game is a draw
    return true;
}

void clearCin()                                //a must to stop the program from looping if user enters something other than an integer as input
{
    std::cin.clear();
    std::cin.ignore(32767, '\n');
}