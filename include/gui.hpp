/*
Date: 10/11/2024

GUI class controls the graphical user interface of the program.
*/

#ifndef GUI_HPP
#define GUI_HPP

#include "gameHandler.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

namespace System
{
        enum class State
        {
                NONE = 0,
                MENU,
                GAME
        };

        struct Assets
        {
                sf::Texture arrowTexture;                               // Arrow texture (undo pick a number)
                sf::Texture pencilTexture;                              // Pencil texture (for notes)
                sf::Font titleFont;                                     // Font for the title
                sf::Font font;                                          // Font for the game

                Assets();
        };

        class GUI
        {
        public: // Methods
        // Class methods
                GUI();
                ~GUI();
        // GUI methods
                void render();
                void update();
                void waitEvent();
        private: // Methods
                void init();
        private: // Variables
                sf::RenderWindow window;                                // The window to render to
                State state;                                            // Used to determine what to render
                Sudoku::GameHandler gameHandler;                        // Interface for the game logic
        };
}

#endif // !GUI_HPP