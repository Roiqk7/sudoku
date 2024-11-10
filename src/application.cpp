/*
Date: 10/11/2024

Application class controls the overall flow of the program.
*/

#include "../include/application.hpp"

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

                runFlag = RunFlag::RUN;

                run();
        }

        /*
        Destructs the Application class.
        */
        Application::~Application()
        {
                LOG_TRACE("Application::~Application() called");

                runFlag = RunFlag::STOPPED;
        }
// Application methods
        /*
        Initializes the application.
        */
        void Application::init()
        {
                LOG_TRACE("Application::init() called");
        }
        /*
        Runs the application.
        */
        void Application::run()
        {
                LOG_TRACE("Application::run() called");

                while (shouldRun())
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

                // TODO: Implement the control flow
        }

        /*
        Closes the application.
        */
        void Application::close()
        {
                LOG_TRACE("Application::close() called");

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