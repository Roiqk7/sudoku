#include "../include/macros.hpp"
#include "../include/signalHandler.hpp"
#include <csignal>
#include <cstdlib>

void signalHandler(int signal)
{
        switch (signal)
        {
                // Interrupt signal (Cmd + C)
                case SIGINT:
                        LOG_CRITICAL("SIGINT received. Exiting...");
                        break;
                // Segmentation fault
                case SIGSEGV:
                        LOG_CRITICAL("SIGSEGV received. Exiting...");
                        break;
                // All other signals
                default:
                        LOG_CRITICAL("Signal {} received. Exiting...", signal);
                        break;
        }

        exit(signal);
}