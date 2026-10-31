/**
* @file spacecraft_file_reader.h
* @description Contains PlanetFileReader struct definition for reading
*			   Araclar.txt file with ease.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef SPACECRAFT_FILE_READER_H
#define SPACECRAFT_FILE_READER_H

#include "file_reader.h"
#include "spacecraft.h"

struct SPACECRAFT_FILE_READER;
typedef struct SPACECRAFT_FILE_READER* SpacecraftFileReader;
struct SPACECRAFT_FILE_READER {
	FileReader super;

	/* Reads next Spacecraft object in the file to 'spacecraft' using 'planetList'. */
	void (*readSpacecraft)(SpacecraftFileReader this, Spacecraft* spacecraft, Planet* planetList, size_t planetListSize);

	/* Reads all the Spacecraft objects in the file to 'spacecraftList' using 'planetList'. */
	void (*readSpacecraftList)(SpacecraftFileReader this, Spacecraft** spacecraftList, size_t* spacecraftListSize, Planet* planetList, size_t planetListSize);

	/* Frees allocated memory used by the object and it's parent object. */
	void (*destroy)(SpacecraftFileReader this);
};

SpacecraftFileReader createSpacecraftFileReader(char* path);
void readSpacecraft(SpacecraftFileReader this, Spacecraft* spacecraft, Planet* planetList, size_t planetListSize);
void readSpacecraftList(SpacecraftFileReader this, Spacecraft** spacecraftList, size_t* spacecraftListSize, Planet* planetList, size_t planetListSize);
void destroySpacecraftFileReader(SpacecraftFileReader this);

#endif