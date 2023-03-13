#pragma once

#define RELAY_LOG_TRACE(...)                          { }
#define RELAY_LOG_DEBUG(...)                          { }
#define RELAY_LOG_INFO(...)                           { }
#define RELAY_LOG_WARNING(...)                        { }
#define RELAY_LOG_ERROR(...)                          { }
#define RELAY_LOG_CRITICAL(...)                       { }

//#include <cstdio>

//#define RELAY_LOG_TRACE(module_enum, string, ...)      {fprintf(stdout,  string "\n", __VA_ARGS__); fflush(stdout);}
//#define RELAY_LOG_DEBUG(module_enum, string, ...)      {fprintf(stdout,  string "\n", __VA_ARGS__); fflush(stdout);}
//#define RELAY_LOG_INFO(module_enum, string, ...)       {fprintf(stdout,  string "\n", __VA_ARGS__); fflush(stdout);}
//#define RELAY_LOG_WARNING(module_enum, string, ...)    {fprintf(stdout,  string "\n", __VA_ARGS__); fflush(stdout);}
//#define RELAY_LOG_ERROR(module_enum, string, ...)      {fprintf(stdout,  string "\n", __VA_ARGS__); fflush(stdout);}
//#define RELAY_LOG_CRITICAL(module_enum, string, ...)   {fprintf(stdout,  string "\n", __VA_ARGS__); fflush(stdout);}
