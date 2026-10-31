/**
* @file planet.c
* @description Contains implementations for functions defined in planet.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "planet.h"

Planet createPlanet(char* name, double agingFactor, TimeSystem timeSystem, DateTime dateTime) {
	Planet this = (Planet)malloc(sizeof(struct PLANET));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->destroy = &destroyPlanet;

	this->name = name;
	this->agingFactor = agingFactor;
	this->timeSystem = timeSystem;
	this->dateTime = dateTime;
	this->population = 0;

	return this;
}

void destroyPlanet(Planet this) {
	if (this == NULL) return;

	free(this->name);
	this->timeSystem->destroy(this->timeSystem);
	this->dateTime->destroy(this->dateTime);
	free(this);
}