/**
* @file person.c
* @description Contains implementations for functions defined in person.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "person.h"

Person createPerson(char* name, int age, double remainingLifeInHours, Spacecraft spacecraft) {
	Person this = (Person)malloc(sizeof(struct PERSON));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->destroy = &destroyPerson;

	this->name = name;
	this->age = age;
	this->remainingLifeInHours = remainingLifeInHours;
	this->spacecraft = spacecraft;
	this->dead = false;

	this->spacecraft->population += 1;
	this->spacecraft->source->population += 1;

	return this;
}
void destroyPerson(Person this) {
	if (this == NULL) return;

	free(this->name);
	free(this);
}