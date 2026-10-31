/**
* @file ice_giant_planet.h
* @description Contains IceGiantPlanet struct definition.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef ICE_GIANT_PLANET_H
#define ICE_GIANT_PLANET_H
#include "planet.h"

struct ICE_GIANT_PLANET;
typedef struct ICE_GIANT_PLANET* IceGiantPlanet;
struct ICE_GIANT_PLANET {
	Planet super;

	/* Frees allocated memory used by the object and it's parent object. */
	void (*destroy)(IceGiantPlanet this);
};

IceGiantPlanet createIceGiantPlanet(char* name, TimeSystem timeSystem, DateTime dateTime);
void destroyIceGiantPlanet(IceGiantPlanet this);

#endif