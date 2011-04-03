/*
 *  LinkedList.c
 *
 *  Created by Simon Dittlmann.
 *
 */

#include "LinkedList.h"
#include <stdlib.h>
#include <string.h>

struct LinkedList {
	int * size;
	void * val;
	struct LinkedList * next;
};


LinkedList * LinkedList_Create() {
	LinkedList * self = NULL;
	if ((self = malloc(sizeof(LinkedList))) == NULL) {
		return NULL;
	}

	if ((self->size = malloc(sizeof(int))) == NULL) {
		free(self);
		return NULL;
	}

	self->next = NULL;
	*(self->size) = 0;

	return (LinkedList *) self;

}


void LinkedList_Destroy(LinkedList * self) {
	if (self != NULL) {
		void * a;
		int * size = (self->size);
		int i;

		for (i = *size; i > 0; i-- ) {
			a = LinkedList_remove(&self);
		}
		free(size);
		free(self);
		self = NULL;
		size = NULL;
	}

}

void * LinkedList_remove(LinkedList ** self) {
	if (*self == NULL) {
		return NULL;
	}

	LinkedList * newlist = NULL;
	void * var = NULL;

	if ((*((*self)->size)) > 0) {
		var = (*self)->val;
		--(*((*self)->size));

		if ((*self)->next != NULL) {
			newlist = (*self)->next;
			free((*self));
			(*self) = NULL;
			*self = newlist;
		} else {
			newlist = (*self);
			(*self)->val = NULL;
			(*self)->next = NULL;
		}

	}

	return var;
}

void * LinkedList_remove_last(LinkedList ** self) {
	if (self == NULL) {
		return NULL;
	}

	int i;
	LinkedList * current;
	void * result = NULL;

	for (current = *self, i = 0; current != NULL && i < LinkedList_size(*self); current = current->next, i++) {
		result = current->val;
	}

	if (result != NULL) {
		*((*self)->size) -= 1;
		free(current);
	}
	return result;
}

void * LinkedList_get(LinkedList * self, int pos) {
	if (self == NULL ||
			pos <= 0 ||
			pos > *(self->size)) {
		return NULL;
	}


	int i;
	void * val;
	LinkedList * current;

	for (current = self, i = 0; current != NULL && i < pos; current = current->next, i++) {
		val = current->val;
	}

	return val;
}

int LinkedList_add(LinkedList * self, void * var) {
	if (self == NULL || var == NULL) {
		return CDS_ILLEGAL_ARGUEMENT_EXCEPTION;
	}

	LinkedList * position;
	LinkedList * last_position = NULL;
	LinkedList * local_list = NULL;

	if ((*(self->size)) == 0) {
		self->next = NULL;
		self->val = var;
	} else {

		if ((local_list = malloc(sizeof(LinkedList))) == NULL) {
			return CDS_OUT_OF_MEMORY_EXCEPTION;
		}

		local_list->size = self->size;
		local_list->val = var;
		local_list->next = NULL;


		for (position = self; position != NULL ; position = position->next) {
			last_position = position;
		}
		//assert((last_position != NULL));
		last_position->next = local_list;

	}

	*(self->size) += 1;

	return CDS_OK;
}

int LinkedList_size(LinkedList * self) {
	if (self == NULL) {
		return -1;
	}
	return *(self->size);
}

_Bool LinkedList_contains(LinkedList * self, void * to_check,  equalsFunction equals) {
	int size = *(self->size);
	void * var = NULL;

	for (int i=1; i <= size; i++) {

		var = LinkedList_get(self, i);

		if ((*equals)(var, to_check))
			return true;
	}

	return false;
}

void * LinkedList_removeFirstOccurrence(LinkedList ** self, void * to_delete, equalsFunction equals) {
	if (*self == NULL ||
			to_delete == NULL ||
			equals == NULL) {
		return NULL;
	}

	int size = *((*self)->size);
	LinkedList * current = NULL;
	LinkedList * last = *self;
	void * var = NULL;

	for (current = *self; current != NULL && size != 0; current = current->next) {
		var = current->val;
		if ((*equals)(var, to_delete)) {

			if (last == current) { // match in first element
				if (current->next == NULL) { // list have only one element
					current->val = NULL;
				} else { // list size is greater 1
					*self = current->next;
					free(current);
				}
			}   else { // match between or in last element
				last->next = current->next;
				free(current);
			}

			*(last->size) -= 1;
			return var;
		}
	}

	return NULL;
}

int LinkedList_destroy_all_items(LinkedList ** list, destroy_f_ptr f_ptr) {
	if (*list == NULL ||
			f_ptr == NULL) {
		return CDS_ILLEGAL_ARGUEMENT_EXCEPTION;
	}

	void * current = NULL;
	int size = LinkedList_size(*list);
	int i = 0;
	
	/*
	   to prevent memory fragmentation remove last first.
	*/
	
	for (i = 1; i <= size; i++) {
		current = NULL;
		current = LinkedList_remove_last(list);
		if (current != NULL) {
			f_ptr(current);
		}
	}

	return CDS_OK;
}

static iterator_item _next(iterator_iterate_on in, int * pos) {
	if (in == NULL || *pos < 0) {
		return NULL;
	}

	LinkedList * self = (LinkedList *) in;
	void * item = LinkedList_get(self, *pos);
	*pos += 1;
	return item;
}

static _Bool _has_next(iterator_iterate_on in, int pos) {
	if (in == NULL || pos < 0) {
		return false;
	}

	void * item;
	LinkedList * self = (LinkedList *) in;

	item = LinkedList_get(self, pos);

	return item != NULL;
}

Iterator * LinkedList_iterator(LinkedList * self) {
	return Iterator_Create((iterator_iterate_on) self, _has_next, _next, 1);
}
