/*
Date: 09/11/2024

Description: This file contains the main function.
*/

#include "../include/globals.hpp"

// Delete - Test
#include "../include/grid.hpp"
#include "../include/solver.hpp"
#include <array>


int main()
{
        LOG_TRACE("main() called");

        #ifdef DEVELOPMENT
        SET_LOG_LEVEL_DEBUG();
        #endif // DEVELOPMENT

        // Delete - Test
        Sudoku::Grid grid;
        grid.print();

        std::array<int, 9> rowArray = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        grid.setBox(0, rowArray);
        grid.setBox(4, rowArray);
        grid.setBox(8, rowArray);
        grid.print();

        Sudoku::Solver solver;
        solver.solve(grid);
        grid.print();

        return 0;
}