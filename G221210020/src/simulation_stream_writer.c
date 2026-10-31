/**
* @file simulation_stream_writer.c
* @description Contains implementations for functions defined in simulation_stream_writer.h.
* @course Programlama Dillerinin Presipleri 2. Öğretim C Grubu
* @assignment 2. Ödev
* @date 18/05/2025
* @author G221210020 - Ayhan Dalkıran - g221210020@sakarya.edu.tr
*/
#include "simulation_stream_writer.h"
#include <string.h>
#include "planet.h"
#include "spacecraft.h"

SimulationStreamWriter createSimulationStreamWriter(FILE* stream, Simulation simulation) {
	SimulationStreamWriter this;

	app_assert(stream != NULL, ("'stream' is NULL"));
	app_assert(simulation != NULL, ("'simulation' is NULL"));

	this = (SimulationStreamWriter)malloc(sizeof(struct SIMULATION_STREAM_WRITER));
	app_assert(this != NULL, ("could not create object: alloc error"));

	this->super = createStreamWriter(stream);
	this->buildWidthCache = &buildWidthCache;
	this->buildStringCache = &buildStringCache;
	this->writePlanetList = &writePlanetList;
	this->writeSpacecraftList = &writeSpacecraftList;
	this->destroy = &destroySimulationStreamWriter;

	this->simulation = simulation;

	this->planetColumnsWidthCache = (size_t*)calloc(simulation->planetListSize + 1, sizeof(size_t));
	this->planetNameRowHeader = duplicateString("");
	this->planetDateTimeRowHeader = duplicateString("Tarih");
	this->planetPopulationRowHeader = duplicateString("Nüfus");

	this->planetRowHeaderCache = (char**)calloc(3, sizeof(char*));
	this->planetNameCache = (char**)calloc(simulation->planetListSize, sizeof(char*));

	this->spacecraftColumnsWidthCache = (size_t*)calloc(6, sizeof(size_t));
	this->spacecraftNameColumnHeader = duplicateString("Araç Adı");
	this->spacecraftStatusColumnHeader = duplicateString("Durum");
	this->spacecraftSourceColumnHeader = duplicateString("Çıkış");
	this->spacecraftDestinationColumnHeader = duplicateString("Varış");
	this->spacecraftDistanceInHoursColumnHeader = duplicateString("Hedefe Kalan Saat");
	this->spacecraftEstimatedArrivalTimeColumnHeader = duplicateString("Hedefe Varacağı Tarih");

	this->spacecraftColumnHeaderCache = (char**)calloc(6, sizeof(char*));
	this->spacecraftNameCache = (char**)calloc(simulation->spacecraftListSize, sizeof(char*));
	this->spacecraftStatusCache = (char**)calloc(4, sizeof(char*));
	this->spacecraftSourceCache = (char**)calloc(simulation->spacecraftListSize, sizeof(char*));
	this->spacecraftDestinationCache = (char**)calloc(simulation->spacecraftListSize, sizeof(char*));
	this->spacecraftEstimatedArrivalTimeCache = (char**)calloc(simulation->spacecraftListSize, sizeof(char*));

	this->columnSpliter = duplicateString("   ");
	this->emptyValue = duplicateString("--");
	this->spacecraftStatusWaiting = duplicateString("Bekliyor");
	this->spacecraftStatusEnroute = duplicateString("Yolda");
	this->spacecraftStatusArrived = duplicateString("Vardı");
	this->spacecraftStatusDestroyed = duplicateString("İMHA");

	this->buildWidthCache(this);
	this->buildStringCache(this);

	return this;
}

void formatLeft(SimulationStreamWriter this, char* buffer, size_t width, char* string) {
	char* formattedString = (char*)malloc(width + 1);
	size_t size = width + getUtf8ContinuationByteCount(string);
	sprintf(formattedString, "%-*s", size, string);
	return formattedString;
}

char* createStringCacheFormatLeft(SimulationStreamWriter this, size_t width, char* string) {
	size_t size = width + getUtf8ContinuationByteCount(string);
	char* formattedString = (char*)malloc(size + 1);
	sprintf(formattedString, "%-*s", size, string);
	return formattedString;
}

char* createStringCacheFormatCenter(SimulationStreamWriter this, size_t width, char* string, char padding, char*) {
	size_t size = width + getUtf8ContinuationByteCount(string);
	char* formattedString = (char*)malloc(size + 1);
	sprintf(formattedString, "%-*s", size, string);
	return formattedString;
}

void buildWidthCache(SimulationStreamWriter this) {
	size_t i;

	app_assert(this != NULL, ("'this' is NULL"));

	/* Planet Cache */
	this->planetColumnsWidthCache[0] = strlen(this->planetNameRowHeader);
	this->planetColumnsWidthCache[0] = max(this->planetColumnsWidthCache[0], strlen(this->planetDateTimeRowHeader));
	this->planetColumnsWidthCache[0] = max(this->planetColumnsWidthCache[0], strlen(this->planetPopulationRowHeader));

	for (i = 0; i < this->simulation->planetListSize; i++) {
		Planet planet = this->simulation->planetList[i];
		this->planetColumnsWidthCache[i + 1] = max(strlen(planet->name) + 2, max(DATE_FORMAT_SIZE, ITOA_MAX_SIZE));
	}

	/* Spacecraft Cache */
	this->spacecraftColumnsWidthCache[0] = strlen(this->spacecraftNameColumnHeader);

	this->spacecraftColumnsWidthCache[1] = strlen(this->spacecraftStatusColumnHeader);
	this->spacecraftColumnsWidthCache[1] = max(this->spacecraftColumnsWidthCache[1], strlen(this->spacecraftStatusWaiting));
	this->spacecraftColumnsWidthCache[1] = max(this->spacecraftColumnsWidthCache[1], strlen(this->spacecraftStatusEnroute));
	this->spacecraftColumnsWidthCache[1] = max(this->spacecraftColumnsWidthCache[1], strlen(this->spacecraftStatusArrived));
	this->spacecraftColumnsWidthCache[1] = max(this->spacecraftColumnsWidthCache[1], strlen(this->spacecraftStatusDestroyed));

	this->spacecraftColumnsWidthCache[2] = strlen(this->spacecraftSourceColumnHeader);
	this->spacecraftColumnsWidthCache[3] = strlen(this->spacecraftDestinationColumnHeader);
	this->spacecraftColumnsWidthCache[4] = max(strlen(this->spacecraftDistanceInHoursColumnHeader), ITOA_MAX_SIZE);
	this->spacecraftColumnsWidthCache[5] = max(strlen(this->spacecraftEstimatedArrivalTimeColumnHeader), DATE_FORMAT_SIZE);

	for (i = 0; i < this->simulation->spacecraftListSize; i++) {
		Spacecraft spacecraft = this->simulation->spacecraftList[i];

		this->spacecraftColumnsWidthCache[0] = max(this->spacecraftColumnsWidthCache[0], strlen(spacecraft->name));
		this->spacecraftColumnsWidthCache[2] = max(this->spacecraftColumnsWidthCache[2], strlen(spacecraft->source->name));
		this->spacecraftColumnsWidthCache[3] = max(this->spacecraftColumnsWidthCache[3], strlen(spacecraft->destination->name));
	}
}

void buildStringCache(SimulationStreamWriter this) {
	size_t i;
	char* stringBuffer;
	size_t width;

	app_assert(this != NULL, ("'this' is NULL"));

	/* Planet Cache */
	this->planetRowHeaderCache[0] = this->createStringCacheFormatLeft(this, this->planetColumnsWidthCache[0], this->planetNameRowHeader);
	this->planetRowHeaderCache[1] = this->createStringCacheFormatLeft(this, this->planetColumnsWidthCache[0], this->planetDateTimeRowHeader);
	this->planetRowHeaderCache[2] = this->createStringCacheFormatLeft(this, this->planetColumnsWidthCache[0], this->planetPopulationRowHeader);

	for (i = 0; i < this->simulation->planetListSize; i++) {
		Planet planet = this->simulation->planetList[i];
		size_t paddingWidth;
		size_t offset;

		width = this->planetColumnsWidthCache[i + 1] + getUtf8ContinuationByteCount(planet->name);
		paddingWidth = (width - strlen(planet->name) - 2) / 2;
		stringBuffer = (char*)malloc(width + 1);
		memset(stringBuffer, '-', width);

		offset = sprintf(stringBuffer + paddingWidth, "%c%s%c", ' ', planet->name, ' ');
		stringBuffer[paddingWidth + offset] = '-';
		stringBuffer[width] = '\0';

		this->planetNameCache[i] = stringBuffer;
	}

	/* Spacecraft Cache */
	this->spacecraftColumnHeaderCache[0] = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[0], this->spacecraftNameColumnHeader);
	this->spacecraftColumnHeaderCache[1] = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[1], this->spacecraftStatusColumnHeader);
	this->spacecraftColumnHeaderCache[2] = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[2], this->spacecraftSourceColumnHeader);
	this->spacecraftColumnHeaderCache[3] = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[3], this->spacecraftDestinationColumnHeader);
	this->spacecraftColumnHeaderCache[4] = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[4], this->spacecraftDistanceInHoursColumnHeader);
	this->spacecraftColumnHeaderCache[5] = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[5], this->spacecraftEstimatedArrivalTimeColumnHeader);

	for (i = 0; i < this->simulation->spacecraftListSize; i++) {
		Spacecraft spacecraft = this->simulation->spacecraftList[i];
		size_t offset;

		this->spacecraftNameCache[i] = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[0], spacecraft->name);
		this->spacecraftSourceCache[i] = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[2], spacecraft->source->name);
		this->spacecraftDestinationCache[i] = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[3], spacecraft->destination->name);
		this->spacecraftEstimatedArrivalTimeCache[i] = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[5], spacecraft->name);

		width = this->spacecraftColumnsWidthCache[5];
		stringBuffer = (char*)malloc(width + 1);
		offset = spacecraft->estimatedArrivalDateTime->toString(spacecraft->estimatedArrivalDateTime, stringBuffer, true, false);
		sprintf(stringBuffer + offset, "%-*s", (int)(width - offset), "");
		this->spacecraftEstimatedArrivalTimeCache[i] = stringBuffer;
	}

	this->spacecraftStatusCache[0] = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[1], this->spacecraftStatusWaiting);
	this->spacecraftStatusCache[1] = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[1], this->spacecraftStatusEnroute);
	this->spacecraftStatusCache[2] = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[1], this->spacecraftStatusArrived);
	this->spacecraftStatusCache[3] = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[1], this->spacecraftStatusDestroyed);

	this->spacecraftDistanceInHoursEmptyValueCache = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[4], this->emptyValue);
	this->spacecraftEstimatedArrivalTimeEmptyValueCache = this->createStringCacheFormatLeft(this, this->spacecraftColumnsWidthCache[5], this->emptyValue);
}

void writePlanetList(SimulationStreamWriter this) {
	size_t i;
	char buffer[max(DATE_FORMAT_SIZE, ITOA_MAX_SIZE) + 1];

	this->super->write(this->super, "Gezegenler:\n");

	this->super->write(this->super, this->planetRowHeaderCache[0]);
	for (i = 0; i < this->simulation->planetListSize; i++) {
		this->super->write(this->super, this->columnSpliter);
		this->super->write(this->super, this->planetNameCache[i]);
	}
	this->super->write(this->super, "\n");

	this->super->write(this->super, this->planetRowHeaderCache[1]);
	for (i = 0; i < this->simulation->planetListSize; i++) {
		Planet planet = this->simulation->planetList[i];
		size_t columnWidth = this->planetColumnsWidthCache[i + 1];
		size_t dateWidth = planet->dateTime->toString(planet->dateTime, buffer, true, false);
		size_t paddingWidth = (columnWidth - dateWidth) / 2;

		this->super->write(this->super, this->columnSpliter);
		this->super->writeFormat(this->super, "%*s%s%*s", (int)paddingWidth, "", buffer, (int)(columnWidth - paddingWidth - dateWidth), "");
	}
	this->super->write(this->super, "\n");

	this->super->write(this->super, this->planetRowHeaderCache[2]);
	for (i = 0; i < this->simulation->planetListSize; i++) {
		Planet planet = this->simulation->planetList[i];
		size_t columnWidth = this->planetColumnsWidthCache[i + 1];
		size_t populationWidth = sprintf(buffer, "%d", planet->population);
		size_t paddingWidth = (columnWidth - populationWidth) / 2;

		this->super->write(this->super, this->columnSpliter);
		this->super->writeFormat(this->super, "%*s%s%*s", (int)paddingWidth, "", buffer, (int)(columnWidth - paddingWidth - populationWidth), "");
	}
	this->super->write(this->super, "\n");
}

void writeSpacecraftList(SimulationStreamWriter this) {
	size_t i;
	char buffer[DATE_FORMAT_SIZE + 1];

	this->super->write(this->super, "Uzay Araçları:\n");

	for (i = 0; i < 6; i++) {
		this->super->write(this->super, this->spacecraftColumnHeaderCache[i]);
		this->super->write(this->super, this->columnSpliter);
	}
	this->super->write(this->super, "\n");

	for (i = 0; i < this->simulation->spacecraftListSize; i++) {
		Spacecraft spacecraft = this->simulation->spacecraftList[i];

		this->super->write(this->super, this->spacecraftNameCache[i]);
		this->super->write(this->super, this->columnSpliter);
		this->super->write(this->super, this->spacecraftStatusCache[spacecraft->status]);
		this->super->write(this->super, this->columnSpliter);
		this->super->write(this->super, this->spacecraftSourceCache[i]);
		this->super->write(this->super, this->columnSpliter);
		this->super->write(this->super, this->spacecraftDestinationCache[i]);
		this->super->write(this->super, this->columnSpliter);

		if (spacecraft->status != SPACECRAFT_STATUS_DESTROYED) {
			this->super->writeFormat(this->super, "%-*d", (int)this->spacecraftColumnsWidthCache[4], spacecraft->distanceInHours);
			this->super->write(this->super, this->columnSpliter);
			spacecraft->estimatedArrivalDateTime->toString(spacecraft->estimatedArrivalDateTime, buffer, true, false);
			this->super->writeFormat(this->super, "%-*s", (int)this->spacecraftColumnsWidthCache[5], buffer);
		}
		else {
			this->super->write(this->super, this->spacecraftDistanceInHoursEmptyValueCache);
			this->super->write(this->super, this->columnSpliter);
			this->super->write(this->super, this->spacecraftEstimatedArrivalTimeEmptyValueCache);
		}
		this->super->write(this->super, "\n");
	}
}

void destroySimulationStreamWriter(SimulationStreamWriter this) {
	size_t i;
	if (this == NULL) return;

	free(this->planetColumnsWidthCache);
	free(this->planetNameRowHeader);
	free(this->planetDateTimeRowHeader);
	free(this->planetPopulationRowHeader);

	for (i = 0; i < 3; i++) {
		free(this->planetRowHeaderCache[i]);
	}
	free(this->planetRowHeaderCache);

	for (i = 0; i < this->simulation->planetListSize; i++) {
		free(this->planetNameCache[i]);
	}
	free(this->planetNameCache);

	free(this->spacecraftColumnsWidthCache);
	free(this->spacecraftNameColumnHeader);
	free(this->spacecraftStatusColumnHeader);
	free(this->spacecraftSourceColumnHeader);
	free(this->spacecraftDestinationColumnHeader);
	free(this->spacecraftDistanceInHoursColumnHeader);
	free(this->spacecraftEstimatedArrivalTimeColumnHeader);

	for (i = 0; i < 6; i++) {
		free(this->spacecraftColumnHeaderCache[i]);
	}
	free(this->spacecraftColumnHeaderCache);

	for (i = 0; i < this->simulation->spacecraftListSize; i++) {
		free(this->spacecraftNameCache[i]);
		free(this->spacecraftSourceCache[i]);
		free(this->spacecraftDestinationCache[i]);
		free(this->spacecraftEstimatedArrivalTimeCache[i]);
	}
	free(this->spacecraftNameCache);
	free(this->spacecraftSourceCache);
	free(this->spacecraftDestinationCache);
	free(this->spacecraftEstimatedArrivalTimeCache);

	for (i = 0; i < 4; i++) {
		free(this->spacecraftStatusCache[i]);
	}
	free(this->spacecraftStatusCache);

	free(this->spacecraftDistanceInHoursEmptyValueCache);
	free(this->spacecraftEstimatedArrivalTimeEmptyValueCache);

	free(this->columnSpliter);
	free(this->emptyValue);
	free(this->spacecraftStatusWaiting);
	free(this->spacecraftStatusEnroute);
	free(this->spacecraftStatusArrived);
	free(this->spacecraftStatusDestroyed);

	free(this);
}