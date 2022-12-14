#ifndef TIMER_H
#define TIMER_H

// this handles everything related to time in seconds

#include <chrono>
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <string.h>
#include <time.h>


void startTimer();
void stopTime();
time_t getTime();
void setTime(const int &desiredTime);
void setTime(const time_t &desiredTime);
std::string formatTime(time_t &seconds);
std::string getFormattedTime();
void stopwatch();
void stopwatch2();


time_t startTime = time(NULL);
bool timeStopped = false;

/*
    ####### ### #     # ####### ######  
       #     #  ##   ## #       #     # 
       #     #  # # # # #       #     # 
       #     #  #  #  # #####   ######  
       #     #  #     # #       #   #   
       #     #  #     # #       #    #  
       #    ### #     # ####### #     #                             
*/

// measures time in seconds
void startTimer()
{
    startTime = time(NULL);
}

void stopTime()
{
    static time_t resumeAt;
    if (!timeStopped) {
        resumeAt = getTime();
        timeStopped = true;
        return;
    }
    timeStopped = false;
    setTime(resumeAt);
}

time_t getTime()
{
    return time(NULL)-startTime;
}

void setTime(const int &desiredTime)
{
    startTime = time(NULL)-desiredTime;
}

void setTime(const time_t &desiredTime)
{
    startTime = time(NULL)-desiredTime;
}

// formats time in seconds into eg. 01:12
std::string formatTime(time_t &seconds)
{
    time_t minutes;
    minutes = seconds/60;
    seconds %= 60;
    std::ostringstream formattedTime;
    formattedTime << std::setfill('0') << std::setw(2) << minutes << ':' << std::setfill('0') << std::setw(2) << seconds;
    return formattedTime.str();
}

std::string getFormattedTime()
{
    time_t seconds = getTime();
    return formatTime(seconds);
}

/*
     #####  ####### ####### #       ######  ####### #     # #     # 
    #     # #     # #     # #       #     # #     # #  #  # ##    # 
    #       #     # #     # #       #     # #     # #  #  # # #   # 
    #       #     # #     # #       #     # #     # #  #  # #  #  # 
    #       #     # #     # #       #     # #     # #  #  # #   # # 
    #     # #     # #     # #       #     # #     # #  #  # #    ## 
     #####  ####### ####### ####### ######  #######  ## ##  #     # 
 
*/

// if true then cooldown is active
bool cooldown(const int &cooldownTime)
{
    static bool state = false;
    static int endOfCooldown;
    static std::chrono::high_resolution_clock::time_point start;
    if (!state) {
        state = true;
        endOfCooldown = cooldownTime;
        start = std::chrono::high_resolution_clock::now();  
        return state;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    auto executionTime = duration.count();
    if (executionTime < endOfCooldown) return state;
    state = false;
    return state;
}

/*
     #####  ####### ####### ######  #     #    #    #######  #####  #     # 
    #     #    #    #     # #     # #  #  #   # #      #    #     # #     # 
    #          #    #     # #     # #  #  #  #   #     #    #       #     # 
     #####     #    #     # ######  #  #  # #     #    #    #       ####### 
          #    #    #     # #       #  #  # #######    #    #       #     # 
    #     #    #    #     # #       #  #  # #     #    #    #     # #     # 
     #####     #    ####### #        ## ##  #     #    #     #####  #     #                                                                     
*/

// used as developer tool to analyze run time
// measures time in microseconds
void stopwatch()
{    
    static int state = 0;
    static std::chrono::high_resolution_clock::time_point start;
    if (state == 0) {
        state = 1;
        start = std::chrono::high_resolution_clock::now();  
        return;
    }
    state = 0;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    auto executionTime = duration.count();
    std::cout << "Finished in " << executionTime << " microseconds\n\n";
}

// used as developer tool to analyze run time
// measures time in microseconds
void stopwatch2()
{    
    static int state = 0;
    static std::chrono::high_resolution_clock::time_point start;
    if (state == 0) {
        state = 1;
        start = std::chrono::high_resolution_clock::now();  
        return;
    }
    state = 0;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    auto executionTime = duration.count();
    std::cout << "2. Finished in " << executionTime << " microseconds\n\n";
}    

// used as developer tool to analyze run time
// measures time in microseconds
void stopwatch3()
{    
    static int state = 0;
    static std::chrono::high_resolution_clock::time_point start;
    if (state == 0) {
        state = 1;
        start = std::chrono::high_resolution_clock::now();  
        return;
    }
    state = 0;
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    auto executionTime = duration.count();
    std::cout << "3. Finished in " << executionTime << " microseconds\n\n";
}  


#endif // TIMER_H