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

char table[row][col] = {
{'1', '2', '3'},
{'4', '5', '6'},
{'7', '8', '9'}
};


int main()
{
    while (gameover()) {
        draw_board();
        turn();
        gameover();
    }
    if (player == 2 && draw == false) {                 //when gameover returns false(?!?!?!?!?!?!) it goes to check who won or if it was a draw,
        std::cout << "Player 1 wins... \n";             //1 and 2 are switched here, it's because i switch the player after every move and idk im too lazy to fix
    }
    else if (player == 1 && draw == false) {
        std::cout << "Player 2 wins... \n";
    }
    else
        std::cout << "It's a draw\n";
}


void draw_board() {

    system("cls");

    std::cout << line;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            std::cout << "| " << table[i][j] << " | ";
        }
        std::cout << std::endl;
        std::cout << line;
    }

}


void turn(){

    std::cout << "Player " << player << " input a number from 1 to 9 to place your " << symbol << " : ";

    std::cin >> input;

    switch (input) {
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
        std::cout << "Field is already taken, try again\n";
        Sleep(1500);
        turn();
    }

    draw_board();

}


bool gameover() {

    for (int i = 0; i < 3; i++)
        if (table[i][0] == table[i][1] && table[i][0] == table[i][2] || table[0][i] == table[1][i] && table[0][i] == table[2][i])
            return false;

    if (table[0][0] == table[1][1] && table[0][0] == table[2][2] || table[0][2] == table[1][1] && table[0][2] == table[2][0])
        return false;

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (table[i][j] != 'X' && table[i][j] != 'O')
                return true;

    draw = true;
    return false;
}


void clearCin()
{
    std::cin.clear();
    std::cin.ignore(32767, '\n');
}

