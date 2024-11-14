/*
Date: 10/11/2024

GUI class controls the graphical user interface of the program.
*/

#ifndef GUI_HPP
#define GUI_HPP

#include "gameHandler.hpp"
#include "invoker.hpp"
#include "scene.hpp"
#include <memory>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <stack>

namespace System
{
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
                void waitEvent();
                void render();
        private: // Methods
        // GUI methods
                void init();
                void handleEvent(const sf::Event& event);
        // Checker
                bool shouldClose(const sf::Event& event) const;
        private: // Variables
                Constants constants;                                    // Constants for the GUI
                Invoker invoker;                                        // Invoker to execute commands in the GUI
                sf::RenderWindow window;                                // The window to render to
                Sudoku::GameHandler gameHandler;                        // Interface for the game logic
                std::stack<Scene> scenes;                               // Scenes in the GUI (top is current)
        };
}

#endif // !GUI_HPP