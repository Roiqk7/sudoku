/*
Date: 10/11/2024

GUI class controls the graphical user interface of the program.
*/

#ifndef GUI_HPP
#define GUI_HPP

#include "gameHandler.hpp"
#include "invoker.hpp"
#include "music.hpp"
#include "scene.hpp"
#include <memory>
#include <list>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

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
        // Getter
                sf::RenderWindow& getWindow();
                Sudoku::GameHandler& getGameHandler();
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
                std::list<Scene> scenes;                                // Scenes in the GUI
                Music music;                                            // Music in the application
        };
}

#endif // !GUI_HPP