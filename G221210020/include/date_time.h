/**
* @file date_time.h
* @description Contains DateTime struct definition for storing date
*              and time withing given timesystem.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef DATE_TIME_H
#define DATE_TIME_H

#include "app_lib.h"
#include "time_system.h"
#include <time.h>

/*
Buffer size calculation:
Printable fields: f
Other characters (not including null terminator): c
Buffer size: (f * ITOA_MAX_SIZE) + c = n
*/

/* Maximum number of characters date formated string can take. */
#define DATE_FORMAT_SIZE (size_t)((2 + 1 + 2 + 1) + ITOA_MAX_SIZE)
/* Maximum number of characters time formated string can take. */
#define TIME_FORMAT_SIZE (size_t)(ITOA_MAX_SIZE + (1 + 2 + 1 + 2))
/* Maximum number of characters date and time formated string can take. */
#define DATE_TIME_FORMAT_SIZE (size_t)(DATE_FORMAT_SIZE + 1 + TIME_FORMAT_SIZE)

struct DATE_TIME;
typedef struct DATE_TIME* DateTime;
struct DATE_TIME {
	/* TimeSystem used by DateTime for time and carry/borrow day calculations. */
	TimeSystem timeSystem;
	/* Current year in range [INT_MIN, INT_MAX] (after successful adjust() call) */
	int year;
	/* Current month in range [1, 12] (after successful adjust() call) */
	int month;
	/* Current day in range [1, 31] (after successful adjust() call) */
	int day;
	/* Current hour in range [0, timeSystem->hoursPerDay] (after successful adjust() call) */
	int hour;

	/*
	Moves DateTime by given time and adjusts to correct date and time.
	Accounts for negative values.
	*/
	void (*moveBy)(DateTime this, int years, int months, int days, int hours);

	/*
	Tries to adjust DateTime fields to valid values.
	Throws error if adjusted DateTime can't be represented as a real date.
	*/
	void (*adjust)(DateTime this);

	/*
	Returns how many hours need to pass to get to futureDateTime.
	Return values can be negative.
	*/
	time_t (*hoursUntil)(DateTime this, DateTime futureDateTime);

	/*
	Returns date represented as time_t.
	Returns -1 if date can't represented as time_t.
	*/
	time_t (*toTimeType)(DateTime this, struct tm* tm);

	/*
	Returns string representation of DateTime object.
	All possible boolean combinations and their behaviours are:
	(useTime true , useDate true): String representation in "hh:00:00 dd.mm.yyyy" format,
	(useTime true , useDate false): String representation in "hh:00:00" format,
	(useTime false, useDate true): String representation in "dd.mm.yyyy" format,
	(useTime false, useDate false): Program termination due to user error.
	*/
	size_t (*toString)(DateTime this, char* buffer, bool useDate, bool useTime);

	/*
	Frees allocated memory used by the object.
	Does not destroy the TimeSystem object.
	*/
	void (*destroy)(DateTime this);
};

DateTime createDateTime(TimeSystem timeSystem, int year, int month, int day, int hour);
void moveBy(DateTime this, int years, int months, int days, int hours);
void adjust(DateTime this);
time_t hoursUntil(DateTime this, DateTime futureDateTime);
time_t toTimeType(DateTime this, struct tm* tm);
size_t toString(DateTime this, char* buffer, bool useDate, bool useTime);
void destroyDateTime(DateTime this);

#endif