/*
Date: 13/11/2024

Invoker class is used to execute commands. Following the command pattern.
*/

#include "command.hpp"
#include "invoker.hpp"
#include "macros.hpp"
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

        @param command Command to submit.
        */
        void Invoker::submitCommand(const std::weak_ptr<Command>& command) noexcept
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
                        const auto& command = commands.front().lock();
                        if (command)
                        {
                                command->execute();
                        }
                        commands.pop();
                }
        }

        /*
        Check if the queue is empty.

        @return True if the queue is empty, false otherwise.
        */
        bool Invoker::empty() const noexcept
        {
                LOG_TRACE("Invoker::empty() called.");

                return commands.empty();
        }
}