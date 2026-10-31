/**
* @file gas_giant_planet.c
* @description Contains implementations for functions defined in gas_giant_planet.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "gas_giant_planet.h"

GasGiantPlanet createGasGiantPlanet(char* name, TimeSystem timeSystem, DateTime dateTime) {
	GasGiantPlanet this = (GasGiantPlanet)malloc(sizeof(struct GAS_GIANT_PLANET));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->super = createPlanet(name, 0.1, timeSystem, dateTime);
	this->destroy = &destroyGasGiantPlanet;

	return this;
}

void destroyGasGiantPlanet(GasGiantPlanet this) {
	if (this == NULL) return;

	this->super->destroy(this->super);
	free(this);
}
