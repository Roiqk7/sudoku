#ifndef GAMEBOARD_H
#define GAMEBOARD_H

// actual gameboard user sees

#include <array>
#include "board.h"
#include "constants.h"
#include "gui.h"
#include "hub.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>
#include "textBox.h"


class Gameboard {
    public:  
        // top left of the gameboard
        const int xPos = 0, yPos = Hub::hubYPos+Hub::hubHeight; 
        const int size = WIDTH;
        // space around board
        const int thinMargin = 2;
        const int thickMargin = 6;
        // block
        // size of one block
        const int blockSize = size/3;
        // size of one tile
        const int tileSize = blockSize/3-4; 
        // size of text within a tile
        const int textSize = tileSize+3;
        // size of one note
        const int noteSize = tileSize/3;
        
        // used to simplify rendering
        struct Note {
            sf::Text text;
            std::string textContent;
            const int fontSize = 20;
            bool show;

            void init(const int &xPos, const int &yPos, const int &number)
            {
                this->textContent = number+EMPTY_CHAR;
                text.setPosition(sf::Vector2f(xPos, yPos));
                text.setCharacterSize(fontSize);
                text.setFont(font);
                text.setString(textContent);
                show = false;
            }

            void call()
            {
                window.draw(text);
            }
        };
        struct Tile {
            int xPos, yPos;
            TextBox box;
            std::array<Note, SIZE> notes;
            bool showNotes;
        };
        struct Block {
            int xPos, yPos;
            sf::RectangleShape frame;
            std::array<Tile, SIZE> tiles;
            std::array<int, SIZE> numbers;
        };
        std::array<Block, SIZE> blocks;

        void createBlocks(Board &board)
        {
            // create 2d array where each row represents numbers of a block
            std::array<std::array<int, SIZE>, SIZE> blockNumbers;
            blockNumbers = board.actualBlocks;
            for (int i = 0; i < SIZE; i++) {
                // sets the position
                blocks[i].xPos = xPos+getCol(i)*blockSize;
                blocks[i].yPos = yPos+getRow(i)*blockSize;
                // assign block numbers to the block
                blocks[i].numbers = blockNumbers[i];
                // add graphics to the block
                setBlockGraphics(blocks[i]);
            }
        }

        void call()
        {
            render();
        }

    private:  

        /*
            ### #     # ### ####### ###    #    ####### ####### 
             #  ##    #  #     #     #    # #      #    #       
             #  # #   #  #     #     #   #   #     #    #       
             #  #  #  #  #     #     #  #     #    #    #####   
             #  #   # #  #     #     #  #######    #    #       
             #  #    ##  #     #     #  #     #    #    #       
            ### #     # ###    #    ### #     #    #    #######                                                  
        */  

        // each block consists of 9 TextBoxes and their frame
        void setBlockGraphics(Block &block)
        {
            setBlockFrame(block);
            initTilesForBlock(block);
        }

        void setBlockFrame(Block &block)
        {
            block.frame.setPosition(sf::Vector2f(block.xPos, block.yPos));
            block.frame.setSize(sf::Vector2f(blockSize, blockSize));
            block.frame.setFillColor(sf::Color{BOARD_OUTLINE_COLOR});
        }

        void initTilesForBlock(Block &block)
        {
            // fills from left to right, top to bottom
            for (int i = 0; i < SIZE; i++) {
                block.tiles[i].xPos = block.xPos+getCol(i)*tileSize+5;
                block.tiles[i].yPos = block.yPos+getRow(i)*tileSize+5;
                block.tiles[i].box = TextBox(MAIN_WINDOW_NUM, tileSize, block.tiles[i].xPos, block.tiles[i].yPos, 
                    navajoWhite, block.numbers[i]+EMPTY_CHAR, textSize, white, white, thinMargin);
                // to properly position the numbers
                block.tiles[i].box.moveText(15, -6);
                // notes
                initNotesForTile(block.tiles[i]);
                if (block.numbers[i] == EMPTY_NUM) block.tiles[i].showNotes = true;
                else block.tiles[i].showNotes = false;
            }
        }

        void initNotesForTile(Tile &tile)
        {
            int xPos, yPos;
            for (int i = 0; i < SIZE; i++) {
                xPos = tile.xPos+getCol(i)*noteSize+5;
                yPos = tile.yPos+getRow(i)*noteSize;
                tile.notes[i].init(xPos, yPos, i+1);
            }
        }

        /*
            ######  ####### #     # ######  ####### ######  
            #     # #       ##    # #     # #       #     # 
            #     # #       # #   # #     # #       #     # 
            ######  #####   #  #  # #     # #####   ######  
            #   #   #       #   # # #     # #       #   #   
            #    #  #       #    ## #     # #       #    #  
            #     # ####### #     # ######  ####### #     #                                               
        */

        void render()
        {
            drawBlocks();
        }

        void drawBlocks()
        {
            // blocks
            for (int i = 0; i < SIZE; i++) {
                window.draw(blocks[i].frame);
                // tiles
                for (int j = 0; j < SIZE; j++) {
                    blocks[i].tiles[j].box.call();
                    // notes
                    if (blocks[i].tiles[j].showNotes) {
                        for (int k = 0; k < SIZE; k++) {
                            if (blocks[i].tiles[j].notes[k].show) blocks[i].tiles[j].notes[k].call();
                        }
                    }
                }
            }
        }
};


#endif // GAMEBOARD_H