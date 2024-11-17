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
        LOG_TRACE("main() called");

        #ifdef DEVELOPMENT
        SET_LOG_LEVEL_DEBUG();
        #endif // DEVELOPMENT

        signal(SIGSEGV, signalHandler);

        System::Application app;

        return 0;
}