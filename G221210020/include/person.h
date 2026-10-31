/**
* @file person.h
* @description Contains Person struct definition.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef PERSON_H
#define PERSON_H
#include "spacecraft.h"

struct PERSON;
typedef struct PERSON* Person;
struct PERSON {
	/* Person's name. */
	char* name;
	/* Person's age (Unused in code). */
	int age;
	/* Person's remaining lifetime in terms of hours. */
	double remainingLifeInHours;
	/* Spacraft the Person is in. */
	Spacecraft spacecraft;
	/* Status of whether the person is dead or not. */
	bool dead;

	/* Frees allocated memory used by the object, including the name string. */
	void (*destroy)(Person this);
};

Person createPerson(char* name, int age, double remainingLifeInHours, Spacecraft spacecraft);
void destroyPerson(Person this);

#endif