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
#include <vector>

namespace System
{
        class GUI
        {
        public: // Methods
        // Class methods
                GUI();
                ~GUI();
        // GUI methods
                void run();
        private: // Methods
        // GUI methods
                void init();
                void waitEvent();
                void render();
                void removeInactiveScenes();
        // Event handling
                void handleEvent(const sf::Event& event);
                void handleMouseClick(const sf::Event& event);
        // Checker
                bool shouldClose(const sf::Event& event) const;
                bool isRelevantEvent(const sf::Event& event) const;
        private: // Variables
        // Variables
                Invoker invoker;                                        // Invoker to execute commands in the GUI
                sf::RenderWindow window;                                // The window to render to
                Sudoku::GameHandler gameHandler;                        // Interface for the game logic
                std::vector<Scene> scenes;                              // Scenes in the GUI (top is current)
        };
}

#endif // !GUI_HPP