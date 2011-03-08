/*
 * array_list.c
 *
 *  Created on: 21.02.2011
 *      Author: simon
 */
#include "array_list.h"
#include "string.h"

struct Array_list {
	int capacity;
	int size;
	void ** array;
};

Array_list * Array_list_Create(int capacity) {

	if (capacity < 0) {
		return NULL;
	}

	Array_list * self = (Array_list*) malloc(sizeof(Array_list));

	if (self == NULL) {
		return NULL;
	}

	capacity = (capacity == 0) ? ARRAY_LIST_DEFAULT_INIT_SIZE : capacity;
	self->capacity = capacity;
	self->size = 0;
	self->array = malloc(capacity * sizeof(void *));
	if (self->array == NULL) {
		free(self);
		return NULL;
	}
	memset(self->array, 0, sizeof(self->array));

	return self;
}

void Array_list_Destroy(Array_list * self) {
	if (self != NULL) {

		free(self->array);
		free(self);
	}
}

int Array_list_get_capacity(Array_list * self) {
	if (self == NULL) {
		return -1;
	}
	return self->capacity;
}


int Array_list_add_on_index(Array_list * self, int idx, void * element) {
	if (self == NULL || element == NULL) {
		return ARRAY_LIST_ILLEGAL_ARGUEMENT_EXCEPTION;
	}
	if (idx < 0 || idx > self->size) {
		return ARRAY_LIST_INDEX_OUT_OF_BOUNDS_EXCEPTION;
	}
	if (self->array[idx] != NULL) {
		//_shift_to_right(self, idx);
	}

	self->array[idx] = element;
	self->size += 1;

	return ARRAY_LIST_OK;
}

int Array_list_size(Array_list * self) {
	return self->size;
}
