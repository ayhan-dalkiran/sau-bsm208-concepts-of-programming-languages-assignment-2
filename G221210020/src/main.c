/**
* @file main.c
* @description Stores the main function where data is read from the files
*			   and loaded into the simulation and written to stdout.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "planet_file_reader.h"
#include "spacecraft_file_reader.h"
#include "person_file_reader.h"
#include "simulation.h"
#include "app_lib.h"
#include "simulation_stream_writer.h"
#include <locale.h>

int main() {
	PlanetFileReader planetFileReader;
	SpacecraftFileReader spacecraftFileReader;
	PersonFileReader personFileReader;

	Planet* planetList = NULL;
	size_t planetListSize = 0;
	RockPlanet* rockPlanetList = NULL;
	size_t rockPlanetListSize = 0;
	GasGiantPlanet* gasGiantPlanetList = NULL;
	size_t gasGiantPlanetListSize = 0;
	IceGiantPlanet* iceGiantPlanetList = NULL;
	size_t iceGiantPlanetListSize = 0;
	DwarfPlanet* dwarfPlanetList = NULL;
	size_t dwarfPlanetListSize = 0;
	Spacecraft* spacecraftList = NULL;
	size_t spacecraftListSize = 0;
	Person* personList = NULL;
	size_t personListSize = 0;

	Simulation simulation;
	SimulationStreamWriter writer;

	size_t i;
	size_t stdout_buffer_size = 16384; /* 16KiB */
	char* stdout_buffer = (char*)malloc(stdout_buffer_size);
	/* Sets stdout buffer to 16 KiB and only prints when the buffer is full */
	setvbuf(stdout, stdout_buffer, _IOFBF, stdout_buffer_size);

	planetFileReader = createPlanetFileReader("Gezegenler.txt");
	spacecraftFileReader = createSpacecraftFileReader("Araclar.txt");
	personFileReader = createPersonFileReader("Kisiler.txt");

	planetFileReader->readPlanetList(
		planetFileReader,
		&planetList, &planetListSize,
		&rockPlanetList, &rockPlanetListSize,
		&gasGiantPlanetList, &gasGiantPlanetListSize,
		&iceGiantPlanetList, &iceGiantPlanetListSize,
		&dwarfPlanetList, &dwarfPlanetListSize);

	spacecraftFileReader->readSpacecraftList(
		spacecraftFileReader,
		&spacecraftList, &spacecraftListSize,
		planetList, planetListSize);

	personFileReader->readPersonList(
		personFileReader,
		&personList, &personListSize,
		spacecraftList, spacecraftListSize);

	planetFileReader->destroy(planetFileReader);
	spacecraftFileReader->destroy(spacecraftFileReader);
	personFileReader->destroy(personFileReader);

	simulation = createSimulation(
		planetList, planetListSize,
		spacecraftList, spacecraftListSize,
		personList, personListSize,
		1);

	writer = createSimulationStreamWriter(stdout, simulation);

	setlocale(LC_ALL, "C");
	system("chcp 65001");
	system("cls");

	while (!simulation->completed) {
		writer->writePlanetList(writer);
		writer->super->write(writer->super, "\n\n");
		writer->writeSpacecraftList(writer);
		simulation->step(simulation);
		fflush(stdout); /* Required since we want to print results before the buffer is filled */
		/* writer->super->write(writer->super, "\x1b[1;1H"); */ /*Moves cursor to top left of the screen */
		system("cls");
	}
	writer->writePlanetList(writer);
	writer->super->write(writer->super, "\n\n");
	writer->writeSpacecraftList(writer);
	fflush(stdout);

	writer->destroy(writer);
	simulation->destroy(simulation);

	for (i = 0; i < personListSize; i++) {
		Person person = personList[i];
		person->destroy(person);
	}

	for (i = 0; i < spacecraftListSize; i++) {
		Spacecraft spacecraft = spacecraftList[i];
		spacecraft->destroy(spacecraft);
	}

	for (i = 0; i < dwarfPlanetListSize; i++) {
		DwarfPlanet planet = dwarfPlanetList[i];
		planet->destroy(planet);
	}

	for (i = 0; i < iceGiantPlanetListSize; i++) {
		IceGiantPlanet planet = iceGiantPlanetList[i];
		planet->destroy(planet);
	}

	for (i = 0; i < gasGiantPlanetListSize; i++) {
		GasGiantPlanet planet = gasGiantPlanetList[i];
		planet->destroy(planet);
	}

	for (i = 0; i < rockPlanetListSize; i++) {
		RockPlanet planet = rockPlanetList[i];
		planet->destroy(planet);
	}

	free(planetList);
	free(rockPlanetList);
	free(gasGiantPlanetList);
	free(iceGiantPlanetList);
	free(dwarfPlanetList);
	free(spacecraftList);
	free(personList);

	return 0;
}