#include "../include/macros.hpp"
#include "../include/signalHandler.hpp"
#include <csignal>
#include <cstdlib>

void signalHandler(int signal)
{
        LOG_CRITICAL("Signal {} received. Exiting...", signal);

        exit(signal);
}