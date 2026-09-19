#ifndef HEADER_MALON_ERROR
#define HEADER_MALON_ERROR

#include <stdio.h>

#define ENABLE_DEBUG 1

	#if ENABLE_DEBUG
	    #define LOG_DEBUG(fmt, ...) \
	        fprintf(stderr, "[DEBUG] (%s:%d in %s): " fmt "\n", \
	                __FILE__, __LINE__, __func__, ##__VA_ARGS__)
	#else
	    #define LOG_DEBUG(fmt, ...) ((void)0)
	#endif

#define LOG_ERROR(fmt, ...) \
    fprintf(stderr, "[ERROR] (%s:%d in %s): " fmt "\n", \
            __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define ERROR_RETURN(code, fmt, ...) \
    do { \
        LOG_ERROR(fmt, ##__VA_ARGS__); \
        return (code); \
    } while (0)

#endif
