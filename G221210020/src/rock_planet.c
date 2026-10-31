/**
* @file rock_planet.c
* @description Contains implementations for functions defined in rock_planet.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "rock_planet.h"

RockPlanet createRockPlanet(char* name, TimeSystem timeSystem, DateTime dateTime) {
	RockPlanet this = (RockPlanet)malloc(sizeof(struct ROCK_PLANET));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->super = createPlanet(name, 1, timeSystem, dateTime);
	this->destroy = &destroyRockPlanet;

	return this;
}

void destroyRockPlanet(RockPlanet this) {
	if (this == NULL) return;

	this->super->destroy(this->super);
	free(this);
}
