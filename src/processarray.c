/* AUTHOR: Kai Li Shi 19157364
 * FILE: processarray.c
 * DATE: 25/10/17
 * PURPOSE: Contains functions used to create, insert into and free the array. 
 *          Also has the two callback functions used in check() */

#include "linkedlist.h"
#include "SpellChecker.h"
#include "processarray.h"
#include <stdio.h>

/* copyToArray
 * Import list (LinkedList*), numWords (integer)
 * Return array (char**)
 * Copies the contents of the linked list and stores it in an array of strings*/
char ** copyToArray(LinkedList * list, int numWords)
{
    LinkedListNode * curr = list->head;
    int i;
    char ** array = (char**)malloc(numWords * sizeof(char*));
    
    for (i = 0; i < numWords; i++)
    {
        array[i] = (char*)malloc(WORDLENGTH * sizeof(char));
        strncpy(array[i], (char*)curr->data, WORDLENGTH);
        curr = curr->next;
    }
    return array;
}


/* freeArray 
 * Import array (char**), size (integer)
 * Return void
 * Frees each element in the array, then frees the array itself */
void freeArray(char ** array, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        free(array[i]);
	array[i] = NULL;
    }
    free(array);
    array = NULL;
}


/* autocorrectYes
 * Import word (char*), suggestion (char*)
 * Return decision (integer)
 * Callback function for check(). Used if the autocorrect setting is yes */
int autocorrectYes(char* word, char* suggestion)
{   
    int decision = TRUE;
    if (suggestion == NULL)
    {   
        printf("Correction for '%s' is unavailable\n", word);
    }
    return decision;
}


/* autocorrectNo
 * Import word (char*), suggestion (char*)
 * Return decision (integer)
 * Callback function for check(). Used if the autocorrect setting is no.
 * Asks the user whether they would like to correct the word to the suggested 
 * word. Continues to ask the user until the user enters a valid option (1 or 2)
 * If the user chooses no then FALSE is returned, otherwise TRUE is returned */
int autocorrectNo(char*word, char*suggestion)
{   
    int decision = TRUE;
    if (suggestion != NULL)
    {   
        char option[100];
        printf("Would you like to correct the word '%s' to '%s'?\n", word, 
               suggestion);
        printf("1. Yes\n2. No\n");
        
	scanf("%1s", option);
	while (strcmp(option, "1") != 0 && strcmp(option,"2") != 0)
	{
            /* clear buffer */
            fgets(option, 100, stdin);
	    printf("Invalid input. Please enter again: ");
            scanf("%1s", option);
	}

	if (strcmp(option, "2") == 0)
	{
	    decision = FALSE;
	}
    }
    else
    {   
        printf("Correction for '%s' is unavailable\n", word);
    }
    return decision;
}

