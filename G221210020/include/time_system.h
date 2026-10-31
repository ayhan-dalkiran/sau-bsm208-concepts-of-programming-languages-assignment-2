/**
* @file time_system.h
* @description Contains TimeSystem struct definition for storing data about
*			   time behaves during a day.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef TIME_SYSTEM_H
#define TIME_SYSTEM_H

#include "app_lib.h"

struct TIME_SYSTEM;
typedef struct TIME_SYSTEM* TimeSystem;
struct TIME_SYSTEM {
	/* How many hours a day contains. */
	int hoursPerDay;

	/* Frees allocated memory used by the object. */
	void (*destroy)(TimeSystem this);
};

TimeSystem createTimeSystem(int hoursPerDay);
void destroyTimeSystem(TimeSystem this);

#endif