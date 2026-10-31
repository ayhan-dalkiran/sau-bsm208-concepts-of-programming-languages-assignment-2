/**
* @file stream_writer.h
* @description Contains StreamWriter struct definition for writing to
*			   output streams with ease.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef STREAM_WRITER_H
#define STREAM_WRITER_H

#include "app_lib.h"
#include <stdio.h>

struct STREAM_WRITER;
typedef struct STREAM_WRITER* StreamWriter;
struct STREAM_WRITER {
	/* Stream object of the opened stream. */
	FILE* stream;

	/* Writes string to the stream. */
	void (*write)(StreamWriter this, char* str);
	/* Writes to the stream in given format. */
	void (*writeFormat)(StreamWriter this, char* format, ...);
	/* Frees allocated memory used by the object. Stream is not closed. */
	void (*destroy)(StreamWriter this);
};

StreamWriter createStreamWriter(FILE* stream);
void write(StreamWriter this, char* str);
void writeFormat(StreamWriter this, char* format, ...);
void destroyStreamWriter(StreamWriter this);

#endif