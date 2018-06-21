/* AUTHOR: Kai Li Shi 19157364
 * FILE: linkedlist.c
 * DATE: 25/10/17
 * PURPOSE: Contains linked list operations for a generic list. This file was 
 *          previously submitted for Practical 6  but has been modified since 
 *          submission */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"
#define FALSE 0
#define TRUE !FALSE

/* createLinkedList 
 * Import none
 * Return list (LinkedList*)
 * Allocates memory for a linked list. Initialises the LinkedList fields and 
 * returns the list. Returns NULL if an error occured */ 
LinkedList* createLinkedList()
{
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->count = 0;
    return list;
}


/* insertStart
 * Import list (LinkedList**), newNode (LinkedListNode*)
 * Return none 
 * Inserts a new node to the start of the list. */
void insertStart(LinkedList ** list, LinkedListNode * newNode)
{
    newNode->next = (*list)->head;
    (*list)->head = newNode;
    (*list)->count = (*list)->count+1;
    if ((*list)->count == 1)
    {
        (*list)->tail = newNode;
    }
}


/* insertLast
 * Import list (LinkedList**), newNode (LinkedListNode*)
 * Return none
 * Imports a new node and inserts it at the end of the list */
void insertLast(LinkedList ** list, LinkedListNode * newNode)
{
    if ((*list)->head == NULL)
    {
        insertStart(list, newNode);
    }
    else
    {
        newNode->next = NULL;
        (*list)->tail->next = newNode;
        (*list)->tail = newNode;
        (*list)->count = (*list)->count+1;
    }
}


/* removeStart
 * Import list (LinkedList **)
 * Return temp (LinkedListNode*)
 * Removes and returns the first node in the list */
LinkedListNode* removeStart(LinkedList** list)
{
    LinkedListNode * temp = (*list)->head; /* make copy of the head pointer */
    (*list)->head = (*list)->head->next; /* point head to second element */
    (*list)->count = (*list)->count - 1;
    return temp; /* return pointer to the removed node */
}


/* retrieveElement 
 * Import list (LinkedList**), index (integer)
 * Returns current (LinkedListNode*)
 * Returns the value of the nth index in the list */
LinkedListNode* retrieveElement (LinkedList** list, int index)
{
    LinkedListNode * current = (*list)->head;
    int done = FALSE, i = 0;
    
    if (index < i) /* negative index */
    {
        current = NULL;
        printf("Error. Index is negative\n\n");
    }
    else if (current == NULL) /*empty list*/
    {
        printf("The list is empty");
    }
    else
    {
        while (done == FALSE && current->data != NULL)
        {
            if (i == index)
            {
                done = TRUE;
            }
            else
            {
                if (current -> next != NULL)
                {
                    current = current -> next;
                    i++;
                }
                else
                {
                    current = NULL;
                    done = TRUE;
                }
            }
        }
    }
    
    if (done == TRUE && current == NULL && index > i)
    {
        printf("Error. Node does not exist\n");
    }
    return current;
}


/* freeLinkedList 
 * Import list (LinkedList **)
 * Return none
 * Frees each node in the list, then frees the list itself */
void freeLinkedList(LinkedList** list)
{
    LinkedListNode *current, *nextNode;
    current = (*list)->head;
    while (current != NULL)
    {
        nextNode = current->next;
        free(current->data);
        free(current);
        current = nextNode;
    }
    free(*list);
}

