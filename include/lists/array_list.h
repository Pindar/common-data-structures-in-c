/*
 * array_list.h
 *
 *  Created on: 21.02.2011
 *      Author: simon
 */

#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_
#include <string.h>
#include "iterator.h"

enum {
	ARRAY_LIST_OK,
	ARRAY_LIST_INDEX_OUT_OF_BOUNDS_EXCEPTION,
	ARRAY_LIST_ILLEGAL_ARGUEMENT_EXCEPTION,
	ARRAY_LIST_OUT_OF_MEMORY_EXCEPTION
};

enum {
	ARRAY_LIST_DEFAULT_INIT_SIZE = 128
};

typedef struct Array_list Array_list;
typedef int (*array_list_to_json_f_ptr)(void *, void **, int*);
typedef size_t (*array_list_json_length_f_ptr) (void *);
typedef void (*array_list_destroy_f_ptr) (void *);

Array_list * Array_list_Create(unsigned int init_size);
void Array_list_Destroy(Array_list * self);
int Array_list_destroy_all_items(Array_list *, array_list_destroy_f_ptr f_ptr);

size_t Array_list_get_capacity(Array_list *);
void * Array_list_get(Array_list * self, unsigned int idx);
void * Array_list_remove_last(Array_list * self);
int Array_list_add_on_index(Array_list *, unsigned int idx, void *);
size_t Array_list_size(Array_list *);

size_t Array_list_calculate_json_array_length(Array_list *, array_list_json_length_f_ptr item_json_length_f);

int Array_list_to_json_array(Array_list *, array_list_to_json_f_ptr item_to_json_f, array_list_json_length_f_ptr item_json_length_f, char ** json, int status_ok);

Iterator * Array_list_iterator(Array_list * self);

#endif /* ARRAY_LIST_H_ */
