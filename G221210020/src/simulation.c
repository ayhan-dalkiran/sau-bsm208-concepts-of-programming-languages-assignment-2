/**
* @file simulation.c
* @description Contains implementations for functions defined in simulation.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "simulation.h"
#include "person.h"

Simulation createSimulation(
	Planet* planetList, size_t planetListSize,
	Spacecraft* spacecraftList, size_t spacecraftListSize,
	Person* personList, size_t personListSize,
	int hoursPerStep) {
	Simulation this = (Simulation)malloc(sizeof(struct SIMULATION));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->step = &step;
	this->destroy = &destroySimulation;

	this->planetList = planetList;
	this->planetListSize = planetListSize;
	this->spacecraftList = spacecraftList;
	this->spacecraftListSize = spacecraftListSize;
	this->personList = personList;
	this->personListSize = personListSize;
	this->hoursPerStep = hoursPerStep;
	this->completed = false;

	return this;
}

void step(Simulation this) {
	size_t i;
	bool completed = true;

	app_assert(this != NULL, ("'this' is NULL"));

	if (this->completed) return;

	for (i = 0; i < this->planetListSize; i++) {
		Planet planet = this->planetList[i];
		planet->dateTime->moveBy(planet->dateTime, 0, 0, 0, this->hoursPerStep);
	}

	for (i = 0; i < this->personListSize; i++) {
		Person person = this->personList[i];
		double agingFactor;

		if (person->dead) continue;

		agingFactor =
			person->spacecraft->status == SPACECRAFT_STATUS_WAITING ? person->spacecraft->source->agingFactor :
			person->spacecraft->status == SPACECRAFT_STATUS_ARRIVED	? person->spacecraft->destination->agingFactor : 1;
		person->remainingLifeInHours -= this->hoursPerStep * agingFactor;

		if (person->remainingLifeInHours <= 0) {
			person->dead = true;
			person->spacecraft->population--;

			if (person->spacecraft->status == SPACECRAFT_STATUS_WAITING) {
				person->spacecraft->source->population--;
			}
			else if (person->spacecraft->status == SPACECRAFT_STATUS_ARRIVED) {
				person->spacecraft->destination->population--;
			}
		}

	}

	for (i = 0; i < this->spacecraftListSize; i++) {
		Spacecraft spacecraft = this->spacecraftList[i];

		if (spacecraft->status == SPACECRAFT_STATUS_DESTROYED) continue;

		if (spacecraft->population <= 0) {
			spacecraft->status = SPACECRAFT_STATUS_DESTROYED;
			continue;
		}

		if (spacecraft->status == SPACECRAFT_STATUS_ARRIVED) continue;

		if (spacecraft->status == SPACECRAFT_STATUS_ENROUTE && spacecraft->distanceInHours <= 0) {
			spacecraft->status = SPACECRAFT_STATUS_ARRIVED;
			spacecraft->destination->population += spacecraft->population;
			continue;
		}
		completed = false;

		if (spacecraft->status == SPACECRAFT_STATUS_WAITING && spacecraft->source->dateTime->hoursUntil(spacecraft->source->dateTime, spacecraft->departureDateTime) <= 0) {
			spacecraft->status = SPACECRAFT_STATUS_ENROUTE;
			spacecraft->source->population -= spacecraft->population;
		}

		if (spacecraft->status == SPACECRAFT_STATUS_ENROUTE) {
			spacecraft->distanceInHours -= this->hoursPerStep;
		}
	}

	this->completed = completed;
}

void destroySimulation(Simulation this) {
	if (this == NULL) return;

	free(this);
}