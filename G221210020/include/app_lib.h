/**
* @file app_lib.h
* @description Contains definitions for boolean literals, app_assert macro and
*					    other functions that doesn't belong to anywhere else.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef APP_LIB_H
#define APP_LIB_H

#include <stdlib.h>

/* Boolean type definition. */
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L /* stdbool.h is not in standard until C99. */
	#include <stdbool.h>
#else
	#define bool int
	#define false 0
	#define true !false
	#define __bool_true_false_are_defined 1
#endif

/* Equivelent to fprintf(stderr, format, ...), defined for ease of use in app_assert macro. */
void stderr_printf(char* format, ...);

/*
Checks if condition is satisfied.
If condition is satisfied, code execution will be resumed.
If condition is not satisfied, writes error to stderr in given format with
given format args and terminates the program.
*/
#define app_assert(condition, formatArgs) do {							\
	if (condition) break;												\
																		\
	stderr_printf("\x1b[31m");											\
	stderr_printf("%s:%d: app_assert failed: ", __FILE__, __LINE__);	\
	stderr_printf formatArgs;											\
	stderr_printf("\x1b[0m"); 											\
	stderr_printf("\n");												\
 																		\
	exit(EXIT_FAILURE); 												\
} while(false);

/* Generic function macro for returning the smaller number between two numbers. */
#define min(x, y) (((x) < (y)) ? (x) : (y))

/* Generic function macro for returning the bigger number between two numbers. */
#define max(x, y) (((x) > (y)) ? (x) : (y))

/* Generic function macro for returning number within given bounds. */
#define clamp(x, bottom, top) (((x) < (bottom)) ? (bottom) : (((x) > (top)) ? (top) : (x)))

/* Maximum number of characters an integer can take when converted to string. */
#define ITOA_MAX_SIZE (size_t)11

/* Returns the number of UTF-8 continuation bytes stored in string. */
size_t getUtf8ContinuationByteCount(char* str);

/* Duplicates given string into a new malloc'ed memory. Returned pointer must be freed by the user. */
char* duplicateString(char* str);

#endif