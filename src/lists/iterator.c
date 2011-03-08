#include "iterator.h"

#include "stdlib.h"

struct Iterator {
	iterator_iterate_on io;
	iterator_has_next_f has_next;
	iterator_next_f next;
	int position;
};


Iterator * Iterator_Create(iterator_iterate_on io, iterator_has_next_f has_next_f, iterator_next_f next_f) {
	Iterator * self = malloc(sizeof(Iterator));
	if (self == NULL) {
		return NULL;
	}

	self->io = io;
	self->has_next = has_next_f;
	self->next = next_f;
	self->position = 0;

	return self;
}

void Iterator_Destroy(Iterator * self) {

	free(self);
	self = NULL;
}

_Bool Iterator_has_next(Iterator * self) {
	return (self->has_next != NULL) ? self->has_next(self->io, self->position) : false;
}

iterator_item Iterator_next(Iterator * self) {
	return (self->next != NULL) ? self->next(self->io, &self->position) : NULL;
}
