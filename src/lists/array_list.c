/*
 * array_list.c
 *
 *  Created on: 21.02.2011
 *      Author: simon
 */
#include "array_list.h"

struct Array_list {
	int size;
	void ** array;
};

Array_list * Array_list_Create(int size) {

	Array_list * self = (Array_list*) malloc(sizeof(Array_list));

	if (self == NULL) {
		return self;
	}

	size = (size == 0) ? ARRAY_LIST_DEFAULT_INIT_SIZE : size;
	self->size = size;

	self->array = malloc(size * sizeof(void *));

	return self;
}

void Array_list_Destroy(Array_list * self) {
	if (self != NULL) {

		free(self->array);
		free(self);
	}
}
