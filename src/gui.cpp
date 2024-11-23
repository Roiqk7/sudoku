/*
Date: 10/11/2024

GUI class controls the graphical user interface of the program.
*/

#include "../include/macros.hpp"
#include "../include/gui.hpp"
#include "../include/scenes.hpp"
#include <algorithm>
#include <chrono>
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
// Getter
        /*
        Get the window.

        @return The window.
        */
        sf::RenderWindow& GUI::getWindow()
        {
                LOG_TRACE("GUI::getWindow() called");

                return window;
        }

        /*
        Get the game handler.

        @return The game handler.
        */
        Sudoku::GameHandler& GUI::getGameHandler()
        {
                LOG_TRACE("GUI::getGameHandler() called");

                return gameHandler;
        }
// GUI methods
        /*
        Initialize the GUI.

        @throw std::runtime_error if the assets failed to load.
        */
        void GUI::init()
        {
                LOG_TRACE("GUI::init() called");

                // Setups the window
                sf::VideoMode mode = sf::VideoMode(1400, 800);
                window.create(mode, "SUDOKU!");

                LOG_DEBUG("Window created with size {}x{}", mode.width, mode.height);

                // Create the default scene
                // This scene is always active but should stay hidden
                // behind other scenes
                scenes.emplace_back("Default");
                createDefaultScene(scenes.back(), window);

                // Create the background scene
                scenes.emplace_back("Background");
                createBackgroundScene(scenes.back(), window);

                // Create the welcome scene
                // Welcome scene is used as general scene used by
                // the application and will be rewritten by other scenes
                scenes.emplace_back("Welcome");
                createWelcomeScene(scenes.back(), *this);

                render();
        }

        /*
        Wait for an event to occur. This is the main loop of the GUI.

        @note This function is blocking.
        */
        void GUI::waitEvent()
        {
                LOG_TRACE("GUI::waitEvent() called");

                sf::Event event;
                // Main loop
                while (window.waitEvent(event))
                {
                        // Close the window if the event is a close event
                        if (shouldClose(event))
                        {
                                window.close();
                                // Start the close process of the application
                                break;
                        }
                        // Otherwise, handle the event
                        else if (isRelevantEvent(event))
                        {
                                #ifdef DEVELOPMENT
                                auto start = std::chrono::high_resolution_clock::now();
                                #endif // DEVELOPMENT

                                handleEvent(event);
                                // Note: Does nothing removeInactiveScenes();

                                {
                                        #ifdef DEVELOPMENT
                                        auto end = std::chrono::high_resolution_clock::now();
                                        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
                                        scenes.emplace_back("Execution Time");
                                        createExecutionTimeScene(scenes.back(), *this, duration);
                                        #endif // DEVELOPMENT
                                }

                                render();

                                {
                                        #ifdef DEVELOPMENT
                                        // Delete the execution time scene
                                        if (scenes.back().name == "Execution Time")
                                        {
                                                scenes.pop_back();
                                        }
                                        #endif // DEVELOPMENT
                                }
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
                        for (const auto& scene : scenes)
                        {
                                LOG_TRACE("Rendering {} scene with {} objects", scene.name, scene.size());
                                scene.render(window);
                        }
                }

                window.display();
        }

        /*
        Remove inactive scenes.
        */
        void GUI::removeInactiveScenes()
        {
                LOG_TRACE("GUI::removeInactiveScenes() called");

                scenes.erase(std::remove_if(scenes.begin(), scenes.end(),
                        [](const Scene& scene) { return !scene.active; }),
                        scenes.end());
        }
// Event handling
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
                        handleMouseClick(event);
                }

                // Add more events if needed...

                invoker.processCommands();
        }

        /*
        Handle a mouse click event.

        @param event The event to handle.
        */
        void GUI::handleMouseClick(const sf::Event& event)
        {
                // We assume the most relevant scene is at the back
                // thus we iterate in reverse and return first valid command
                for (auto it = scenes.rbegin(); it != scenes.rend(); it++)
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