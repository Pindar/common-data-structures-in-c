/*
 * array_list.c
 *
 *  Created on: 21.02.2011
 *      Author: simon
 */
#include "array_list.h"
#include <string.h>
#include <stdlib.h>


struct Array_list {
	size_t capacity;
	size_t size;
	void ** array;
};

Array_list * Array_list_Create(unsigned int capacity) {


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
	memset(self->array, 0, capacity * sizeof(void *));

	return self;
}

void Array_list_Destroy(Array_list * self) {
	if (self != NULL) {

		free(self->array);
		free(self);
	}
}

size_t Array_list_get_capacity(Array_list * self) {
	if (self == NULL) {
		return 0;
	}
	return self->capacity;
}

static int _double_capacity(Array_list * self) {
	size_t new_capacity;
	void ** new_array;

	new_capacity = 2 * Array_list_get_capacity(self);

	// double capacity and copy all values.
	new_array = realloc(self->array, new_capacity * sizeof(void *));
	if (new_array == NULL) {
		return ARRAY_LIST_OUT_OF_MEMORY_EXCEPTION;
	}
	memset(new_array + self->capacity + 1, 0, (new_capacity * sizeof(void *) / 2) - 1);
	self->capacity = new_capacity;
	self->array = new_array;


	return ARRAY_LIST_OK;
}

static int _shift_to_right(Array_list * self, unsigned int idx) {
	size_t i;

	if (self->capacity == Array_list_size(self)) {
		_double_capacity(self);
	}
	// we can now move all elements one slot to the right

	for (i = Array_list_size(self); i >= idx; i -= 1) {
		self->array[i + 1] = self->array[i];
		if (i == 0) {
			break;
		}
	}


	return ARRAY_LIST_OK;
}

int Array_list_add_on_index(Array_list * self, unsigned int idx, void * element) {
	if (self == NULL || element == NULL) {
		return ARRAY_LIST_ILLEGAL_ARGUEMENT_EXCEPTION;
	}
	if (idx > self->size) {
		return ARRAY_LIST_INDEX_OUT_OF_BOUNDS_EXCEPTION;
	}

	if (self->array[idx] != NULL) {
		_shift_to_right(self, idx);
	}

	self->array[idx] = element;
	self->size += 1;

	return ARRAY_LIST_OK;
}

void * Array_list_get(Array_list * self, unsigned int idx) {
	if (self == NULL || idx > Array_list_size(self) - 1) {
		return NULL;
	}

	return self->array[idx];
}

size_t Array_list_size(Array_list * self) {
	if (self == NULL) {
		return 0;
	}
	return self->size;
}

size_t Array_list_calculate_json_array_length(Array_list * self, array_list_json_length_f_ptr calculate_item_f) {
	enum {
		JSON_OVERHEAD = 5
	};
	size_t i,
		   sum = 0;


	for (i = 0; i < Array_list_size(self); i += 1) {
		sum += calculate_item_f(self->array[i]);
	}

	return sum + JSON_OVERHEAD;
}

int Array_list_to_json_array(Array_list * self, array_list_to_json_f_ptr item_to_json_f, array_list_json_length_f_ptr item_json_length_f, char ** json, int status_ok)
{
	if (self == NULL || item_to_json_f == NULL || item_json_length_f == NULL) {
		return ARRAY_LIST_ILLEGAL_ARGUEMENT_EXCEPTION;
	}
	status_ok = status_ok;
	item_json_length_f = item_json_length_f;
	item_to_json_f = item_to_json_f;

	size_t json_array_len;
	unsigned int i;
	char *json_array = NULL,
		 *json_array_ptr = NULL;
	const char *begin = "[ ";
	const char *end = " ]";
	int error_code = 0;
	int result_len = 0;
	unsigned int processed_items = 0;

	json_array_len = Array_list_calculate_json_array_length(self, item_json_length_f);
	json_array_ptr = realloc((*json), json_array_len * sizeof(char));
	memset(json_array_ptr, 0, json_array_len * sizeof(char));

	json_array = json_array_ptr;

	strncat(json_array_ptr, begin, strlen(begin));
	json_array_ptr += strlen(begin);

	for (i = 0; i < Array_list_size(self); i += 1) {

		error_code = item_to_json_f(Array_list_get(self, i), (void **) &json_array_ptr, &result_len);
		if (error_code != status_ok) {
			return ARRAY_LIST_OUT_OF_MEMORY_EXCEPTION;
		}
		json_array_ptr += (result_len);

		processed_items += 1;
		if (processed_items != Array_list_size(self)) {
			// add a comma
			strcat(json_array_ptr, ", ");
			json_array_ptr += 2;
		}
	}

	strcat(json_array, end);
	*json = json_array;

	return ARRAY_LIST_OK;
}

void * Array_list_remove_last(Array_list * self) {
	if (self == NULL || Array_list_size(self) == 0) {
		return NULL;
	}

	size_t size = Array_list_size(self);
	self->size -= 1;
	return self->array[size - 1];
}

int Array_list_destroy_all_items(Array_list * self, array_list_destroy_f_ptr f_ptr) {
	if (self == NULL || f_ptr == NULL) {
		return ARRAY_LIST_ILLEGAL_ARGUEMENT_EXCEPTION;
	}

	size_t i;
	void * item;

	for (i = Array_list_size(self); i > 0; i -= 1) {

		item = Array_list_remove_last(self);
		f_ptr(item);

	}

	// i == 0
	item = Array_list_remove_last(self);
	f_ptr(item);

	return ARRAY_LIST_OK;
}

static iterator_item _next(iterator_iterate_on in, int * pos) {
	if (in == NULL || *pos < 0) {
		return NULL;
	}
	Array_list * self = (Array_list *) in;
	void * item = Array_list_get(self, (unsigned int) *pos);
	*pos += 1;

	return item;
}

static _Bool _has_next(iterator_iterate_on in, int pos) {
	if (in == NULL || pos < 0) {
		return false;
	}

	Array_list * self = (Array_list *) in;

	return Array_list_get(self, (unsigned int) pos) != NULL;
}

Iterator * Array_list_iterator(Array_list * self) {
	return Iterator_Create((iterator_iterate_on) self, _has_next, _next, 0);
}
