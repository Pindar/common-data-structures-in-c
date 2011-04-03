/*
 * LinkedList.h
 *
 *      Author: Simon Dittlmann
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <stdbool.h>
#include "iterator.h"
#include "errors.h"

typedef struct LinkedList LinkedList;
typedef void (*destroy_f_ptr) (void *);
typedef _Bool (*equalsFunction)(void*, void *);

LinkedList * LinkedList_Create(void);

/**
 * free LinkedList, be careful: you can lost your ptrs to the values
 */
void LinkedList_Destroy(LinkedList *);
int LinkedList_destroy_all_items(LinkedList ** list, destroy_f_ptr f_ptr);

void * LinkedList_remove(LinkedList **);
void * LinkedList_remove_last(LinkedList **);
void * LinkedList_removeFirstOccurrence(LinkedList ** self, void *, equalsFunction);

int LinkedList_add(LinkedList *, void *);

void * LinkedList_get(LinkedList *, int position);
_Bool LinkedList_contains(LinkedList * self, void * to_check,  equalsFunction);

int LinkedList_size(LinkedList * );

Iterator * LinkedList_iterator(LinkedList *);
#endif /* LINKEDLIST_H_ */
