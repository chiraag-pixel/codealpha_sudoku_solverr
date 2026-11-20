#include <iostream>
#include <string>
using namespace std;

int grid[9][9];

void printGrid() {
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0) {
            cout << "------+-------+------\n";
        }
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0) {
                cout << "| ";
            }
            if (grid[i][j] == 0) {
                cout << ". ";
            } else {
                cout << grid[i][j] << " ";
            }
        }
        cout << "\n";
    }
}

// checks if num can be placed at grid[row][col]
// looks at the row, the column and the 3x3 box
bool isSafe(int row, int col, int num) {
    for (int i = 0; i < 9; i++) {
        if (grid[row][i] == num) return false;
        if (grid[i][col] == num) return false;
    }

    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[startRow + i][startCol + j] == num) return false;
        }
    }
    return true;
}

// backtracking: find an empty cell, try 1 to 9, go to the next empty cell.
// if nothing works go back and change the previous cell
bool solve() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (grid[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isSafe(row, col, num)) {
                        grid[row][col] = num;
                        if (solve()) {
                            return true;
                        }
                        grid[row][col] = 0;  // wrong choice, undo
                    }
                }
                return false;  // no number fits here
            }
        }
    }
    return true;  // no empty cells left
}

// checks that the numbers already given don't break the rules
bool startingGridOk() {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            int num = grid[i][j];
            if (num != 0) {
                grid[i][j] = 0;
                bool ok = isSafe(i, j, num);
                grid[i][j] = num;
                if (!ok) {
                    cout << "Row " << i + 1 << ", column " << j + 1
                         << " (" << num << ") clashes with another number.\n";
                    return false;
                }
            }
        }
    }
    return true;
}

void useSample() {
    string sample[9] = {
        "530070000",
        "600195000",
        "098000060",
        "800060003",
        "400803001",
        "700020006",
        "060000280",
        "000419005",
        "000080079"};
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            grid[i][j] = sample[i][j] - '0';
        }
    }
}

// reads 9 rows, each row has 9 characters. 0 or . means empty
bool readGrid() {
    cout << "Enter the puzzle row by row (9 characters per row).\n";
    cout << "Use 0 or . for empty cells. Example: 530070000\n";

    for (int i = 0; i < 9; i++) {
        string row;
        while (true) {
            cout << "Row " << i + 1 << ": ";
            if (!(cin >> row)) {
                return false;  // input ended
            }

            bool ok = (row.length() == 9);
            for (int j = 0; ok && j < 9; j++) {
                if (row[j] != '.' && (row[j] < '0' || row[j] > '9')) {
                    ok = false;
                }
            }

            if (ok) break;
            cout << "Row must have exactly 9 digits (or dots). Try again.\n";
        }

        for (int j = 0; j < 9; j++) {
            grid[i][j] = (row[j] == '.') ? 0 : row[j] - '0';
        }
    }
    return true;
}

int main() {
    int choice;

    cout << "Sudoku Solver\n";
    cout << "1. Enter my own puzzle\n";
    cout << "2. Use a sample puzzle\n";
    cout << "Choice: ";
    if (!(cin >> choice)) {
        return 0;
    }

    if (choice == 2) {
        useSample();
    } else {
        if (!readGrid()) {
            return 0;
        }
    }

    cout << "\nPuzzle:\n";
    printGrid();

    if (!startingGridOk()) {
        cout << "\nThis puzzle is not valid.\n";
        return 0;
    }

    if (solve()) {
        cout << "\nSolution:\n";
        printGrid();
    } else {
        cout << "\nNo solution exists for this puzzle.\n";
    }

    return 0;
}
