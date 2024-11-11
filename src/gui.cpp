/*
Date: 10/11/2024

GUI class controls the graphical user interface of the program.
*/

#include "../include/globals.hpp"
#include "../include/gui.hpp"
#include <stdexcept>

namespace System
{
// Assets helper struct
        /*
        Constructor for Assets struct.

        @throws std::runtime_error if assets fail to load.
        */
        Assets::Assets()
        {
                // Load arrow texture
                if (!arrowTexture.loadFromFile("assets/arrow.png")
                        || !pencilTexture.loadFromFile("assets/pencil.png")
                        || !titleFont.loadFromFile("assets/arial.ttf")
                        || !font.loadFromFile("assets/arial.ttf"))
                {
                        throw std::runtime_error("Failed to load game assets.");
                }
        }

// Class methods
        /*
        Constructor for GUI class.
        */
        GUI::GUI()
        {
                init();
        }

        /*
        Destructor for GUI class.
        */
        GUI::~GUI()
        {
        }
// GUI methods
        /*
        Render the GUI.
        */
        void GUI::render()
        {
                // TODO: Implement render method
        }

        /*
        Update the window.
        */
        void GUI::update()
        {
                // TODO: Implement update method
        }

        /*
        Wait for an event to occur.
        */
        void GUI::waitEvent()
        {
                // TODO: Implement waitEvent method
        }

        /*
        Initialize the GUI.
        */
        void GUI::init()
        {
                // Setups the window
                window.create(sf::VideoMode(sf::Vector2u(WIDTH, HEIGHT)), "SUDOKU!");
        }
} // namespace System