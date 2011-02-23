/*
 * array_list.h
 *
 *  Created on: 21.02.2011
 *      Author: simon
 */

#ifndef ARRAY_LIST_H_
#define ARRAY_LIST_H_

enum {
	ARRAY_LIST_OK,
	ARRAY_LIST_INDEX_OUT_OF_BOUNDS_EXCEPTION,
	ARRAY_LIST_ILLEGAL_ARGUEMENT_EXCEPTION
};

enum {
	ARRAY_LIST_DEFAULT_INIT_SIZE = 128
};

typedef struct Array_list Array_list;

Array_list * Array_list_Create(int init_size);
void Array_list_Destroy(Array_list * self);

int Array_list_get_capacity(Array_list *);
int Array_list_add_on_index(Array_list *, int idx, void *);
int Array_list_size(Array_list *);
#endif /* ARRAY_LIST_H_ */
