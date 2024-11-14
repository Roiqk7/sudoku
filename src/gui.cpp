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
                LOG_TRACE("GUI::GUI() called");

                init();
        }

        /*
        Destructor for GUI class.
        */
        GUI::~GUI()
        {
                LOG_TRACE("GUI::~GUI() called");
        }
// GUI methods
        /*
        Run the GUI.
        */
        void GUI::run()
        {
                LOG_TRACE("GUI::run() called");

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
                LOG_TRACE("GUI::waitEvent() called");

                sf::Event event;
                while (window.waitEvent(event))
                {
                        if (shouldClose(event))
                        {
                                window.close();
                        }
                        else if (isRelevantEvent(event))
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
                LOG_TRACE("GUI::render() called");

                window.clear();
                if (!scenes.empty())
                {
                        auto& scene = scenes.top();
                        scene.render(window);
                }
                window.display();
        }

        /*
        Initialize the GUI.

        @throw std::runtime_error if the assets failed to load.
        */
        void GUI::init()
        {
                LOG_TRACE("GUI::init() called");

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
                LOG_TRACE("GUI::handleEvent() called");

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
                LOG_TRACE("GUI::shouldClose() called");

                return event.type == sf::Event::Closed;
        }

        /*
        Check if the event is relevant.

        @param event The event to check.

        @return True if the event is relevant, false otherwise.
        */
        bool GUI::isRelevantEvent(const sf::Event& event) const
        {
                LOG_TRACE("GUI::isRelevantEvent() called");

                return event.type == sf::Event::MouseButtonPressed;
        }
} // namespace System