/*
Date: 09/11/2024

Grid class stores the sudoku grid and provides methods to manipulate it.

The sudoku grid is stored as a 1D array of 81 integers. The grid is divided into 9 rows, 9 columns, and 9 boxes.
Here is visual representation of the grid:
         0  1  2 | 3  4  5 | 6  7  8
         9 10 11 |12 13 14 |15 16 17
        18 19 20 |21 22 23 |24 25 26
        ---------|---------|---------
        27 28 29 |30 31 32 |33 34 35
        36 37 38 |39 40 41 |42 43 44
        45 46 47 |48 49 50 |51 52 53
        ---------|---------|---------
        54 55 56 |57 58 59 |60 61 62
        63 64 65 |66 67 68 |69 70 71
        72 73 74 |75 76 77 |78 79 80
And this is how the boxes are numbered:
        0  1  2
        3  4  5
        6  7  8
*/

#ifndef GRID_HPP
#define GRID_HPP

#include <array>

namespace Sudoku
{
        class Grid
        {
        public: // Methods
        // Class methods
                Grid();
                ~Grid();
        // Getter methods
                int getCell(int i) const;
                int getCell(int row, int col) const;
                void getRow(int row, std::array<int, 9>& rowArray) const;
                void getCol(int col, std::array<int, 9>& colArray) const;
                void getBox(int box, std::array<int, 9>& boxArray) const;
                void getBoxFixed(int box, std::array<bool, 9>& boxArray) const;
        // Setter methods
                void setZero(int count) noexcept;
                void setCell(int i, int value);
                void setCell(int row, int col, int value);
                void setRow(int row, const std::array<int, 9>& rowArray);
                void setCol(int col, const std::array<int, 9>& colArray);
                void setBox(int box, const std::array<int, 9>& boxArray);
        // Utility methods
                size_t size() const noexcept;
                void clear() noexcept;
                void fill(int value) noexcept;
                int convertIndex(int row, int col) const;
                void print() const noexcept;
                int count(int value) const noexcept;
        // Check methods
                bool checkIndex(int index, bool cell = true) const noexcept;
                bool isSolved() const noexcept;
                bool isValidValue(int row, int col, int value) const;
                bool isValidCell(
                        int row, int col, bool includeZero = true) const;
                bool isValidRow(int row) const;
                bool isValidCol(int col) const;
                bool isValidBox(int box) const;
                bool isValid() const;
                bool contains(int value) const noexcept;
        private: // Variables
                std::array<int, 81> grid;                                               // Stores the sudoku grid as a 1D array
        public: // Variables
                std::array<bool, 81> fixed;                                             // Stores whether a cell is fixed
        };
} // namespace Sudoku

#endif // !GRID_HPP