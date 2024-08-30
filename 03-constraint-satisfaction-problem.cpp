#include <iostream>
#include <vector>
using namespace std;

bool isSafe(vector<vector<int>> &board, int row, int col, int num) {
    for (int x = 0; x < 9; x++) {
        if (board[row][x] == num || board[x][col] == num ||
            board[row - row % 3 + x / 3][col - col % 3 + x % 3] == num) {
            return false;
        }
    }
    return true;
}

bool solveSudoku(vector<vector<int>> &board, int row, int col) {
    if (row == 8 && col == 9) return true;
    if (col == 9) {
        row++;
        col = 0;
    }
    if (board[row][col] != 0) return solveSudoku(board, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solveSudoku(board, row, col + 1)) return true;
            board[row][col] = 0;
        }
    }
    return false;
}

void printBoard(vector<vector<int>> &board) {
    for (int r = 0; r < 9; r++) {
        for (int d = 0; d < 9; d++) {
            cout << board[r][d] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<int>> board = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solveSudoku(board, 0, 0)) {
        printBoard(board);
    } else {
        cout << "No solution exists.\n";
    }

    return 0;
}
