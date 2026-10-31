/**
* @file spacecraft.c
* @description Contains implementations for functions defined in spacecraft.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "spacecraft.h"

Spacecraft createSpacecraft(char* name, Planet source, Planet destination, DateTime departureDateTime, int distanceInHours) {
	Spacecraft this = (Spacecraft)malloc(sizeof(struct SPACECRAFT));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->destroy = &destroySpacecraft;

	this->name = name;
	this->source = source;
	this->destination = destination;
	this->departureDateTime = departureDateTime;
	this->distanceInHours = distanceInHours;
	this->population = 0;
	this->status = SPACECRAFT_STATUS_WAITING;
	this->estimatedArrivalDateTime = createDateTime(
		destination->timeSystem,
		destination->dateTime->year, destination->dateTime->month, destination->dateTime->day,
		destination->dateTime->hour);
	this->estimatedArrivalDateTime->moveBy(this->estimatedArrivalDateTime, 0, 0, 0, source->dateTime->hoursUntil(source->dateTime, departureDateTime) + distanceInHours);

	return this;
}

void destroySpacecraft(Spacecraft this) {
	if (this == NULL) return;

	free(this->name);
	this->departureDateTime->destroy(this->departureDateTime);
	this->estimatedArrivalDateTime->destroy(this->estimatedArrivalDateTime);
	free(this);
}