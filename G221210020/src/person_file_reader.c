/**
* @file person_file_reader.c
* @description Contains implementations for functions defined in person_file_reader.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "person_file_reader.h"
#include <string.h>

PersonFileReader createPersonFileReader(char* path) {
	PersonFileReader this = (PersonFileReader)malloc(sizeof(struct PERSON_FILE_READER));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->readPerson = &readPerson;
	this->readPersonList = &readPersonList;
	this->destroy = &destroyPersonFileReader;

	this->super = createFileReader(path);

	return this;
}

void readPerson(PersonFileReader this, Person* person, Spacecraft* spacecraftList, size_t spacecraftListSize) {
	char* name;
	int age;
	double remainingLifeInHours;
	char* spacecraftName;

	Spacecraft spacecraft;
	size_t i;

	app_assert(this != NULL, ("'this' is NULL"));

	this->super->skipWhitespace(this->super);
	name = this->super->readStringUntil(this->super, "#");
	this->super->skipWhitespace(this->super);
	age = this->super->readInt(this->super);
	this->super->skipUntil(this->super, "#");
	this->super->skipWhitespace(this->super);
	remainingLifeInHours = (double)this->super->readInt(this->super);
	this->super->skipUntil(this->super, "#");
	this->super->skipWhitespace(this->super);
	spacecraftName = this->super->readStringUntil(this->super, "\n");
	this->super->skipWhitespace(this->super);

	spacecraft = NULL;
	for (i = 0; i < spacecraftListSize; i++) {
		Spacecraft s = spacecraftList[i];

		if (strcmp(s->name, spacecraftName) == 0) {
			spacecraft = s;
			break;
		}
	}
	app_assert(spacecraft != NULL, ("could not find spacecraft '%s'", spacecraftName));

	*person = createPerson(name, age, remainingLifeInHours, spacecraft);
}

void readPersonList(PersonFileReader this, Person** personList, size_t* personListSize, Spacecraft* spacecraftList, size_t spacecraftListSize) {
	app_assert(this != NULL, ("'this' is NULL"));

	while (!this->super->isEof(this->super)) {
		Person person;

		this->readPerson(this, &person, spacecraftList, spacecraftListSize);
		(*personList) = (Person*)realloc(*personList, (*personListSize + 1) * sizeof(Person));
		(*personList)[*personListSize] = person;
		(*personListSize) += 1;
	}
}

void destroyPersonFileReader(PersonFileReader this) {
	if (this == NULL) return;

	this->super->destroy(this->super);
	free(this);
}
