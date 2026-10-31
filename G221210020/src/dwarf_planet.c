/**
* @file dwarf_planet.c
* @description Contains implementations for functions defined in dwarf_planet.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "dwarf_planet.h"

DwarfPlanet createDwarfPlanet(char* name, TimeSystem timeSystem, DateTime dateTime) {
	DwarfPlanet this = (DwarfPlanet)malloc(sizeof(struct DWARF_PLANET));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->super = createPlanet(name, 0.01, timeSystem, dateTime);
	this->destroy = &destroyDwarfPlanet;

	return this;
}

void destroyDwarfPlanet(DwarfPlanet this) {
	if (this == NULL) return;

	this->super->destroy(this->super);
	free(this);
}
