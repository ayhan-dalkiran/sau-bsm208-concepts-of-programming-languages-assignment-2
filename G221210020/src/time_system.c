/**
* @file time_system.c
* @description Contains implementations for functions defined in time_system.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "time_system.h"

TimeSystem createTimeSystem(int hoursPerDay) {
	TimeSystem this;
	app_assert(hoursPerDay > 0, ("'hoursPerDay' has to be larger than 0, got '%d'", hoursPerDay));

	this = (TimeSystem)malloc(sizeof(struct TIME_SYSTEM));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->destroy = &destroyTimeSystem;

	this->hoursPerDay = hoursPerDay;

	return this;
}

void destroyTimeSystem(TimeSystem this) {
	if (this == NULL) return;

	free(this);
}
