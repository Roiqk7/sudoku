/*
Date: 09/11/2024

Description: This file contains the main function.
*/

#include "../include/globals.hpp"

// Delete - Test
#include "../include/grid.hpp"
#include "../include/generator.hpp"
#include <array>

int main()
{
        LOG_TRACE("main() called");

        #ifdef DEVELOPMENT
        SET_LOG_LEVEL_DEBUG();
        #endif // DEVELOPMENT

        // Delete - Test
        Sudoku::Grid grid;
        Sudoku::Generator generator;

        for (int i = 0; i < 9; i++)
        {
                generator.generate(grid);
                grid.print();
        }

        return 0;
}