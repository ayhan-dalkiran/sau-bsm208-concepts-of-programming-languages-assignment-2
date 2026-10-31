/**
* @file app_lib.c
* @description Contains implementations for functions defined in app_lib.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "app_lib.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void stderr_printf(char* format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
}

size_t getUtf8ContinuationByteCount(char* string) {
	size_t stringSize = 0;
	size_t utf8ContinuationByteCount = 0;
	unsigned char character = (unsigned char)string[0];

	while (character != '\0') {
		stringSize += 1;

		if ((character >> 6) == 0x02) utf8ContinuationByteCount += 1;

		character = (unsigned char)string[stringSize];
	}

	return utf8ContinuationByteCount;
}

char* duplicateString(char* string) {
	size_t stringSize = strlen(string);
	char* duplicate = (char*)malloc(stringSize + 1);

	return strcpy(duplicate, string);
}
