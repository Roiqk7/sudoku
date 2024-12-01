/*
Date: 09/11/2024

Description: This file contains the main function.
*/

#include "../include/application.hpp"
#include "../include/macros.hpp"
#include "../include/signalHandler.hpp"
#include <csignal>
// Uncomment if you want to enable logging to a file #include <filesystem>

int main()
{
        #ifdef DEVELOPMENT
        // Note: Uncomment the following lines to enable logging to a file
        // std::filesystem::create_directories("log");
        // std::filesystem::path logPath = std::filesystem::current_path() / "log" / "log.txt";
        // SET_LOG_FILE(logPath.string());
        SET_LOG_LEVEL_DEBUG();
        LOG_TRACE("main() called");
        // LOG_DEBUG("Log file set to: {}", logPath.string());
        #endif // DEVELOPMENT

        // Set up signal handling
        std::signal(SIGINT, signalHandler);
        std::signal(SIGSEGV, signalHandler);

        // Run the application
        System::Application app;

        return 0;
}