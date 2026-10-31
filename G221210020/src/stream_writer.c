/**
* @file stream_writer.c
* @description Contains implementations for functions defined in stream_writer.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "stream_writer.h"
#include "app_lib.h"
#include <stdio.h>
#include <stdarg.h>

StreamWriter createStreamWriter(FILE* stream) {
	StreamWriter this;

	app_assert(stream != NULL, ("'stream' is NULL"));

	this = (StreamWriter)malloc(sizeof(struct STREAM_WRITER));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->write = &write;
	this->writeFormat = &writeFormat;
	this->destroy = &destroyStreamWriter;

	this->stream = stream;

	return this;
}

void write(StreamWriter this, char* str) {
	fputs(str, this->stream);
}

void writeFormat(StreamWriter this, char* format, ...) {
	va_list args;
	va_start(args, format);
	vfprintf(this->stream, format, args);
	va_end(args);
}

void destroyStreamWriter(StreamWriter this) {
	if (this == NULL) return;

	free(this);
}