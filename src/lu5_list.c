


#include "lu5_list.h"

#include <stdlib.h>

void lu5_list_push(lu5_node **head, void *data, size_t data_size) 
{
	lu5_node *new_node = (lu5_node*)malloc(sizeof(lu5_node));
	
	new_node->data = data;
	new_node->next = *head;

	*head = new_node;
}

void lu5_list_iter(lu5_node *node, void (*ptr)(void*)) 
{
	while (node != NULL) {
		if (ptr != NULL) 
			(*ptr)(node->data);

		if (node->next == NULL) 
			break;
		
		node = node->next;
	};
}

void lu5_list_iter_close(lu5_node *node, void(*callback)(void*)) 
{
	while (node != NULL)
	{
		lu5_node *next_node;
		next_node = node->next;

		if (callback != NULL) 
			(*callback)(node->data);

		if (next_node == NULL) 
			break;
		
		free(node);
		node = next_node;
	};
}