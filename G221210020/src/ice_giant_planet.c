/**
* @file ice_giant_planet.c
* @description Contains implementations for functions defined in ice_giant_planet.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "ice_giant_planet.h"

IceGiantPlanet createIceGiantPlanet(char* name, TimeSystem timeSystem, DateTime dateTime) {
	IceGiantPlanet this = (IceGiantPlanet)malloc(sizeof(struct ICE_GIANT_PLANET));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->super = createPlanet(name, 0.5, timeSystem, dateTime);
	this->destroy = &destroyIceGiantPlanet;

	return this;
}

void destroyIceGiantPlanet(IceGiantPlanet this) {
	if (this == NULL) return;

	this->super->destroy(this->super);
	free(this);
}
