# sudoku_solverr
The puzzle is stored in a 9x9 array and solved with backtracking. For each empty cell it tries the numbers 1 to 9, and a number is only placed if it isn't already in that row, column or 3x3 box. If a cell has no number that fits, the program goes back to the previous cell and tries the next number.

How to use
Run the program and pick an option:

Enter your own puzzle: type 9 rows with 9 characters each. Use 0 or . for empty cells.
Use the built in sample puzzle.
Example row: 530070000

If the numbers you entered break the sudoku rules, or the puzzle has no solution, it tells you.

Run
g++ sudoku\_solver.cpp -o sudoku
./sudoku
