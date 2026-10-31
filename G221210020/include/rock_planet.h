/**
* @file rock_planet.h
* @description Contains RockPlanet struct definition.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef ROCK_PLANET_H
#define ROCK_PLANET_H
#include "planet.h"

struct ROCK_PLANET;
typedef struct ROCK_PLANET* RockPlanet;
struct ROCK_PLANET {
	Planet super;

	/* Frees allocated memory used by the object and it's parent object. */
	void (*destroy)(RockPlanet this);
};

RockPlanet createRockPlanet(char* name, TimeSystem timeSystem, DateTime dateTime);
void destroyRockPlanet(RockPlanet this);

#endif