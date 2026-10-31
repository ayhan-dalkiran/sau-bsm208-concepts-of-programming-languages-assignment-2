/**
* @file spacecraft.h
* @description Contains Spacraft struct definition.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef SPACECRAFT_H
#define SPACECRAFT_H
#include "time_system.h"
#include "date_time.h"
#include "planet.h"

enum SPACECRAFT_STATUS {
	SPACECRAFT_STATUS_WAITING = 0,
	SPACECRAFT_STATUS_ENROUTE = 1,
	SPACECRAFT_STATUS_ARRIVED = 2,
	SPACECRAFT_STATUS_DESTROYED = 3
};
typedef enum SPACECRAFT_STATUS SpacecraftStatus;

struct SPACECRAFT;
typedef struct SPACECRAFT* Spacecraft;
struct SPACECRAFT {
	/* Spacecraft name. */
	char* name;
	/* Spacecraft's departure Planet. */
	Planet source;
	/* Spacecraft's destination Planet. */
	Planet destination;
	/* Spacecraft's departure DateTime. */
	DateTime departureDateTime;
	/* How many hours need to pass until Spacecraft arrived to destination. */
	int distanceInHours;
	/* Amount of people on the spacecraft. */
	int population;
	/* Status of the spacecraft. */
	SpacecraftStatus status;
	/* DateTime of when will spacecraft arrive to destination. */
	DateTime estimatedArrivalDateTime;

	/* Frees allocated memory used by the object, including the name string, departure DateTime and estimated arrival DateTime. */
	void (*destroy)(Spacecraft this);
};

Spacecraft createSpacecraft(char* name, Planet source, Planet destination, DateTime departureDateTime, int distanceInHours);
void destroySpacecraft(Spacecraft this);

#endif