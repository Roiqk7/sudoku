/*
Date: 09/11/2024

Description: This file contains global variables, macros etc. that are used throughout the program.

Notes: x
*/

#ifndef MACROS_HPP
#define MACROS_HPP

#ifdef DEVELOPMENT
// Include the spdlog library for logging
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
// Macro for development logging
#define LOG_TRACE(...) spdlog::trace(__VA_ARGS__)
#define LOG_DEBUG(...) spdlog::debug(__VA_ARGS__)
#define LOG_INFO(...) spdlog::info(__VA_ARGS__)
#define LOG_WARN(...) spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)
#define LOG_CRITICAL(...) spdlog::critical(__VA_ARGS__)
// Macros to set log level
#define SET_LOG_LEVEL_TRACE() spdlog::set_level(spdlog::level::trace)
#define SET_LOG_LEVEL_DEBUG() spdlog::set_level(spdlog::level::debug)
#define SET_LOG_LEVEL_INFO() spdlog::set_level(spdlog::level::info)
#define SET_LOG_LEVEL_WARN() spdlog::set_level(spdlog::level::warn)
#define SET_LOG_LEVEL_ERROR() spdlog::set_level(spdlog::level::err)
#define SET_LOG_LEVEL_CRITICAL() spdlog::set_level(spdlog::level::critical)
#define SET_LOG_LEVEL_OFF() spdlog::set_level(spdlog::level::off)
// Macro to set the log file
#define SET_LOG_FILE(filename) \
{ \
        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>(); \
        auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(filename, true); \
        std::vector<spdlog::sink_ptr> sinks {console_sink, file_sink}; \
        auto logger = std::make_shared<spdlog::logger>("multi_sink", sinks.begin(), sinks.end()); \
        spdlog::set_default_logger(logger); \
}
#else // RELEASE
// Define macros as no-operation if not in development mode
#define LOG_TRACE(...) (void)0
#define LOG_DEBUG(...) (void)0
#define LOG_INFO(...) (void)0
#define LOG_WARN(...) (void)0
#define LOG_ERROR(...) (void)0
#define LOG_CRITICAL(...) (void)0

#define SET_LOG_LEVEL_TRACE() (void)0
#define SET_LOG_LEVEL_DEBUG() (void)0
#define SET_LOG_LEVEL_INFO() (void)0
#define SET_LOG_LEVEL_WARN() (void)0
#define SET_LOG_LEVEL_ERROR() (void)0
#define SET_LOG_LEVEL_CRITICAL() (void)0
#define SET_LOG_LEVEL_OFF() (void)0

#define SET_LOG_FILE(filename) (void)0
#endif // RELEASE

#endif // !MACROS_HPP