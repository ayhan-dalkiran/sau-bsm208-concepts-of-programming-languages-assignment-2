/**
* @file planet_file_reader.h
* @description Contains PlanetFileReader struct definition for reading
*			   Gezegenler.txt file with ease.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef PLANET_FILE_READER_H
#define PLANET_FILE_READER_H

#include "file_reader.h"
#include "planet.h"
#include "rock_planet.h"
#include "gas_giant_planet.h"
#include "ice_giant_planet.h"
#include "dwarf_planet.h"

struct PLANET_FILE_READER;
typedef struct PLANET_FILE_READER* PlanetFileReader;
struct PLANET_FILE_READER {
	FileReader super;

	/*Reads next Planet object in the file to 'planet' and one of the other specific pointer types.*/
	void (*readPlanet)(
		PlanetFileReader this,
		Planet* planet,
		RockPlanet* rockPlanet,
		GasGiantPlanet* gasGiantPlanet,
		IceGiantPlanet* iceGiantPlanet,
		DwarfPlanet* dwarfPlanet);

	/* Reads all the Planet objects in the file to 'planetList' and one of the other lists. */
	void (*readPlanetList)(
		PlanetFileReader this,
		Planet** planetList, size_t* planetListSize,
		RockPlanet** rockPlanetList, size_t* rockPlanetListSize,
		GasGiantPlanet** gasGiantPlanetList, size_t* gasGiantPlanetListSize,
		IceGiantPlanet** iceGiantPlanetList, size_t* iceGiantPlanetListSize,
		DwarfPlanet** dwarfPlanetList, size_t* dwarfPlanetListSize);

	/* Frees allocated memory used by the object and it's parent object. */
	void (*destroy)(PlanetFileReader this);
};

enum PLANET_TYPE {
	PLANET_TYPE_ROCK = 0,
	PLANET_TYPE_GAS_GIANT = 1,
	PLANET_TYPE_ICE_GIANT = 2,
	PLANET_TYPE_DWARF = 3
};
typedef enum PLANET_TYPE PlanetType;

PlanetFileReader createPlanetFileReader(char* path);
void readPlanet(
	PlanetFileReader this,
	Planet* planet,
	RockPlanet* rockPlanet,
	GasGiantPlanet* gasGiantPlanet,
	IceGiantPlanet* iceGiantPlanet,
	DwarfPlanet* dwarfPlanet);
void readPlanetList(
	PlanetFileReader this,
	Planet** planetList, size_t* planetListSize,
	RockPlanet** rockPlanetList, size_t* rockPlanetListSize,
	GasGiantPlanet** gasGiantPlanetList, size_t* gasGiantPlanetListSize,
	IceGiantPlanet** iceGiantPlanetList, size_t* iceGiantPlanetListSize,
	DwarfPlanet** dwarfPlanetList, size_t* dwarfPlanetListSize);
void destroyPlanetFileReader(PlanetFileReader this);

#endif