/*
 * LinkedList.h
 *
 *  Created on: 13.09.2010
 *      Author: dittlmann
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <stdbool.h>
#include "errors.h"

typedef struct LinkedList LinkedList;
typedef void (*destroy_f_ptr) (void *);

LinkedList * LinkedList_Create(void);

/**
 * free LinkedList, be careful: you can lost your ptrs to the values
 */
void LinkedList_Destroy(LinkedList *);

void * LinkedList_remove(LinkedList **);
void * LinkedList_remove_last(LinkedList **);

void * LinkedList_get(LinkedList *, int position);

int LinkedList_add(LinkedList *, void *);

int LinkedList_size(LinkedList * );

typedef _Bool (*equalsFunction)(void*, void *);

_Bool LinkedList_contains(LinkedList * self, void * to_check,  equalsFunction);

void * LinkedList_removeFirstOccurrence(LinkedList ** self, void *, equalsFunction);

int LinkedList_destroy_all_items(LinkedList ** list, destroy_f_ptr f_ptr);

#endif /* LINKEDLIST_H_ */
