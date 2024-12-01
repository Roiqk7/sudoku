/*
Date: 13/11/2024

Command class used to store commands for buttons in the scene. Following the command pattern.
*/

#include "command.hpp"
#include "macros.hpp"
#include <functional>

namespace System
{
        /*
        Constructor for the Command class.
        */
        Command::Command(std::function<void()> command)
                : command(command)
        {
                LOG_TRACE("Command::Command() called");
        }

        /*
        Execute the command.
        */
        void Command::execute()
        {
                LOG_TRACE("Command::execute() called");

                command();
        }
}