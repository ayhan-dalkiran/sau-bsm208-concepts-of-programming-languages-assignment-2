/**
* @file planet_file_reader.c
* @description Contains implementations for functions defined in planet_file_reader.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "planet_file_reader.h"
#include "rock_planet.h"
#include "gas_giant_planet.h"
#include "ice_giant_planet.h"
#include "dwarf_planet.h"

PlanetFileReader createPlanetFileReader(char* path) {
	PlanetFileReader this = (PlanetFileReader)malloc(sizeof(struct PLANET_FILE_READER));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->readPlanet = &readPlanet;
	this->readPlanetList = &readPlanetList;
	this->destroy = &destroyPlanetFileReader;

	this->super = createFileReader(path);

	return this;
}

void readPlanet(
	PlanetFileReader this,
	Planet* planet,
	RockPlanet* rockPlanet,
	GasGiantPlanet* gasGiantPlanet,
	IceGiantPlanet* iceGiantPlanet,
	DwarfPlanet* dwarfPlanet) {
	char* name;
	PlanetType type;
	int hoursPerDay;
	int day;
	int month;
	int year;

	TimeSystem timeSystem;
	DateTime dateTime;

	app_assert(this != NULL, ("'this' is NULL"));

	this->super->skipWhitespace(this->super);
	name = this->super->readStringUntil(this->super, "#");
	this->super->skipWhitespace(this->super);
	type = this->super->readInt(this->super);
	this->super->skipUntil(this->super, "#");
	this->super->skipWhitespace(this->super);
	hoursPerDay = this->super->readInt(this->super);
	this->super->skipUntil(this->super, "#");
	this->super->skipWhitespace(this->super);
	day = this->super->readInt(this->super);
	this->super->skipUntil(this->super, ".");
	this->super->skipWhitespace(this->super);
	month = this->super->readInt(this->super);
	this->super->skipUntil(this->super, ".");
	this->super->skipWhitespace(this->super);
	year = this->super->readInt(this->super);
	this->super->skipWhitespace(this->super);

	timeSystem = createTimeSystem(hoursPerDay);
	dateTime = createDateTime(timeSystem, year, month, day, 0);

	switch (type) {
		case PLANET_TYPE_ROCK:
			*rockPlanet = createRockPlanet(name, timeSystem, dateTime);
			*planet = (*rockPlanet)->super;
		break;
		case PLANET_TYPE_GAS_GIANT:
			*gasGiantPlanet = createGasGiantPlanet(name, timeSystem, dateTime);
			*planet = (*gasGiantPlanet)->super;
		break;
		case PLANET_TYPE_ICE_GIANT:
			*iceGiantPlanet = createIceGiantPlanet(name, timeSystem, dateTime);
			*planet = (*iceGiantPlanet)->super;
		break;
		case PLANET_TYPE_DWARF:
			*dwarfPlanet = createDwarfPlanet(name, timeSystem, dateTime);
			*planet = (*dwarfPlanet)->super;
		break;
		default:
			app_assert(false, ("invalid planet type '%d'", type));
		break;
	}
}

void readPlanetList(
	PlanetFileReader this,
	Planet** planetList, size_t* planetListSize,
	RockPlanet** rockPlanetList, size_t* rockPlanetListSize,
	GasGiantPlanet** gasGiantPlanetList, size_t* gasGiantPlanetListSize,
	IceGiantPlanet** iceGiantPlanetList, size_t* iceGiantPlanetListSize,
	DwarfPlanet** dwarfPlanetList, size_t* dwarfPlanetListSize) {
	app_assert(this != NULL, ("'this' is NULL"));

	while (!this->super->isEof(this->super)) {
		Planet planet = NULL;
		RockPlanet rockPlanet = NULL;
		GasGiantPlanet gasGiantPlanet = NULL;
		IceGiantPlanet iceGiantPlanet = NULL;
		DwarfPlanet dwarfPlanet = NULL;

		this->readPlanet(this, &planet, &rockPlanet, &gasGiantPlanet, &iceGiantPlanet, &dwarfPlanet);

		if (rockPlanet != NULL) {
			(*rockPlanetList) = (RockPlanet*)realloc(*rockPlanetList, (*rockPlanetListSize + 1) * sizeof(RockPlanet));
			(*rockPlanetList)[*rockPlanetListSize] = rockPlanet;
			(*rockPlanetListSize) += 1;
		}
		else if (gasGiantPlanet != NULL) {
			(*gasGiantPlanetList) = (GasGiantPlanet*)realloc(*gasGiantPlanetList, (*gasGiantPlanetListSize + 1) * sizeof(GasGiantPlanet));
			(*gasGiantPlanetList)[*gasGiantPlanetListSize] = gasGiantPlanet;
			(*gasGiantPlanetListSize) += 1;
		}
		else if (iceGiantPlanet != NULL) {
			(*iceGiantPlanetList) = (IceGiantPlanet*)realloc(*iceGiantPlanetList, (*iceGiantPlanetListSize + 1) * sizeof(IceGiantPlanet));
			(*iceGiantPlanetList)[*iceGiantPlanetListSize] = iceGiantPlanet;
			(*iceGiantPlanetListSize) += 1;
		}
		else if (dwarfPlanet != NULL) {
			(*dwarfPlanetList) = (DwarfPlanet*)realloc(*dwarfPlanetList, (*dwarfPlanetListSize + 1) * sizeof(DwarfPlanet));
			(*dwarfPlanetList)[*dwarfPlanetListSize] = dwarfPlanet;
			(*dwarfPlanetListSize) += 1;
		}
		else app_assert(false, ("failed to get valid planet subtype"));

		(*planetList) = (Planet*)realloc(*planetList, (*planetListSize + 1) * sizeof(Planet));
		(*planetList)[*planetListSize] = planet;
		(*planetListSize) += 1;
	}
}

void destroyPlanetFileReader(PlanetFileReader this) {
	if (this == NULL) return;

	this->super->destroy(this->super);
	free(this);
}
