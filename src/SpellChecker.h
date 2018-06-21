/* AUTHOR: Kai Li Shi 19157364
 * FILE: SpellChecker.h 
 * DATE: 25/10/17
 * PURPOSE: Header file for SpellChecker.c. Contains the typedef struct
 *          declaration */

#ifndef SPELLCHECKER_H
#define SPELLCHECKER_H

/* typedef for a struct of Settings
 * has the fields:
 * dictfile (string), the name of the dictionary file
 * maxdifference (integer), the maximum difference between the misspelt word 
 * and the corrction
 * autocorrect (string), 'yes' or 'no' indicating whether the corrections are 
 * automatically applied or not */
typedef struct {
    char * dictfile;
    int maxdifference;
    char * autocorrect;
} Settings;


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE !FALSE
#define WORDLENGTH 50
/* default length of words is 50 characters long. the longest word in the dictionary
 * is less than 50 characters */

#endif
