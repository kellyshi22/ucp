/* AUTHOR: Kai Li Shi 19157364
 * FILE: fileio.c
 * DATE: 25/10/17
 * PURPOSE: Contains all functions related to the reading and writing of files*/          
#include "SpellChecker.h"
#include "linkedlist.h"
#include "fileio.h"

/* writeFile 
 * Import array (char**), numWords (integer), fileName (char*)
 * Return none
 * Opens a file and writes the contents of the array to the file. Each word
 * in the array is written on a new line */
void writeFile(char** array, int numWords, char * fileName)
{
    FILE * f = fopen(fileName, "w");
    if (f == NULL)
    {   
        perror("Error.");
    }
    else
    {   
        int i; 
        for (i = 0; i < numWords; i++)
        {   
            fputs(array[i], f);
            fputs("\n", f);
        }
        fclose(f);
    }
}

/* processSettings 
 * Import settingsFile (FILE*), settingsPtr (Settings*)
 * Export settingsPtr (Settings*)
 * Reads the settings file and stores each of the values in a settings struct.
 * If the same settings name is found multiple times and the values of the
 * settings are different then an error message is shown and NULL is returned.
 * If the same settings name is found multiple times and the values of the 
 * settings are the same then no error is shown and the program will continue.
 * If the settings file is missing one or more settings then an error is shown
 * and NULL is returned. */
Settings * processSettings(FILE* settingsFile, Settings * settingsPtr)
{
    char settingsName[100];
    char value[100];
    int foundDictFile = FALSE, foundMaxDifference = FALSE;
    int foundAutoCorrect = FALSE, multipleFound = FALSE;

    while (EOF != fscanf(settingsFile, "%s = %s", settingsName, value) 
           && multipleFound == FALSE)
    {   
        if (strcmp(settingsName, "dictfile") == 0)
        {   
            /* if dictfile setting hasn't been found yet */
            if (foundDictFile == FALSE)
            {   
                /* copy value to the struct */
                strncpy(settingsPtr->dictfile, value, 100); 
                foundDictFile = TRUE;
            }
            else 
            {   
                /* if dictfile setting has already been found then check if 
                 * the value is the same as the previously found one. 
                 * if it is the same then no error is printed, otherwise
                 * print error */
	        if (strcmp(value, settingsPtr->dictfile) != 0)
		{
		    multipleFound = TRUE;
                    printf("Error. Multiple 'dictfile' settings found.\n");
		}
            }
        }
        
        
        else if (strcmp(settingsName, "maxdifference") == 0)
        {
            /* if maxdifference hasn't been found yet */   
            if (foundMaxDifference == FALSE)
            {   
                /* check that the maxdifference value is an integer */
	        int val;
		if (sscanf(value, "%d", &val) != 1)
		{
		    printf("Maxdifference value is not an integer\n");
		}
		else
		{
                    /* if it is an integer then store in struct */
		    settingsPtr->maxdifference = atoi(value);
                    foundMaxDifference = TRUE;
		}
            }
            else
            {
                /* if maxdifference setting is already found then check if
                 * the value is the same as the previously found one.
                 * if it is the same then no error is printed, otherwise
                 * print error */ 
                if (atoi(value) != settingsPtr->maxdifference)
		{
		    multipleFound = TRUE;
                    printf("Error. Multiple 'maxdifference' settings found.\n");
		}
            }
        }
        
        
        else if (strcmp(settingsName, "autocorrect") == 0)
        {
            /* if autocorrect hasn't been found */
            if (foundAutoCorrect == FALSE)
            {
                /* store in the struct */
		if (strcmp("yes", value) == 0 || strcmp("no", value) == 0)
		{
		    strncpy(settingsPtr->autocorrect, value, 4);
                    foundAutoCorrect = TRUE;
		}
		else
		{
		    multipleFound = TRUE;
		    printf("Error. Invalid autocorrect value\n");
		}
            }
            else
            {
                /* if autocorrect setting is already found then check if 
                 * the value is the same as the previously found one
                 * if it is the same then no error is printed, otherwise 
                 * print an error message */
                if (strcmp(value, settingsPtr->autocorrect) != 0)
		{
		    multipleFound = TRUE;
                    printf("Error. Multiple 'autocorrect' settings found.\n");
		}
            }
        }
    }

    /* if the same setting is found multiple times and their values are
     * different then free the pointer to the struct and set the pointer to 
     * NULL */ 
    if (multipleFound)
    {
        free(settingsPtr->dictfile);
        free(settingsPtr->autocorrect);
        free(settingsPtr);
        settingsPtr = NULL;
    }
    else if (!(foundDictFile && foundAutoCorrect && foundMaxDifference))
    {
        /* if the settings file is missing settings then output error message
         * with a list of the missing settings */
        printf("Error. Settings file is missing the settings(s): \n");
        if (!foundDictFile)
        {
            printf("dictfile\n");
        }
        if (!foundAutoCorrect)
        {
            printf("autocorrect\n");
        }
        if (!foundMaxDifference)
        {
            printf("maxdifference\n");
        }

        /* free settings pointer and set pointer as null */
        free(settingsPtr->dictfile);
        free(settingsPtr->autocorrect);
        free(settingsPtr);
        settingsPtr = NULL;
    }   
    return settingsPtr;
}


/* readFile 
 * Import file (FILE*), list (LinkedList*)
 * Return list (LinkedList*)
 * Reads the file and stores the words in a linked list. If the word contains 
 * '\n' at the end of it then change it to '\0'. */  
LinkedList * readFile(FILE* file, LinkedList * list)
{
    char word[WORDLENGTH];
    int length = 0;
    LinkedListNode * newNode = NULL;
    while (NULL != fgets(word, WORDLENGTH, file))
    {
        length = strlen(word);
        if (word[length-1] == '\n')
        {
            word[length-1] = '\0';
        }
        newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
        newNode->data = (char*)malloc(WORDLENGTH*sizeof(char));
        strncpy(newNode->data, word, WORDLENGTH);

        insertLast(&list, newNode);
    }
    return list;
}


/* readUserFile 
 * Import file (FILE*), list (LinkedList*)
 * Return list (LinkedList*)
 * Reads the user file and stores the words in a linked list. Uses fscanf since
 * words are separated with whitespace. If the word contains '\n' at the end of
 * it then change it to '\0' */
LinkedList * readUserFile(FILE* file, LinkedList* list)
{
    char word[WORDLENGTH];
    int length = 0;
    LinkedListNode * newNode = NULL;
    while (1 == fscanf(file, "%s", word))
    {
        length = strlen(word);
        if (word[length-1] == '\n')
        {
            word[length-1] = '\0';
        }
        newNode = (LinkedListNode*)malloc(sizeof(LinkedListNode));
        newNode->data = (char*)malloc(WORDLENGTH*sizeof(char));
        strncpy(newNode->data, word, WORDLENGTH);
        insertLast(&list, newNode);
    }
    return list;
}

