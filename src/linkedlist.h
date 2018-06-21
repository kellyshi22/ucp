/* AUTHOR: Kai Li Shi 19157364
 * FILE: linkedlist.h
 * DATE: 25/10/17
 * PURPOSE: Header file for linkedlist.c. Includes method declarations and
 *          typedef declarations for the LinkedList and LinkedListNode */

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/* Typedef for the list node. It has the fields:
 * data (void*), a pointer to the data to be stored in the node.
 * next (LinkedListNode*), a pointer to the next node in the list. */
typedef struct LinkedListNode {
    void * data;
    struct LinkedListNode * next;
} LinkedListNode;


/* Typedef for a double ended list. It has the fields:
 * head (LinkedListNode*), a pointer to the first node. 
 * tail (LinkedListNode*), a pointer to the last node.
 * count (integer), the number of nodes in the list.
 * The list is used to store the words in the dictionary file
 * and the words in the user file of the program */
typedef struct {
    LinkedListNode* head;
    LinkedListNode* tail;
    int count;
} LinkedList;

LinkedList* createLinkedList();
void insertStart(LinkedList ** list, LinkedListNode * newNode);
LinkedListNode* removeStart(LinkedList** list);
LinkedListNode* retrieveElement (LinkedList** list, int index);
void printList(LinkedList** list);
void freeLinkedList(LinkedList** list);
void insertLast(LinkedList ** list, LinkedListNode * newNode);

#endif 
