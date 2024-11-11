/*
Date: 10/11/2024

Application class controls the overall flow of the program.
*/

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "macros.hpp"
#include "gui.hpp"

namespace System
{
        enum class RunFlag
        {
                NONE = 0,
                RUN,
                WILL_STOP,
                STOPPED
        };

        class Application
        {
        public: // Methods
        // Class methods
                Application();
                ~Application();
        private: // Methods
        // Application methods
                void init();
                void run();
                void controlFlow();
                void close();
        // Check methods
                bool shouldRun();
        private: // Variables
                RunFlag runFlag;
                GUI gui;
        };
}

#endif // !APPLICATION_HPP