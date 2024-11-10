/*
Date: 10/11/2024

GUI class controls the graphical user interface of the program.
*/

#ifndef GUI_HPP
#define GUI_HPP

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
                sf::RenderWindow window;
                State state;
        };
}

#endif // !GUI_HPP