#ifndef _LU5_CORE_H_
#define _LU5_CORE_H_

#include "lu5_state.h"

/**
 * Generic Linked lists used to track loaded images and font pointers. 
 *
 */

typedef struct lu5_node_s {
	void *data;
	struct lu5_node_s *next;
} lu5_node;

void lu5_list_push(lu5_node **head, void *data, size_t data_size);
void lu5_list_iter(lu5_node *node, void (*ptr)(void*));
void lu5_list_iter_close(lu5_node *node, void (*ptr)(void*));

#endif
