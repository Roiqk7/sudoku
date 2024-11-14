/*
Date: 14/11/2024

This file provides a few tests for the Invoker class.
*/

#ifndef TEST
#error "Tried to compile a test file without the TEST macro defined. Aborting compilation."
#else

#include "../../include/command.hpp"
#include "../../include/invoker.hpp"
#include <array>
#include <gtest/gtest.h>

/*
Test for the Invoker::submitCommand() method.

Expected: No exceptions are thrown and the command is added to the queue.
*/
TEST(Invoker, SubmitCommand)
{
        System::Invoker invoker;
        std::shared_ptr<System::Command> command = std::make_shared<System::Command>([](){});

        ASSERT_TRUE(invoker.empty());

        invoker.submitCommand(command);

        ASSERT_FALSE(invoker.empty());
}

/*
Test for the Invoker::submitCommand() method with a nullptr.

Expected: No exceptions are thrown and the command is added to the queue.
*/
TEST(Invoker, SubmitCommandNullptr)
{
        System::Invoker invoker;

        ASSERT_TRUE(invoker.empty());

        invoker.submitCommand(std::shared_ptr<System::Command>());

        ASSERT_FALSE(invoker.empty());
}

/*
Test for the Invoker::processCommands() method.

Expected: No exceptions are thrown and the command is executed.
*/
TEST(Invoker, ProcessCommands)
{
        System::Invoker invoker;
        bool executed = false;
        std::shared_ptr<System::Command> command = std::make_shared<System::Command>([&executed]()
        {
                executed = true;
        });

        invoker.submitCommand(command);
        invoker.processCommands();

        ASSERT_TRUE(executed);
}

/*
Test for the Invoker::processCommands() method with a nullptr.

Expected: No exceptions are thrown and the command is not executed.
*/
TEST(Invoker, ProcessCommandsNullptr)
{
        System::Invoker invoker;

        ASSERT_NO_THROW(
                {
                        invoker.submitCommand(std::shared_ptr<System::Command>());
                        invoker.processCommands();
                }
        );
}

#endif // !TEST