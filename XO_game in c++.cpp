/*
      yildiz
*/
#define ll long long 
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <queue>
#include <map>
using namespace std;
const int SIZE = 3;
const char EMPTY = '-';
const char P1 = 'X';
const char P2 = 'O';

void initBoard(char board[SIZE][SIZE]);
void playGame(char board[SIZE][SIZE]);
void draw(char board[SIZE][SIZE]);
bool isValid(char board[SIZE][SIZE], int r, int c);
bool won(char board[SIZE][SIZE], char sym);
bool checkRow(char board[SIZE][SIZE], int r, char sym);
bool checkCol(char board[SIZE][SIZE], int c, char sym);
bool checkDiags(char board[SIZE][SIZE], char sym);
bool full(char board[SIZE][SIZE]);
int getInt(const string& prompt);

int main() {
    char board[SIZE][SIZE];
    initBoard(board);
    playGame(board);
    return 0;
}

void initBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = EMPTY;
        }
    }
}

void playGame(char board[SIZE][SIZE]) {
    cout << "HEY DUDE! Welcome to Heba's XO\n";
    cout << "Enter player 1's name: ";
    string p1;
    getline(cin, p1);
    cout << "Enter player 2's name: ";
    string p2;
    getline(cin, p2);

    bool isP1Turn = true;
    bool gameEnd = false;

    while (!gameEnd) {
        draw(board);
        string currPlayer = isP1Turn ? p1 : p2;
        cout << currPlayer << "'s turn (" << (isP1Turn ? P1 : P2) << "):\n";

        int r, c;
        do {
            r = getInt("Enter the row number (0 to 2): ");
            c = getInt("Enter the column number (0 to 2): ");
            if (isValid(board, r, c)) {
                break;
            }
            cout << "Invalid POSITION, Try again.\n";
        } while (true);

        board[r][c] = isP1Turn ? P1 : P2;
        if (won(board, isP1Turn ? P1 : P2)) {
            cout << currPlayer << " WON!\n";
            gameEnd = true;
        }
        else if (full(board)) {
            cout << "TIE GUYS!\n";
            gameEnd = true;
        }
        else {
            isP1Turn = !isP1Turn;
        }
    }
    draw(board);
}

int getInt(const string& prompt) {
    int input;
    cout << prompt;
    while (!(cin >> input)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. " << prompt;
    }
    return input;
}

bool isValid(char board[SIZE][SIZE], int r, int c) {
    return r >= 0 && r < SIZE && c >= 0 && c < SIZE && board[r][c] == EMPTY;
}

void draw(char board[SIZE][SIZE]) {
    cout << "Current board:\n";
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j];
        }
        cout << "\n";
    }
}

bool won(char board[SIZE][SIZE], char sym) {
    for (int i = 0; i < SIZE; i++) {
        if (checkRow(board, i, sym) || checkCol(board, i, sym)) {
            return true;
        }
    }
    return checkDiags(board, sym);
}

bool checkRow(char board[SIZE][SIZE], int r, char sym) {
    for (int c = 0; c < SIZE; c++) {
        if (board[r][c] != sym) {
            return false;
        }
    }
    return true;
}

bool checkCol(char board[SIZE][SIZE], int c, char sym) {
    for (int r = 0; r < SIZE; r++) {
        if (board[r][c] != sym) {
            return false;
        }
    }
    return true;
}

bool checkDiags(char board[SIZE][SIZE], char sym) {
    bool diag1 = true, diag2 = true;
    for (int i = 0; i < SIZE; i++) {
        if (board[i][i] != sym) {
            diag1 = false;
        }
        if (board[i][SIZE - 1 - i] != sym) {
            diag2 = false;
        }
    }
    return diag1 || diag2;
}

bool full(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}