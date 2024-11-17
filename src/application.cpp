/*
Date: 10/11/2024

Application class controls the overall flow of the program.
*/

#include "../include/application.hpp"
#include "../include/macros.hpp"
#include "../include/gui.hpp"

namespace System
{
// Class methods
        /*
        Initializes the Application class.
        */
        Application::Application()
        {
                LOG_TRACE("Application::Application() called");

                runFlag = RunFlag::NONE;

                init();

                if (shouldRun())
                {
                        run();
                }
        }

        /*
        Destructs the Application class.
        */
        Application::~Application()
        {
                LOG_TRACE("Application::~Application() called");

                LOG_INFO("Application closed");

                runFlag = RunFlag::STOPPED;
        }
// Application methods
        /*
        Initializes the application.
        */
        void Application::init()
        {
                LOG_TRACE("Application::init() called");

                runFlag = RunFlag::RUN;

                LOG_INFO("Application initialized");
        }
        /*
        Runs the application.
        */
        void Application::run()
        {
                LOG_TRACE("Application::run() called");

                if (shouldRun())
                {
                        controlFlow();
                }

                close();
        }

        /*
        Controls the flow of the application.
        */
        void Application::controlFlow()
        {
                LOG_TRACE("Application::controlFlow() called");

                // Run the GUI
                try
                {
                        gui.run();
                }
                // Catch any exceptions
                catch (const std::exception& e)
                {
                        LOG_ERROR("Exception caught: {}", e.what());
                }

                runFlag = RunFlag::WILL_STOP;
        }

        /*
        Closes the application.
        */
        void Application::close()
        {
                LOG_TRACE("Application::close() called");

                LOG_INFO("Closing application...");

                runFlag = RunFlag::WILL_STOP;
        }
// Check methods
        /*
        Checks if the application should run.

        @return True if the application should run, false otherwise.
        */
        bool Application::shouldRun()
        {
                LOG_TRACE("Application::shouldRun() called");

                return runFlag == RunFlag::RUN;
        }
}