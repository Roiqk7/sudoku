/*
Date: 09/11/2024

Description: This file contains the main function.
*/

#include "../include/application.hpp"
#include "../include/macros.hpp"

int main()
{
        LOG_TRACE("main() called");

        #ifdef DEVELOPMENT
        SET_LOG_LEVEL_DEBUG();
        #endif // DEVELOPMENT

        System::Application app;

        return 0;
}