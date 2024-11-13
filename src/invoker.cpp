/*
Date: 13/11/2024

Invoker class is used to execute commands. Following the command pattern.
*/

#include "../include/command.hpp"
#include "../include/invoker.hpp"
#include "../include/macros.hpp"
#include <memory>
#include <queue>

namespace System
{
// Class methods
        /*
        Construct the Invoker object.
        */
        Invoker::Invoker()
        {
                LOG_TRACE("Invoker::Invoker() called.");
        }

        /*
        Destruct the Invoker object.
        */
        Invoker::~Invoker()
        {
                LOG_TRACE("Invoker::~Invoker() called.");
        }
// Invoker methods
        /*
        Submit a command to the invoker.
        */
        void Invoker::submitCommand(std::shared_ptr<Command> command)
        {
                LOG_TRACE("Invoker::submitCommand() called.");

                commands.push(command);
        }

        /*
        Process all commands in the queue.
        */
        void Invoker::processCommands()
        {
                LOG_TRACE("Invoker::processCommands() called.");

                while (!commands.empty())
                {
                        auto& command = commands.front();
                        command->execute();
                        commands.pop();
                }
        }
}