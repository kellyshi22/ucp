/* AUTHOR: Kai Li Shi 19157364
 * FILE: processarray.h
 * DATE: 25/10/17
 * PURPOSE: Header file for processarray.c. Includes method declarations */

#ifndef PROCESSARRAY_H
#define PROCESSARRAY_H


int autocorrectYes(char* word, char* suggestion);
int autocorrectNo(char*word, char*suggestion);
char ** copyToArray(LinkedList * list, int numWords);
void freeArray(char ** array, int size);

#endif
