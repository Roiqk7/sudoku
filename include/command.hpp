/*
Date: 13/11/2024

Command class used to store commands for buttons in the scene. Following the command pattern.
*/

#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <functional>

namespace System
{
        class Command
        {
        public: // Methods
        // Class methods
                Command(std::function<void()> command);
                ~Command() = default;
        // Command methods
                virtual void execute() = 0;
        private: // Variables
                std::function<void()> command;
        };
}

#endif // !COMMAND_HPP