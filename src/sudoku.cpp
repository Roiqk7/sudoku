/*
Date: 09/11/2024

Description: This file contains the main function.
*/

#include "../include/application.hpp"
#include "../include/macros.hpp"
#include "../include/signalHandler.hpp"
#include <csignal>

int main()
{
        #ifdef DEVELOPMENT
        SET_LOG_LEVEL_DEBUG();
        LOG_TRACE("main() called");
        #endif // DEVELOPMENT

        // Set up signal handling
        std::signal(SIGINT, signalHandler);
        std::signal(SIGSEGV, signalHandler);

        // Run the application
        System::Application app;

        return 0;
}