/**
* @file spacecraft_file_reader.c
* @description Contains implementations for functions defined in spacecraft_file_reader.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "spacecraft_file_reader.h"
#include <string.h>

SpacecraftFileReader createSpacecraftFileReader(char* path) {
	SpacecraftFileReader this = (SpacecraftFileReader)malloc(sizeof(struct SPACECRAFT_FILE_READER));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->readSpacecraft = &readSpacecraft;
	this->readSpacecraftList = &readSpacecraftList;
	this->destroy = &destroySpacecraftFileReader;

	this->super = createFileReader(path);

	return this;
}

void readSpacecraft(SpacecraftFileReader this, Spacecraft* spacecraft, Planet* planetList, size_t planetListSize) {
	char* name;
	char* source;
	char* destination;
	int day;
	int month;
	int year;
	int distanceInHours;

	Planet sourcePlanet;
	Planet destinationPlanet;
	size_t i;
	DateTime departureDateTime;

	app_assert(this != NULL, ("'this' is NULL"));

	this->super->skipWhitespace(this->super);
	name = this->super->readStringUntil(this->super, "#");
	this->super->skipWhitespace(this->super);
	source = this->super->readStringUntil(this->super, "#");
	this->super->skipWhitespace(this->super);
	destination = this->super->readStringUntil(this->super, "#");
	this->super->skipWhitespace(this->super);
	day = this->super->readInt(this->super);
	this->super->skipUntil(this->super, ".");
	this->super->skipWhitespace(this->super);
	month = this->super->readInt(this->super);
	this->super->skipUntil(this->super, ".");
	this->super->skipWhitespace(this->super);
	year = this->super->readInt(this->super);
	this->super->skipUntil(this->super, "#");
	this->super->skipWhitespace(this->super);
	distanceInHours = this->super->readInt(this->super);
	this->super->skipWhitespace(this->super);

	sourcePlanet = NULL;
	destinationPlanet = NULL;
	for (i = 0; i < planetListSize; i++) {
		Planet p = planetList[i];

		if (strcmp(p->name, source) == 0) {
			sourcePlanet = p;
			break;
		}
	}
	app_assert(sourcePlanet != NULL, ("could not find source planet '%s'", source));

	for (i = 0; i < planetListSize; i++) {
		Planet p = planetList[i];

		if (strcmp(p->name, destination) == 0) {
			destinationPlanet = p;
			break;
		}
	}
	app_assert(destinationPlanet != NULL, ("could not find destination planet '%s'", destination));

	departureDateTime = createDateTime(sourcePlanet->timeSystem, year, month, day, 0);
	*spacecraft = createSpacecraft(name, sourcePlanet, destinationPlanet, departureDateTime, distanceInHours);
}

void readSpacecraftList(SpacecraftFileReader this, Spacecraft** spacecraftList, size_t* spacecraftListSize, Planet* planetList, size_t planetListSize) {
	app_assert(this != NULL, ("'this' is NULL"));

	while (!this->super->isEof(this->super)) {
		Spacecraft spacecraft;

		this->readSpacecraft(this, &spacecraft, planetList, planetListSize);
		(*spacecraftList) = (Spacecraft*)realloc(*spacecraftList, (*spacecraftListSize + 1) * sizeof(Spacecraft));
		(*spacecraftList)[*spacecraftListSize] = spacecraft;
		(*spacecraftListSize) += 1;
	}
}

void destroySpacecraftFileReader(SpacecraftFileReader this) {
	if (this == NULL) return;

	this->super->destroy(this->super);
	free(this);
}
