/* AUTHOR: Kai Li Shi 19157364
 * FILE: fileio.h 
 * DATE 25/10/17
 * PURPOSE: Header file for fileio.c. Includes method declarations */

#ifndef FILEIO_H
#define FILEIO_H

void writeFile(char** array, int numWords, char * fileName);
Settings * processSettings(FILE* settingsFile, Settings * settingsPtr);
LinkedList * readFile(FILE* file, LinkedList * list);
LinkedList * readUserFile(FILE* file, LinkedList* list);

#endif 
