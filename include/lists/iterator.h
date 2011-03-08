/*
 * iterator.h
 *
 *  Created on: 09.12.2010
 *      Author: dittlmann
 */

#ifndef ITERATOR_H_
#define ITERATOR_H_

#include <stdbool.h>

typedef struct Iterator Iterator;
typedef void * iterator_item;
typedef void * iterator_iterate_on;
typedef _Bool (*iterator_has_next_f) (iterator_iterate_on, int);
typedef iterator_item (*iterator_next_f) (iterator_iterate_on, int*);

Iterator * Iterator_Create(iterator_iterate_on, iterator_has_next_f, iterator_next_f);
void Iterator_Destroy(Iterator *);

_Bool Iterator_has_next(Iterator *);

iterator_item Iterator_next(Iterator *);

#endif /* ITERATOR_H_ */
