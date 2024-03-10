#pragma once

#define  ENABLE_LOG    // whether enable log output

#ifdef ENABLE_LOG

#define LOG_TRACE(fmt, ...)			my_log(fmt, ##__VA_ARGS__)
#define LOG_DEBUG(fmt, ...)			my_log(fmt, ##__VA_ARGS__)
#define LOG_INFO(fmt, ...)			my_log(fmt, ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...)		my_log(fmt, ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...)			my_log(fmt, ##__VA_ARGS__)
#define LOG_FATAL(fmt, ...)			my_log(fmt, ##__VA_ARGS__)
#define LOG_REPORT(fmt, ...)		my_log(fmt, ##__VA_ARGS__)

#else

#define LOG_TRACE(fmt, ...)			
#define LOG_DEBUG(fmt, ...)			
#define LOG_INFO(fmt, ...)			
#define LOG_WARNING(fmt, ...)		
#define LOG_ERROR(fmt, ...)			
#define LOG_FATAL(fmt, ...)			
#define LOG_REPORT(fmt, ...)		
#endif



void my_log(const char *pszFormat, ...);

