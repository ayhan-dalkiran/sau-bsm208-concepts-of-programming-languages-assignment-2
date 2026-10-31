/**
* @file gas_giant_planet.h
* @description Contains GasGiantPlanet struct definition.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef GAS_GIANT_PLANET_H
#define GAS_GIANT_PLANET_H
#include "planet.h"

struct GAS_GIANT_PLANET;
typedef struct GAS_GIANT_PLANET* GasGiantPlanet;
struct GAS_GIANT_PLANET {
	Planet super;

	/* Frees allocated memory used by the object and it's parent object. */
	void (*destroy)(GasGiantPlanet this);
};

GasGiantPlanet createGasGiantPlanet(char* name, TimeSystem timeSystem, DateTime dateTime);
void destroyGasGiantPlanet(GasGiantPlanet this);

#endif