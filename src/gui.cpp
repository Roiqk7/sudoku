/*
Date: 10/11/2024

GUI class controls the graphical user interface of the program.
*/

#include "../include/macros.hpp"
#include "../include/gui.hpp"
#include <stdexcept>

namespace System
{
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

        @throws std::runtime_error if the assets failed to load.
        */
        void GUI::init()
        {
                // Setups the window
                window.create(sf::VideoMode(sf::Vector2u(
                        constants.WINDOW_WIDTH, constants.WINDOW_HEIGHT)),
                        "SUDOKU!");
        }
} // namespace System