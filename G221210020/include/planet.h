/**
* @file planet.h
* @description Contains Planet struct definition.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef PLANET_H
#define PLANET_H
#include "time_system.h"
#include "date_time.h"

struct PLANET;
typedef struct PLANET* Planet;
struct PLANET {
	/* Planet's name. */
	char* name;
	/* How much a Person ages relative to normal rate. */
	double agingFactor;
	/* TimeSystem used by the Planet. */
	TimeSystem timeSystem;
	/* Planet's current DateTime. */
	DateTime dateTime;
	/* Planet's current population. */
	int population;

	/* Frees allocated memory used by the object, including the name string, DateTime and TimeSystem. */
	void (*destroy)(Planet this);
};

Planet createPlanet(char* name, double agingFactor, TimeSystem timeSystem, DateTime dateTime);
void destroyPlanet(Planet this);

#endif