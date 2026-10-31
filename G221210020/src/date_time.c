/**
* @file date_time.c
* @description Contains implementations for functions defined in date_time.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "date_time.h"
#include <math.h>
#include <stdio.h>
#include <string.h>

DateTime createDateTime(TimeSystem timeSystem, int year, int month, int day, int hour) {
	DateTime this = (DateTime)malloc(sizeof(struct DATE_TIME));
	app_assert(timeSystem != NULL, ("'timeSystem' is NULL"));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->moveBy = &moveBy;
	this->adjust = &adjust;
	this->hoursUntil = &hoursUntil;
	this->toTimeType = &toTimeType;
	this->toString = &toString;
	this->destroy = &destroyDateTime;

	this->timeSystem = timeSystem;
	this->year = 0;
	this->month = 0;
	this->day = 0;
	this->hour = 0;
	this->moveBy(this, year, month, day, hour);

	return this;
}

void moveBy(DateTime this, int years, int months, int days, int hours) {
	app_assert(this != NULL, ("'this' is NULL"));

	this->year += years;
	this->month += months;
	this->day += days;
	this->hour += hours;

	this->adjust(this);
}

void adjust(DateTime this) {
	struct tm tm;

	app_assert(this != NULL, ("'this' is NULL"));
	/* If newHour is positive, adds carry to day. */
	/* If newHour is negative, removes borrow from day. */
	this->day += (int)floor((double)this->hour / this->timeSystem->hoursPerDay);
	/* % operator rounds quotient towards zero and C standart does not guarantee that remainder will not be negative. */
	/* To make carry/borrow calculation simpler, we need to round quotient towards negative and ensure that remainder is never negative. */
	/* This is a custom modulo calculation with floor division to do exactly that. */
	this->hour -= this->timeSystem->hoursPerDay * (int)floor((double)this->hour / this->timeSystem->hoursPerDay);

	app_assert(this->toTimeType(this, &tm) != -1, ("can't adjust fields to valid date and time"));
	this->year = tm.tm_year + 1900;
	this->month = tm.tm_mon + 1;
	this->day = tm.tm_mday;
}

time_t hoursUntil(DateTime this, DateTime futureDateTime) {
	struct tm tm;
	time_t future;
	time_t now;
	double diff; /* In seconds. */

	app_assert(this != NULL, ("'this' is NULL"));

	future = futureDateTime->toTimeType(futureDateTime, &tm);
	now = this->toTimeType(this, &tm);

	diff = difftime(future, now); /* In seconds. */
	diff *= (double)this->timeSystem->hoursPerDay / 24;
	diff /= 60; /* In minutes. */
	diff /= 60; /* In hours. */
	diff += (futureDateTime->hour - this->hour); /* Adding in the hour difference. */

	return (time_t)diff;
}

time_t toTimeType(DateTime this, struct tm* tm) {
	app_assert(this != NULL, ("'this' is NULL"));
	app_assert(tm != NULL, ("'tm' is NULL"));

	tm->tm_year = this->year - 1900;
	tm->tm_mon = this->month - 1;
	tm->tm_mday = this->day;
	tm->tm_hour = 0;
	tm->tm_min = 0;
	tm->tm_sec = 0;
	tm->tm_isdst = 0;

	return mktime(tm);
}

size_t toString(DateTime this, char* buffer, bool useDate, bool useTime) {
	size_t size;

	app_assert(this != NULL, ("'this' is NULL"));
	app_assert(useDate || useTime, ("'useDate' and 'useTime' cannot be both false at the same time"));

	this->adjust(this);

	if (useDate && useTime) {
		size = sprintf(buffer, "%02d.%02d.%d %02d:00:00", this->day, this->month, this->year, this->hour);
	}
	else if (useDate) {
		size = sprintf(buffer, "%02d.%02d.%d", this->day, this->month, this->year);
	}
	else if (useTime) {
		size = sprintf(buffer, "%02d:00:00", this->hour);
	}
	else {
		/* Should never get here. */
		app_assert(false, ("invalid program state, 'useDate' and 'useTime' cannot be both false at the same time"));
	}

	buffer[size] = '\0';

	return size;
}

void destroyDateTime(DateTime this) {
	if (this == NULL) return;

	free(this);
}