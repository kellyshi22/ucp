/* AUTHOR: Kai Li Shi 19157364
 * FILE: linkedlist.c
 * DATE: 25/10/17
 * PURPOSE: Contains main(). Checks for errors, allocates and frees memory as 
 * needed. */

#include "SpellChecker.h"
#include "linkedlist.h"
#include "check.h"
#include "processarray.h"
#include "fileio.h"

int main (int argc, char * argv[])
{
    if (argc == 1) /* invalid no of command line arguments */
    {
        printf("To use the program please enter ./SpellChecker filename\n");
    }
    else if (argc >= 3)
    {
        printf("Error. One file name must be entered\n");
    }
    else
    {
        /* open the user file */
        FILE * userFile = fopen(argv[1], "r");
        if (userFile == NULL)
        {
            perror("Error opening user file");
        }
        else
        {
	    /* open settings file */
            FILE * settingsFile = fopen(".spellconf", "r");
            if (settingsFile == NULL)
            {
                perror("Error opening settings file");
            }
            else
            {
                char ** dictionaryArray, ** userArray;
		/* malloc settings pointer */
                Settings * settingsPtr = (Settings*)malloc(sizeof(Settings));
                settingsPtr->dictfile = (char*)malloc(100*sizeof(char));
                settingsPtr->autocorrect = (char*)malloc(4*sizeof(char));
                
		/* read settings file & initlialise fields in the struct */
                settingsPtr = processSettings(settingsFile, settingsPtr);
                
		/* if settings file is complete */
                if (settingsPtr != NULL)
                {
		    /* open dictionary file and save words in a linked list */
                    FILE * dictionaryFile = fopen(settingsPtr->dictfile, "r");
                    if (dictionaryFile != NULL)
                    {
                        LinkedList * dictList, * userList;
                        /* create linked list for dictionary words */
                        dictList = createLinkedList();

                        if (dictList != NULL)
                        {
                            dictList = readFile(dictionaryFile, dictList);
                            printf("Dictionary file has been stored in the list");
			    /* copy the dictionary list to an array */
                            dictionaryArray = copyToArray(dictList, dictList->count);
                            printf(" and array\n");
                            
			    /* create user linked list */
                            userList = createLinkedList();
                            if (userList != NULL)
                            {
                                int (*ptr)(char*, char*) = NULL;
                                userList = readUserFile(userFile, userList);
                                printf("User file has been stored in the list");
				/* copy the user list to an array */
                                userArray = copyToArray(userList, userList->count);
                                printf(" and array\n");

				/* check autocorrect value and point pointer to 
				 * the correct function, to be passed to check*/
                                if (strcmp(settingsPtr->autocorrect, "no") == 0)
                                {
                                    ptr = &autocorrectNo;
			        }
          	                else
			        {
                                    ptr = &autocorrectYes;
                                }
				
				/* call check function */
                                check(userArray, userList->count, 
                                      dictionaryArray, dictList->count, 
                                      settingsPtr->maxdifference, ptr);
				
                                /* write correct words back to user file */
                                writeFile(userArray, userList->count, argv[1]);
                                printf("%s has been corrected\n", argv[1]);
                                freeArray(userArray, userList->count);
                            }
                            freeLinkedList(&userList);
                            freeArray(dictionaryArray, dictList->count);
                        }
                        freeLinkedList(&dictList);
                        fclose(dictionaryFile);
                    }
                    else
                    {
                        perror("Error opening dictionary file");
                    }
                    free(settingsPtr->autocorrect);
                    settingsPtr->autocorrect = NULL;
                    free(settingsPtr->dictfile);
                    settingsPtr->dictfile = NULL;
                    free(settingsPtr);
                    settingsPtr = NULL;
                }
                fclose(userFile);
                fclose(settingsFile);
            }
        }
    }
    return 0;
}

