/**
* @file file_reader.c
* @description Contains implementations for functions defined in file_reader.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "file_reader.h"
#include <string.h>
#include <ctype.h>

FileReader createFileReader(char* path) {
	FileReader this = (FileReader)malloc(sizeof(struct FILE_READER));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->isEof = &isEof;
	this->peek = &peek;
	this->read = &read;
	this->skip = &skip;
	this->skipUntil = &skipUntil;
	this->skipWhitespace = &skipWhitespace;
	this->readInt = &readInt;
	this->readStringUntil = &readStringUntil;
	this->destroy = &destroyFileReader;

	this->file = fopen(path, "r");
	app_assert(this->file != NULL, ("could not open file '%s'", path));

	return this;
}

bool isEof(FileReader this) {
	int c;
	fpos_t pos;
	app_assert(this != NULL, ("'this' is NULL"));

	fgetpos(this->file, &pos);
	c = fgetc(this->file);
	fsetpos(this->file, &pos);

	return c == EOF;
}

int peek(FileReader this) {
	app_assert(this != NULL, ("'this' is NULL"));
	if (this->isEof(this)) return EOF;

	return ungetc(fgetc(this->file), this->file);
}

int read(FileReader this) {
	app_assert(this != NULL, ("'this' is NULL"));

	if (this->isEof(this)) return EOF;

	return fgetc(this->file);
}

size_t skip(FileReader this, size_t count) {
	size_t charactersRead;
	size_t i;

	app_assert(this != NULL, ("'this' is NULL"));

	charactersRead = 0;
	for (i = 0; i < count && !this->isEof(this); i++) {
		this->read(this);
		charactersRead += 1;
	}

	return charactersRead;
}

size_t skipUntil(FileReader this, char* delimiter) {
	size_t delimiterSize = strlen(delimiter);
	size_t charactersRead = 0;
	size_t matches = 0;

	app_assert(this != NULL, ("'this' is NULL"));

	while(!this->isEof(this) && matches < delimiterSize) {
		int c = this->read(this);
		charactersRead += 1;

		if (c == delimiter[matches]) {
			matches += 1;
		}
	}

	return charactersRead;
}

size_t skipWhitespace(FileReader this) {
	size_t charactersRead;

	app_assert(this != NULL, ("'this' is NULL"));

	charactersRead = 0;
	while(!this->isEof(this)) {
		int c = this->peek(this);
		if (!isspace(c)) break;

		charactersRead += 1;
		this->read(this);
	}

	return charactersRead;
}

int readInt(FileReader this) {
	int num;

	app_assert(this != NULL, ("'this' is NULL"));

	fscanf(this->file, "%d", &num);
	return num;

}

char* readStringUntil(FileReader this, char* delimiter) {
	fpos_t initPos;

	size_t delimiterSize;
	size_t charactersRead;
	size_t matches;

	char* string;
	size_t i;

	app_assert(this != NULL, ("'this' is NULL"));

	fgetpos(this->file, &initPos);

	delimiterSize = strlen(delimiter);
	charactersRead = 0;
	matches = 0;

	/* Finding string size */
	while(!this->isEof(this) && matches < delimiterSize) {
		int c = this->read(this);
		charactersRead += 1;

		if (c == delimiter[matches]) {
			matches += 1;
		}
		else {
			matches = 0;
		}
	}

	fsetpos(this->file, &initPos);
	string = (char*)malloc(charactersRead + 1);
	for (i = 0; i < (charactersRead - matches); i++) {
		int c = this->read(this);
		string[i] = c;
	}
	string[charactersRead - matches] = '\0';
	this->skip(this, matches);

	return string;
}

void destroyFileReader(FileReader this) {
	if (this == NULL) return;

	fclose(this->file);
	free(this);
}