/*
Date: 10/11/2024

Application class controls the overall flow of the program.
*/

#include "../include/application.hpp"

namespace System
{
// Class methods
        Application::Application()
        {
                LOG_TRACE("Application::Application() called");
        }

        Application::~Application()
        {
                LOG_TRACE("Application::~Application() called");
        }
// Application methods
        void Application::run()
        {
                LOG_TRACE("Application::run() called");

                while (shouldRun())
                {
                        controlFlow();
                }

                close();
        }

        void Application::controlFlow()
        {
                LOG_TRACE("Application::controlFlow() called");
        }

        void Application::close()
        {
                LOG_TRACE("Application::close() called");
        }
}