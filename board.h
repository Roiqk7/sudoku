#ifndef BOARD_H
#define BOARD_H

// generates unique sudoku puzzle (described bellow) and allows easy access to blocks

#include <algorithm>
#include <array>
#include "constants.h"
#include <iostream>
#include <random>
#include "timer.h"
#include <vector>


// num*3
int getBlockNum(const int &num)
{
    return num*3;
}

// num/3
int getRow(const int &num)
{
    return num/3;
}

// num%3
int getCol(const int &num)
{
    return num%3;
}

class Board {
    public: 
        std::array<std::array<int, SIZE>, SIZE> solved;
        std::array<std::array<int, SIZE>, SIZE> solvedBlocks;
        std::array<std::array<int, SIZE>, SIZE> actual;
        std::array<std::array<int, SIZE>, SIZE> actualBlocks;
        // determines puzzle difficulty based on user input
        int difficulty;
        // determines amount of numbers missing from puzzle based on difficulty
        int toFill;

        //  used for generation only
        struct Tile
        {
            // number on the tile
            int number;
            // number of possible numbers which can safely be assigned
            int value;
            // holds numbers which can be safely inserted
            std::vector<int> possibleNums;
        };
        std::array<std::array<Tile, SIZE>, SIZE> newlyGenerated;
        // [0] represents count of 0 value tiles, [1] represents count of 1 value tiles...
        std::array<int, SIZE+1> valueCount;

        Board() {
            difficulty = NO_NUMBER_SELECTED;
        }

        // creates new puzzle with according difficulty
        void createNewPuzzle(const int &difficulty)
        {
            this->difficulty = difficulty;
            toFill = getToFillNum();
            generate();
            setBlocks();
            startTimer();
        }

        void setBlocks()
        {
            solvedBlocks = getBlocks(solved);
            actualBlocks = getBlocks(actual);
            selectorWindow.setVisible(true);
        }

        std::array<std::array<int, SIZE>, SIZE> getBoard()
        {
            return actual;
        }

        // used to check if user made a mistake
        bool isMistake(const int &blockNum, const int &tileNum, const int &num) {
            return (solvedBlocks[blockNum][tileNum] != num && num != EMPTY_NUM); 
        }

    private:  
        const std::array<int, 4> maxRemove = {47, 52, 57, 62}; 
        const int removeRange = maxRemove[1] - maxRemove[0];
        /*                                                        
             ####  ###### #    # ###### #####    ##   ##### ###### 
            #    # #      ##   # #      #    #  #  #    #   #      
            #      #####  # #  # #####  #    # #    #   #   #####  
            #  ### #      #  # # #      #####  ######   #   #      
            #    # #      #   ## #      #   #  #    #   #   #      
             ####  ###### #    # ###### #    # #    #   #   ###### 
            We first create solved board. We do that by assigning randomly shuffled numbers 1-9 to
            three diagonal blocks. Then we hand it to solve function which is explained bellow. We then
            copy the solved array into 2d array which does not contain Tile struct (since we do not need it 
            anymore) and we then remove certain number of numbers based on the difficulty.
            Number of given based on difficulty:
            Easy: 34-38       
            Medium: 29-33
            Hard: 24-28
            Expert: 19-23                         
        */

        // orchestrates the generation of new sudoku puzzle
        void generate()
        {
            newlyGenerated = {{0}};
            valueCount = {0};

            getSolved();
            copyIntoSolved();

            stopwatch();
            getActual();
            stopwatch();
        }

        // creates solved board
        void getSolved()
        {
            // first fill diagonal blocks with randomly spread numbers 1-9
            fillDiagonalBlocks();
            std::cout << "Filled diagonals\n";
            printOut(newlyGenerated);
            // then calculate values pre-backtracking algorithm to make it available
            stopwatch();
            std::cout << "\nValue precalculation\n";
            calculateValues();
            stopwatch();
            // solve using backtracking
            stopwatch();
            solve(newlyGenerated);
            std::cout << "Solved board\n";
            printOut(newlyGenerated);
            stopwatch();
        }

        // creates actual board as seen by user
        void getActual()
        {
            std::cout << "Starting board\n";
            actual = solved;
            removeNumbers(actual);
            printOut(actual);
            std::cout << "Numbers to fill: " << toFill << '\n';
        }

        // removes numbers until difficulty is satisfied
        void removeNumbers(std::array<std::array<int, SIZE>, SIZE> &solved)
        {
            int removed = 0;
            int row, col;
            while (removed != toFill) {
                row = rand()%SIZE;
                col = rand()%SIZE;
                if (solved[row][col] != EMPTY_NUM) solved[row][col] = EMPTY_NUM, removed++;
            }
        }

        /*
             #####  ####### #       #     # ####### 
            #     # #     # #       #     # #       
            #       #     # #       #     # #       
             #####  #     # #       #     # #####   
                  # #     # #        #   #  #       
            #     # #     # #         # #   #       
             #####  ####### #######    #    #######  
            This is slightly updated backtracking algorithm. The time complexity is same but it's faster
            then my previous backtracking solver attempts. Before we even start solving we hand our board with 
            three diagonal blocks filled to calculate values function which counts for each empty tile
            how many numbers can be safely inserted. We then hand this evaluated 2d array to our solve function.
            The solve function then finds smallest value and tile with this value. We do that to ensure we are 
            always looking at tile with least number of possible numbers. This makes the process faster then 
            my previous backtracking algorithms. We then simply check all valid numbers until we find the 
            correct one.
        */

        // calculates value for each tile
        void calculateValues()
        {
            for (int row = 0; row < SIZE; row++) {
                for (int col = 0; col < SIZE; col++) {
                    getValue(row, col);
                }
            }
            valueCount[0] = 0;
        }

        // solves sudoku using backtracking algorithm
        bool solve(std::array<std::array<Tile, SIZE>, SIZE> &unsolved)
        {
            int row, col, smallestValue, num;
            smallestValue = getSmallestValue();
            if (smallestValue == INFINITE_VALUE) return true;
            if (smallestValue == 0) return false;
            findSmallestValueTile(unsolved, row, col, smallestValue);
            for (int i = 0; i < smallestValue; i++) {
                num = unsolved[row][col].possibleNums[i];
                if (isValid(num, row, col)) {
                    insertAndUpdateAffected(num, row, col);
                    if (solve(unsolved)) return true;
                    insertAndUpdateAffected(EMPTY_NUM, row, col);
                }
            }
            return false;
        }

        // iterate though array containing count of tiles with certain value and find lowest non-zero value count
        int getSmallestValue()
        {
            for (int i = 0; i <= SIZE; i++) {
                if (0 < valueCount[i]) return i;
            }
            return INFINITE_VALUE;
        }

        // finds empty tile on the board
        void findSmallestValueTile(std::array<std::array<Tile, SIZE>, SIZE> &unsolved, int &row, int &col, int &smallestValue)
        {
            for (row = 0; row < SIZE; row++) {
                for (col = 0; col < SIZE; col++) {
                    if (unsolved[row][col].number == EMPTY_NUM 
                    && unsolved[row][col].value == smallestValue) return;
                }
            }
        }

        // checks if number can be put on certain tile
        bool isValid(const int &num, const int &row, const int &col) {
            // row and col
            for (int i = 0; i < SIZE; i++) {
                if (newlyGenerated[row][i].number == num || newlyGenerated[i][col].number == num) return false;
            }
            // block
            int startRow = row-row%3, startCol = col-col%3;
            for (int i = 0; i <  3; i++) {
                for (int j = 0; j <  3; j++) {
                    if (newlyGenerated[startRow+i][startCol+j].number == num) return false;
                }
            }
            return true;
        }

        void insertAndUpdateAffected(const int &num, const int &row, const int &col)
        {
            newlyGenerated[row][col].number = num;
            updateValuesForAffected(row, col);
        }

        // updates values of affected numbers by inserted number
        void updateValuesForAffected(const int &row, const int &col)
        {
            // row and col
            for (int i = 0; i < SIZE; i++) {
                getValue(row, i);
                getValue(i, col);
            }
            // block
            int startRow = row-row%3, startCol = col-col%3;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    getValue(startRow+i, startCol+j);
                }
            } 
        }

        void getValue(const int &row, const int &col)
        {
            // subtract from current position
            valueCount[newlyGenerated[row][col].value]--;
            // skip occupied tiles
            if (newlyGenerated[row][col].number != EMPTY_NUM) {
                newlyGenerated[row][col].value = INFINITE_VALUE;
                return;
            };
            // make sure to clear all values so we don't have segmentation fault
            newlyGenerated[row][col].value = 0;
            newlyGenerated[row][col].possibleNums.clear();
            // count possibilities
            for (int num = 1; num <= SIZE; num++) {
                if (isValid(num, row, col)) {
                    newlyGenerated[row][col].possibleNums.push_back(num);
                    newlyGenerated[row][col].value++;
                }
            }
            // add to newly got position
            valueCount[newlyGenerated[row][col].value]++;
        }

        /*                                                       
            #####  ###### #    # #####  ####   ####  #       ####  
            #    # #      #    #   #   #    # #    # #      #      
            #    # #####  #    #   #   #    # #    # #       ####  
            #    # #      #    #   #   #    # #    # #           # 
            #    # #       #  #    #   #    # #    # #      #    # 
            #####  ######   ##     #    ####   ####  ######  ####                                                 
        */

        // prints inputted board into console
        void printOut(std::array<std::array<int, SIZE>, SIZE> &board)
        {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (board[i][j] == EMPTY_NUM) {
                        std::cout << '.' << ' ';
                    }
                    else std::cout << board[i][j] << ' ';
                }
                std::cout << '\n';
            }
        }

        // prints newly generated array
        void printOut(std::array<std::array<Tile, SIZE>, SIZE> &newlyGenerated)
        {
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    if (newlyGenerated[i][j].number == EMPTY_NUM) {
                        std::cout << '.' << ' ';
                    }
                    else std::cout << newlyGenerated[i][j].number << ' ';
                }
                std::cout << '\n';
            }
        }

        // prints tile values
        void printOutValues(std::array<std::array<Tile, SIZE>, SIZE> &newlyGenerated)
        {
            std::cout << "Values\n";
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    std::cout << std::setfill(' ') << std::setw(3) << newlyGenerated[i][j].value;
                }
                std::cout << '\n';
            }
            for (int i = 0; i < SIZE; i++) std::cout << i << ':' <<  valueCount[i] << ',';
            std::cout << '\n';
        }

        /*
            ######  #       #######  #####  #    #  #####  
            #     # #       #     # #     # #   #  #     # 
            #     # #       #     # #       #  #   #       
            ######  #       #     # #       ###     #####  
            #     # #       #     # #       #  #         # 
            #     # #       #     # #     # #   #  #     # 
            ######  ####### #######  #####  #    #  #####                                     
        */

        // puts numbers 1-9 in selected block on the diagonal
        void fillDiagonalBlocks() 
        {
            int block, row, col, i, max;
            std::array<int, SIZE> shuffledNums;
            for (block = 0; block < 3; block++) {
                shuffledNums = getRandomBlockNums();
                for (row = getBlockNum(block), i = 0, max = row+3; row < max; row++) {
                    for (col = getBlockNum(block); col < max; col++, i++) {
                        newlyGenerated[row][col].number = shuffledNums[i];
                    }
                }
            }
        }

    //* Generation

        // generates randomly shuffled numbers 1-9 used in generation of unique puzzle
        std::array<int, SIZE> getRandomBlockNums()
        {
            std::array<int, SIZE> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(nums.begin(), nums.end(), g);
            return nums;
        }

        // returns 2d array containing blocks from left to right, top to bottom
        std::array<std::array<int, SIZE>, SIZE> getBlocks(std::array<std::array<int, SIZE>, SIZE> &board)
        {
            stopwatch();
            std::array<std::array<int, SIZE>, SIZE> blocks = {{0}};
            for (int i = 0; i < SIZE; i++) blocks[i] = getBlock(i, board);
            std::cout << "Blocks\n";
            printOut(blocks);
            stopwatch();
            return blocks;
        }

    //* Gameboard

        // returns array containing numbers in block from left to right, top to bottom
        std::array<int, SIZE> getBlock(int &blockNum, std::array<std::array<int, SIZE>, SIZE> &board)
        {
            std::array<int, SIZE> block = {0};
            const int startRow = getBlockNum(getRow(blockNum)), startCol = getBlockNum(getCol(blockNum));
            const int endRow = startRow+3, endCol = startCol+3;
            int row, col, i;
            for (row = startRow, i = 0; row < endRow; row++) {
                for (col = startCol; col < endCol; col++, i++)  block[i] = board[row][col];
            }
            return block;
        }

        /*
            #    # ###### #      #####  ###### #####   ####  
            #    # #      #      #    # #      #    # #      
            ###### #####  #      #    # #####  #    #  ####  
            #    # #      #      #####  #      #####       # 
            #    # #      #      #      #      #   #  #    # 
            #    # ###### ###### #      ###### #    #  ####  
        */

    //* Generation 

        // after array is solved it copies newly generated to 2d array without Tile struct since beyond generation is useless
        void copyIntoSolved()
        {
            for (int row = 0; row < SIZE; row++) {
                for (int col = 0; col < SIZE; col++) solved[row][col] = newlyGenerated[row][col].number;
            }
        }

        // returns amount of numbers which need to be deleted based on difficulty
        int getToFillNum()
        {
            return maxRemove[difficulty]-rand()%removeRange;
        }
    
    //* Game board

        bool sameNumber(const int &num, const int &row, const int &col)
        {
            return actual[row][col] == num;
        }
};


#endif // BOARD_H