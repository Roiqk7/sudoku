/*
Date: 13/11/2024

Invoker class is used to execute commands. Following the command pattern.
*/

#ifndef INVOKER_HPP
#define INVOKER_HPP

#include "command.hpp"
#include "macros.hpp"
#include <memory>
#include <queue>

namespace System
{
        class Invoker
        {
        public: // Methods
        // Class methods
                Invoker();
                ~Invoker();
        // Invoker methods
                void submitCommand(const std::weak_ptr<Command>& command) noexcept;
                void processCommands();
                bool empty() const noexcept;
        private: // Variables
                std::queue<std::weak_ptr<Command>> commands;
        };
}

#endif // !INVOKER_HPP