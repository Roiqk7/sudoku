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

        struct Constants
        {
                const int WINDOW_WIDTH = 800;                           // Width of the window
                const int WINDOW_HEIGHT = 600;                          // Height of the window
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
                State state;                                            // Used to determine what to render
                Constants constants;                                    // Constants for the GUI
                sf::RenderWindow window;                                // The window to render to
                Assets assets;                                          // Assets for the game
                Sudoku::GameHandler gameHandler;                        // Interface for the game logic
        };
}

#endif // !GUI_HPP