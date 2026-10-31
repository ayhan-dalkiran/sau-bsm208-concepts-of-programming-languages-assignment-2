/**
* @file simulation.h
* @description Contains Simulation struct definition for modifiying
*			   planets, spacecrafts and people with respect to time.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef SIMULATION_H
#define SIMULATION_H

#include "planet.h"
#include "spacecraft.h"
#include "person.h"

struct SIMULATION;
typedef struct SIMULATION* Simulation;
struct SIMULATION {
	Planet* planetList;
	size_t planetListSize;

	Spacecraft* spacecraftList;
	size_t spacecraftListSize;

	Person* personList;
	size_t personListSize;

	/* Amount of hours simulation will move forward with each step. */
	int hoursPerStep;
	bool completed;

	void (*step)(Simulation this);

	/*
	Frees allocated memory used by the object and it's parent object.
	Planet, Spacecraft and Person lists won't be freed.
	*/
	void (*destroy)(Simulation this);
};

Simulation createSimulation(
	Planet* planetList, size_t planetListSize,
	Spacecraft* spacecraftList, size_t spacecraftListSize,
	Person* personList, size_t personListSize,
	int hoursPerStep);
void step(Simulation this);
void destroySimulation(Simulation this);

#endif