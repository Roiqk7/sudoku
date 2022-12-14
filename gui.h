#ifndef GUI_H
#define GUI_H

// draws on the board and handles clicks

#include <array>
#include "board.h"
#include "constants.h"
#include "difficultyWindow.h"
#include "gameboard.h"
#include "gameOverProp.h"
#include "hub.h"
#include <iostream>
#include "menu.h"
#include "selectorWindow.h"
#include <SFML/Graphics.hpp>
#include "textBox.h"
#include "timer.h"


class Gui {
    public: 
        Gameboard gameboard;
        GameOverProp gameOverProp;
        Hub hub;

        Gui() {
            tileSelected = false;
            selectedBlock = selectedTile = NO_NUMBER_SELECTED;
            hub.init();
            selector.init();
        }

        void call(Board &board)
        {
            if (!timeStopped) hub.updateTimer();
            render(board);
        }

        /*
            ####### #     # ####### #     # #######  #####  
            #       #     # #       ##    #    #    #     # 
            #       #     # #       # #   #    #    #       
            #####   #     # #####   #  #  #    #     #####  
            #        #   #  #       #   # #    #          # 
            #         # #   #       #    ##    #    #     # 
            #######    #    ####### #     #    #     #####                                   
        */

        void handleClick(const int windowNumber, Board &board, Menu &menu)
        {
            std::cout << "3. Click handling\n";
            stopwatch3();
            getClickedElement(windowNumber, board, menu);
            stopwatch3();
        }

        void handleNewGameCreation(Board &board, Menu &menu, const int &difficulty)
        {
            menu.newGame = false;
            menu.show = false;
            std::cout << "2. New puzzle creation\n";
            stopwatch2();
            board.createNewPuzzle(difficulty);
            setBoard(board);
            stopwatch2();
        }

    private:  
        sf::Vector2i cursorPos; 
        bool tileSelected;
        int selectedBlock, selectedTile;

        void render(Board &board)
        {
            hub.call();
            gameboard.call();
            selector.call();
            if (gameOverProp.gameOver) return gameOverProp.call();
            if (tileSelected) 
            handleHighlight(board, board.actualBlocks[selectedBlock][selectedTile]);
        }

        /*
             #####  ####### #     # ####### ######     #    ####### ####### 
            #     # #       ##    # #       #     #   # #      #    #       
            #       #       # #   # #       #     #  #   #     #    #       
            #  #### #####   #  #  # #####   ######  #     #    #    #####   
            #     # #       #   # # #       #   #   #######    #    #       
            #     # #       #    ## #       #    #  #     #    #    #       
             #####  ####### #     # ####### #     # #     #    #    ####### 
        */

        // uploads board onto screen
        void setBoard(Board &board)
        {
            std::cout << "hub and gameboard setup\n";
            stopwatch();
            selectedBlock = selectedTile = selectedNumber = NO_NUMBER_SELECTED;
            tileSelected = false;
            hub.initHubElementText(board);
            gameboard.createBlocks(board);
            stopwatch();
        }

        // restarts the game
        void restart(Board &board)
        {
            board.setBlocks();
            gameboard.createBlocks(board);
            resetValues();
        }

        void resetValues() 
        {
            tileSelected = false;
            selectedBlock = selectedTile = selectedNumber = NO_NUMBER_SELECTED;
            gameOverProp.gameOver = false;
            hub.mistakeCounter.mistakes = 0;
            hub.updateMistakeCounter();
            timeStopped = false;
            startTimer();
        }

        /*
            ### #     # ######  #     # ####### 
             #  ##    # #     # #     #    #    
             #  # #   # #     # #     #    #    
             #  #  #  # ######  #     #    #    
             #  #   # # #       #     #    #    
             #  #    ## #       #     #    #    
            ### #     # #        #####     #    
            User blessed us with their input                         
        */

        // user clicked somewhere, we need to find where
        void getClickedElement(const int windowNumber, Board &board, Menu &menu)
        {
            switch (windowNumber) {
                case MAIN_WINDOW_NUM:
                    return handleMainClick(board, menu);
                case SELECTOR_WINDOW_NUM:
                    if (cooldown(COOLDOWN)) break;
                    else return handleSelectorClick(board);
                case DIFFICULTY_WIDOW_NUM:
                    return handleDifficultyClick(board, menu);
                default:
                    break;
            }
            return;
        }

        /*
             #####  #######    #    ######   #####  #     # 
            #     # #         # #   #     # #     # #     # 
            #       #        #   #  #     # #       #     # 
             #####  #####   #     # ######  #       ####### 
                  # #       ####### #   #   #       #     # 
            #     # #       #     # #    #  #     # #     # 
             #####  ####### #     # #     #  #####  #     # 
            Where did user click?                                   
        */

        void handleMainClick(Board &board, Menu &menu)
        {
            cursorPos = sf::Mouse::getPosition(window);
            // if game is over then do not handle anything else
            if (gameOverProp.gameOver) getClickedGameOverPropElement(cursorPos);
            // clicked on menu
            if (menu.show) return menu.getClickedElement(cursorPos);
            // hub selected
            else if (cursorPos.y < hub.hubHeight) 
                return getClickedHubElement(cursorPos, board, menu);
            // board selected
            else {
                selectedBlock = getRect(gameboard.size, gameboard.xPos, gameboard.yPos, gameboard.thickMargin, cursorPos);
                selectedTile = getRect(gameboard.blockSize, gameboard.blocks[selectedBlock].xPos, gameboard.blocks[selectedBlock].yPos,
                    gameboard.thinMargin, cursorPos);
                if (selectedBlock == ELEMENT_NOT_FOUND || selectedTile == ELEMENT_NOT_FOUND) {
                    tileSelected = false;
                    return;
                }
                if (!tileSelected) tileSelected = true;
            }   
        }


        void getClickedGameOverPropElement(const sf::Vector2i &cursorPos)
        {
            // user wants new game
            if (checkClicked(gameOverProp.newGamePropXPos, gameOverProp.newGamePropWidth, cursorPos.x)
                && checkClicked(gameOverProp.newGamePropYPos, gameOverProp.newGamePropHeigh, cursorPos.y))
                    difficultyWindow.setVisible(true);
            // user wants to leave
            if (checkClicked(gameOverProp.exitPropXPos, gameOverProp.exitPropWidth, cursorPos.x)
                && checkClicked(gameOverProp.exitPropYPos, gameOverProp.exitPropHeigh, cursorPos.y))
                    exit(EXIT_SUCCESS);
        }

        // user either clicked pause, new game or hint
        void getClickedHubElement(const sf::Vector2i &cursorPos, Board &board, Menu &menu)
        {
            // check pause
            if (checkClicked(hub.pauseButton.xPos, hub.pauseButton.width, cursorPos.x)) {
                menu.show = true;
                stopTime();
            }
            // check new game
            if (checkClicked(hub.newGameProp.xPos, hub.newGameProp.width, cursorPos.x)) 
                difficultyWindow.setVisible(true);
            // check hint 
            if (checkClicked(hub.hintProp.xPos, hub.hintProp.width, cursorPos.x)) 
                if (board.toFill != 0) putHint(board);
            // check notes
            if (checkClicked(hub.notesProp.xPos, hub.notesProp.width, cursorPos.x)) 
                handleNotes();
                
        }

        // user selected a number
        void handleSelectorClick(Board &board)
        {
            cursorPos = sf::Mouse::getPosition(selectorWindow);
            int selectedNumber = 1+calculateElement(HEIGHT_2, SIZE+1, 0, 0, cursorPos.y);
            if (selectedNumber == ELEMENT_NOT_FOUND) return;
            if (selectedNumber == SIZE+1) selectedNumber = EMPTY_NUM;
            if (tileSelected) {
                if (!hub.notesProp.active) handleNumberInsertion(board, selectedNumber);
                else handleNotesInsertion(board, selectedNumber-1);
            }
        }

        void handleDifficultyClick(Board &board, Menu &menu)
        {
            cursorPos = sf::Mouse::getPosition(difficultyWindow);
            int difficulty = calculateElement(HEIGHT_3, DIFFICULTY_WIN_ELEMENT_COUNT, 0, 0, cursorPos.y);
            if (difficulty == NO_NUMBER_SELECTED) return;
            if (difficulty == DIFFICULTY_WIN_ELEMENT_COUNT-1 && menu.newGame) difficulty = rand()%DIFFICULTY_WIN_ELEMENT_COUNT;
            resetValues();
            difficultyWindow.setVisible(false);
            if (difficulty != DIFFICULTY_WIN_ELEMENT_COUNT-1) handleNewGameCreation(board, menu, difficulty);
            else restart(board);
        }

        /*
            ### #     #  #####  ####### ######  ####### 
             #  ##    # #     # #       #     #    #    
             #  # #   # #       #       #     #    #    
             #  #  #  #  #####  #####   ######     #    
             #  #   # #       # #       #   #      #    
             #  #    ## #     # #       #    #     #    
            ### #     #  #####  ####### #     #    #    
            Place number on screen                                
        */

        // determines if number can be placed and if it's correct
        void handleNumberInsertion(Board &board, const int &number)
        {
            if (checkIfOccupiedAndWrong(board)) {
                tileSelected = false;
                return;
            }
            gameboard.blocks[selectedBlock].tiles[selectedTile].box.changeText(number);
            if (number != EMPTY_NUM) gameboard.blocks[selectedBlock].tiles[selectedTile].showNotes = false;
            else gameboard.blocks[selectedBlock].tiles[selectedTile].showNotes = true;
            gameboard.blocks[selectedBlock].numbers[selectedTile] = number;
            board.actualBlocks[selectedBlock][selectedTile] = number;
            handleHighlight(board, number);
            if (number != EMPTY_NUM) {
                if (board.isMistake(selectedBlock, selectedTile, number)) handleMistake(board, number-1);
                else handleCorrect(board, number-1);
            }
            else gameboard.blocks[selectedBlock].tiles[selectedTile].box.mistakeHighlight = false;
        }

        void handleMistake(Board &board, const int &number)
        {
            hub.mistakeCounter.mistakes++;
            hub.updateMistakeCounter();
            gameboard.blocks[selectedBlock].tiles[selectedTile].box.mistakeHighlight = true;
            gameboard.blocks[selectedBlock].tiles[selectedTile].notes[number].show = false;
            handleGameOver(board);
        }

        void handleCorrect(Board &board, const int &number)
        {
            board.toFill--;
            gameboard.blocks[selectedBlock].numbers[selectedTile] = board.actualBlocks[selectedBlock][selectedTile] = board.solvedBlocks[selectedBlock][selectedTile];
            gameboard.blocks[selectedBlock].tiles[selectedTile].box.mistakeHighlight = false;
            gameboard.blocks[selectedBlock].tiles[selectedTile].box.mainHighlight = true;
            gameboard.blocks[selectedBlock].tiles[selectedTile].showNotes = false;
            removeNotesFromRowColBlock(number);
            handleGameOver(board);
        }

        /*
            #     # ####### ####### #######  #####  
            ##    # #     #    #    #       #     # 
            # #   # #     #    #    #       #       
            #  #  # #     #    #    #####    #####  
            #   # # #     #    #    #             # 
            #    ## #     #    #    #       #     # 
            #     # #######    #    #######  #####  
        */

        void handleNotesInsertion(Board &board, const int &number)
        {
            if (checkIfOccupied(board)) {
                tileSelected = false;
                return;
            }
            if (gameboard.blocks[selectedBlock].tiles[selectedTile].notes[number].show)
                gameboard.blocks[selectedBlock].tiles[selectedTile].notes[number].show = false;
            else gameboard.blocks[selectedBlock].tiles[selectedTile].notes[number].show = true;
        }

        void handleNotes()
        {
            if (!hub.notesProp.box.highlight) {
                hub.notesProp.active = true;
                hub.notesProp.box.highlight = true;
                return;
            }
            hub.notesProp.active = false;
            hub.notesProp.box.highlight = false;
        }

        // if user enters correct number this removes the number from notes in row, col and block
        void removeNotesFromRowColBlock(const int &number)
        {
            const int blockRow = getRow(selectedBlock), blockCol = getCol(selectedBlock);
            const int tileRow = getRow(selectedTile), tileCol = getCol(selectedTile);
            for (int block = 0; block < 3; block++) {
                for (int tile = 0; tile < 3; tile++) {
                    gameboard.blocks[getBlockNum(blockRow)+block].tiles[getBlockNum(tileRow)+tile].notes[number].show = false;
                    gameboard.blocks[blockCol+getBlockNum(block)].tiles[tileCol+getBlockNum(tile)].notes[number].show = false;
                    gameboard.blocks[selectedBlock].tiles[getBlockNum(block)+tile].notes[number].show = false;
                }
            }
        }

        /*
            #     # ###  #####  #     # #       ###  #####  #     # ####### 
            #     #  #  #     # #     # #        #  #     # #     #    #    
            #     #  #  #       #     # #        #  #       #     #    #    
            #######  #  #  #### ####### #        #  #  #### #######    #    
            #     #  #  #     # #     # #        #  #     # #     #    #    
            #     #  #  #     # #     # #        #  #     # #     #    #    
            #     # ###  #####  #     # ####### ###  #####  #     #    #    
        */

        // handle highlight of the block, row, col and same numbers 
        void handleHighlight(Board &board, const int &number)
        {
            bool state;
            static int lastBlockNum = selectedBlock, lastTileNum = selectedTile, lastNumber = number;
            // if new block or tile then turn off highlight for previous and reassign last_ values
            if (lastBlockNum != selectedBlock || lastTileNum != selectedTile || lastNumber != number) {
                state = false;
                highlightRowColBlock(lastBlockNum, lastTileNum, state);
                highlightSameNums(lastNumber, state);
                lastBlockNum = selectedBlock, lastTileNum = selectedTile, lastNumber = number;
            }
            // highlight numbers
            state = true;
            highlightRowColBlock(selectedBlock, selectedTile, state);
            if (number != EMPTY_NUM) highlightSameNums(number, state);
        }

        void highlightRowColBlock(const int &blockNum, const int &tileNum, const bool &state)
        {
            const int blockRow = getRow(blockNum), blockCol = getCol(blockNum);
            const int tileRow = getRow(tileNum), tileCol = getCol(tileNum);
            for (int block = 0; block < 3; block++) {
                for (int tile = 0; tile < 3; tile++) {
                    gameboard.blocks[getBlockNum(blockRow)+block].tiles[getBlockNum(tileRow)+tile].box.highlight = state;
                    gameboard.blocks[blockCol+getBlockNum(block)].tiles[tileCol+getBlockNum(tile)].box.highlight = state;
                    gameboard.blocks[blockNum].tiles[getBlockNum(block)+tile].box.highlight = state;
                }
            }
            gameboard.blocks[blockNum].tiles[tileNum].box.mainHighlight = state;
        }

        void highlightSameNums(const int &num, const bool &state)
        {
            for (int block = 0; block < SIZE; block++) {
                for (int tile = 0; tile < SIZE; tile++) {
                    if (gameboard.blocks[block].numbers[tile] == num) 
                    gameboard.blocks[block].tiles[tile].box.mainHighlight = state;
                }
            }
        }

        /*
             #####     #    #     # #######    ####### #     # ####### ######  
            #     #   # #   ##   ## #          #     # #     # #       #     # 
            #        #   #  # # # # #          #     # #     # #       #     # 
            #  #### #     # #  #  # #####      #     # #     # #####   ######  
            #     # ####### #     # #          #     #  #   #  #       #   #   
            #     # #     # #     # #          #     #   # #   #       #    #  
             #####  #     # #     # #######    #######    #    ####### #     # 
                                                                    
        */

        // checks if game is over and handles the situation
        void handleGameOver(Board &board)
        {
            int gameOverCondition;
            if (board.toFill == 0) gameOverCondition = WON;
            else if (hub.mistakeCounter.mistakes == 3) gameOverCondition = LOST;
            else return;
            // game over
            stopTime();
            selectorWindow.setVisible(false);
            gameOverProp.init(gameOverCondition);
        }

        /*
            #     # ####### #       ######  ####### ######  
            #     # #       #       #     # #       #     # 
            #     # #       #       #     # #       #     # 
            ####### #####   #       ######  #####   ######  
            #     # #       #       #       #       #   #   
            #     # #       #       #       #       #    #  
            #     # ####### ####### #       ####### #     # 
        */

        // takes element of size and divides it into divideInto and starts from start pos and looks if mousePos is present
        int calculateElement(const int &size, const int &divideInto, const int &startPos, const int &jump, const int &cursorPos)
        {
            for (int beginning = startPos+jump, end = startPos+(size/divideInto)-jump, i = 0; i < divideInto; beginning = end+jump, end += (size/divideInto)+jump, i++) {
                if (beginning < cursorPos && cursorPos < end) return i;
            }
            return ELEMENT_NOT_FOUND;
        }

        // gets number of either block or tile
        int getRect(const int &size, const int &xPos, const int &yPos, const int &margin, const sf::Vector2i &cursorPos)
        {
            int row, col;
            row = calculateElement(size, 3, yPos, margin, cursorPos.y);
            col = calculateElement(size, 3, xPos, margin, cursorPos.x);
            if (row == ELEMENT_NOT_FOUND || col == ELEMENT_NOT_FOUND) return ELEMENT_NOT_FOUND;
            return getBlockNum(row)+getCol(col);
        }

        bool checkClicked(const int &startPos, const int &size, const int &cursor)
        {
            return (startPos < cursor && cursor < startPos+size);
        }

        // true if occupied, false if empty or present number is mistake
        bool checkIfOccupiedAndWrong(Board &board)
        {
            return (checkIfOccupied(board)
                && !board.isMistake(selectedBlock, selectedTile, board.actualBlocks[selectedBlock][selectedTile]));
        }

        // true if occupied, false if empty
        bool checkIfOccupied(Board &board) 
        {
            return board.actualBlocks[selectedBlock][selectedTile] != EMPTY_NUM;
        }

        void putHint(Board &board)
        {
            if (cooldown(COOLDOWN)) return;
            bool hintPlaced = false;
            while (!hintPlaced) {
                selectedBlock = rand()%SIZE, selectedTile = rand()%SIZE;
                if (board.actualBlocks[selectedBlock][selectedTile] == EMPTY_NUM) {
                    gameboard.blocks[selectedBlock].tiles[selectedTile].box.changeText(board.solvedBlocks[selectedBlock][selectedTile]);
                    gameboard.blocks[selectedBlock].tiles[selectedTile].box.hintHighlight = true;
                    hintPlaced = true;
                }
            }
            handleCorrect(board, board.solvedBlocks[selectedBlock][selectedTile]);
        }
};


#endif // GUI_H
