/**
* @file file_reader.h
* @description Contains FileReader struct definition for reading from file with ease.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef FILE_READER_H
#define FILE_READER_H

#include "app_lib.h"
#include <stdio.h>

struct FILE_READER;
typedef struct FILE_READER* FileReader;
struct FILE_READER {
	/* File object of the opened file. */
	FILE* file;

	/* Returns true if next character is EOF, false otherwise. */
	bool (*isEof)(FileReader this);

	/* Returns next character without moving the file cursor. */
	int (*peek)(FileReader this);

	/* Returns next character and moves the file cursor forward. */
	int (*read)(FileReader this);

	/*
	Skips 'count' amount of characters or until EOF is reached.
	Returns amount of characters skipped.
	*/
	size_t (*skip)(FileReader this, size_t count);

	/*
	Skips until delimiter is found or EOF is reached.
	Returns amount of characters skipped.
	*/
	size_t (*skipUntil)(FileReader this, char* delimiter);

	/*
	Skips until non-whitespace character is found or EOF is reached.
	Returns amount of characters skipped.
	*/
	size_t (*skipWhitespace)(FileReader this);

	/* Reads integer from file. */
	int (*readInt)(FileReader this);

	/* Reads string from file until delimiter is found or EOF is reached. */
	char* (*readStringUntil)(FileReader this, char* delimiter);

	/* Frees allocated memory used by the object and closes file stream. */
	void (*destroy)(FileReader this);
};

FileReader createFileReader(char* path);
bool isEof(FileReader this);
int peek(FileReader this);
int read(FileReader this);
size_t skip(FileReader this, size_t count);
size_t skipUntil(FileReader this, char* delimiter);
size_t skipWhitespace(FileReader this);
int readInt(FileReader this);
char* readStringUntil(FileReader this, char* delimiter);
void destroyFileReader(FileReader this);

#endif