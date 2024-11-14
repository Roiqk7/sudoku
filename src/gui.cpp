/*
Date: 10/11/2024

GUI class controls the graphical user interface of the program.
*/

#include "../include/macros.hpp"
#include "../include/gui.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
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
        Run the GUI.
        */
        void GUI::run()
        {
                while (window.isOpen())
                {
                        waitEvent();
                }
        }

        /*
        Wait for an event to occur.
        */
        void GUI::waitEvent()
        {
                sf::Event event;
                while (window.waitEvent(event))
                {
                        if (shouldClose(event))
                        {
                                window.close();
                        }
                        else
                        {
                                handleEvent(event);
                                render();
                        }
                }
        }

        /*
        Render the GUI.
        */
        void GUI::render()
        {
                window.clear();
                auto& scene = scenes.top();
                scene.render(window);
                window.display();
        }

        /*
        Initialize the GUI.

        @throw std::runtime_error if the assets failed to load.
        */
        void GUI::init()
        {
                const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

                // Setups the window
                window.create(desktop, "Sudoku");
        }

        /*
        Handle an event.

        @param event The event to handle.
        */
        void GUI::handleEvent(const sf::Event& event)
        {
                // Click event
                if (event.type == sf::Event::MouseButtonPressed)
                {
                        auto& scene = scenes.top();
                        std::weak_ptr<Command> command;
                        scene.retrieveClickedCommand(event.mouseButton.x,
                                event.mouseButton.y, command);
                        if (!command.expired())
                        {
                                invoker.submitCommand(command);
                        }
                }

                // Add more events if needed...

                invoker.processCommands();
        }
// Checker
        /*
        Check if the window should close.

        @param event The event to check.

        @return True if the window should close, false otherwise.
        */
        bool GUI::shouldClose(const sf::Event& event) const
        {
                return event.type == sf::Event::Closed;
        }

} // namespace System