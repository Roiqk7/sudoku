/*
Date: 09/11/2024

Description: This file contains the main function.
*/

#include "../include/globals.hpp"

int main()
{
        LOG_TRACE("main() called");

        #ifdef DEVELOPMENT
        SET_LOG_LEVEL_DEBUG();
        #endif // DEVELOPMENT

        return 0;
}