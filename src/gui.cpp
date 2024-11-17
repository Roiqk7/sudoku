/*
Date: 10/11/2024

GUI class controls the graphical user interface of the program.
*/

#include "../include/macros.hpp"
#include "../include/gui.hpp"
#include "../include/scenes.hpp"
#include <memory>
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

                LOG_DEBUG("GUI scene count: {}", scenes.size());

                window.clear();
                if (!scenes.empty())
                {
                        for (const auto& scene : scenes)
                        {
                                LOG_DEBUG("Rendering {} scene with {} objects", scene.name, scene.size());
                                scene.render(window);
                        }
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

                // Create the default scene
                Scene scene("Default");
                createDefaultScene(scene, window);
                scenes.push_back(std::move(scene));

                // Render the default scene
                render();
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
                        // We assume the most relevant scene is at the back
                        // thus we iterate in reverse and return first valid command
                        for (auto it = scenes.rbegin(); it != scenes.rend(); ++it)
                        {
                                auto& scene = *it;
                                std::weak_ptr<Command> command;
                                scene.retrieveClickedCommand(event.mouseButton.x,
                                        event.mouseButton.y, command);
                                if (!command.expired())
                                {
                                        invoker.submitCommand(command);
                                        // Exit the loop once a valid command is found
                                        break;
                                }
                        }
                }

                // Update the scenes if the window is resized
                if (event.type == sf::Event::Resized)
                {
                        for (auto& scene : scenes)
                        {
                                scene.update();
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

                return event.type == sf::Event::MouseButtonPressed
                        || event.type == sf::Event::Resized;
        }
} // namespace System