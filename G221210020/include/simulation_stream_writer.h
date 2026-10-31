/**
* @file simulation_stream_writer.h
* @description Contains SimulationStreamWriter struct definition for writing
*			   state of the Simulation to the output stream as performantly
*			   as possible.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#ifndef SIMULATION_STREAM_WRITER_H
#define SIMULATION_STREAM_WRITER_H

#include "app_lib.h"
#include "stream_writer.h"
#include "simulation.h"
#include <stdio.h>

struct SIMULATION_STREAM_WRITER;
typedef struct SIMULATION_STREAM_WRITER* SimulationStreamWriter;
struct SIMULATION_STREAM_WRITER {
	StreamWriter super;
	/* Simulation that will be written to the stream. */
	Simulation simulation;

	/* List of planet column widths that each cell can theoretically occupy. */
	size_t* planetColumnsWidthCache;
	/* Text that will be written to planet name row header. */
	char* planetNameRowHeader;
	/* Text that will be written to planet DateTime row header. */
	char* planetDateTimeRowHeader;
	/* Text that will be written to planet population row header. */
	char* planetPopulationRowHeader;

	/* Cached planet headers that will be directly written to stream. */
	char** planetRowHeaderCache;
	/* Cached planet names that will be directly written to stream. */
	char** planetNameCache;

	/* List of spacecraft column widths that each cell can theoretically occupy. */
	size_t* spacecraftColumnsWidthCache;
	/* Text that will be written to spacecraft name column header. */
	char* spacecraftNameColumnHeader;
	/* Text that will be written to spacecraft status column header. */
	char* spacecraftStatusColumnHeader;
	/* Text that will be written to spacecraft source column header. */
	char* spacecraftSourceColumnHeader;
	/* Text that will be written to spacecraft destination column header. */
	char* spacecraftDestinationColumnHeader;
	/* Text that will be written to spacecraft distance in hours column header. */
	char* spacecraftDistanceInHoursColumnHeader;
	/* Text that will be written to spacecraft arrival time column header. */
	char* spacecraftEstimatedArrivalTimeColumnHeader;

	/* Cached spacecraft headers that will be directly written to stream. */
	char** spacecraftColumnHeaderCache;
	/* Cached spacecraft names that will be directly written to stream. */
	char** spacecraftNameCache;
	/* Cached spacecraft sources that will be directly written to stream. */
	char** spacecraftSourceCache;
	/* Cached spacecraft destinations that will be directly written to stream. */
	char** spacecraftDestinationCache;
	/* Cached spacecraft arrival times that will be directly written to stream. */
	char** spacecraftEstimatedArrivalTimeCache;

	/* Text that will be written for SPACECRAFT_STATUS_WAITING. */
	char* spacecraftStatusWaiting;
	/* Text that will be written for SPACECRAFT_STATUS_ENROUTE. */
	char* spacecraftStatusEnroute;
	/* Text that will be written for SPACECRAFT_STATUS_ARRIVED. */
	char* spacecraftStatusArrived;
	/* Text that will be written for SPACECRAFT_STATUS_DESTROYED. */
	char* spacecraftStatusDestroyed;
	/* Caches spacecraft status values that is mapped to SPACECRAFT_STATUS values. */
	char** spacecraftStatusCache;

	/* Cached empty spacecraft distance in hours value that will be directly written to stream. */
	char* spacecraftDistanceInHoursEmptyValueCache;
	/* Cached empty spacecraft arriva time value that will be directly written to stream. */
	char* spacecraftEstimatedArrivalTimeEmptyValueCache;

	/* Text that will be written for empty cells. */
	char* emptyValue;
	/* Text that will be written to split columns. */
	char* columnSpliter;

	/* Returns a malloc'ed cache string that has the input padded to the left.*/
	char* (*createStringCacheFormatLeft)(SimulationStreamWriter this, size_t width, char* string);

	/* Calculates and caches maximum column widths. */
	void (*buildWidthCache)(SimulationStreamWriter this);

	/* Builds and caches static string values. */
	void (*buildStringCache)(SimulationStreamWriter this);

	/* Writes planet data to stream. */
	void (*writePlanetList)(SimulationStreamWriter this);

	/* Writes spacecraft data to stream. */
	void (*writeSpacecraftList)(SimulationStreamWriter this);

	/*
	Frees allocated memory used by the object and all the cached data.
	Simulation object is not freed.
	*/
	void (*destroy)(SimulationStreamWriter this);
};

SimulationStreamWriter createSimulationStreamWriter(FILE* stream, Simulation simulation);
char* createStringCacheFormatLeft(SimulationStreamWriter this, size_t width, char* string);
void buildWidthCache(SimulationStreamWriter this);
void buildStringCache(SimulationStreamWriter this);
void writePlanetList(SimulationStreamWriter this);
void writeSpacecraftList(SimulationStreamWriter this);
void destroySimulationStreamWriter(SimulationStreamWriter this);

#endif