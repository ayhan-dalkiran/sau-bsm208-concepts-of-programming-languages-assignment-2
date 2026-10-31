/**
* @file person_file_reader.h
* @description Contains PersonFileReader struct definition for reading
*			   Kisiler.txt file with ease.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef PERSON_FILE_READER_H
#define PERSON_FILE_READER_H

#include "file_reader.h"
#include "person.h"

struct PERSON_FILE_READER;
typedef struct PERSON_FILE_READER* PersonFileReader;
struct PERSON_FILE_READER {
	FileReader super;

	/* Reads next Person object in the file to 'person' using 'spacecraftList'. */
	void (*readPerson)(PersonFileReader this, Person* person, Spacecraft* spacecraftList, size_t spacecraftListSize);

	/* Reads all the Person objects in the file to 'personList' using 'spacecraftList'. */
	void (*readPersonList)(PersonFileReader this, Person** personList, size_t* personListSize, Spacecraft* spacecraftList, size_t spacecraftListSize);

	/* Frees allocated memory used by the object and it's parent object. */
	void (*destroy)(PersonFileReader this);
};

PersonFileReader createPersonFileReader(char* path);
void readPerson(PersonFileReader this, Person* person, Spacecraft* spacecraftList, size_t spacecraftListSize);
void readPersonList(PersonFileReader this, Person** personList, size_t* personListSize, Spacecraft* spacecraftList, size_t spacecraftListSize);
void destroyPersonFileReader(PersonFileReader this);

#endif