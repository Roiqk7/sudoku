/*
Date: 10/11/2024

Application class controls the overall flow of the program.
*/

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "globals.hpp"

namespace System
{
        class Application
        {
        public: // Methods
        // Class methods
                Application();
                ~Application();
        private: // Methods
        // Application methods
                void run();
                void controlFlow();
                void close();
        // Check methods
                bool shouldRun();
        };
}

#endif // !APPLICATION_HPP