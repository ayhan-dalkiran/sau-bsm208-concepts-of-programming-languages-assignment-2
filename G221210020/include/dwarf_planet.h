/**
* @file dwarf_planet.h
* @description Contains DwarfPlanet struct definition.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef DWARF_PLANET_H
#define DWARF_PLANET_H
#include "planet.h"

struct DWARF_PLANET;
typedef struct DWARF_PLANET* DwarfPlanet;
struct DWARF_PLANET {
	Planet super;

	/* Frees allocated memory used by the object and it's parent object. */
	void (*destroy)(DwarfPlanet this);
};

DwarfPlanet createDwarfPlanet(char* name, TimeSystem timeSystem, DateTime dateTime);
void destroyDwarfPlanet(DwarfPlanet this);

#endif