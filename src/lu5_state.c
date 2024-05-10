#include "lu5_state.h"

#include "lu5_color.h"

#include "lu5_font.h"

lu5_State lu5 = {
	// use LU5_ERROR_LOG for no logging
	.log_level = LU5_WARN_LOG,
	.style = {
		.strokeWeight = 1,
		.stroke = LU5_BLACK,
		.fill = LU5_WHITE,
		.fontSize = 22
	},
	.env = {
		// Set no limit
		.target_framerate = -1
	}
};

void lu5_list_push(lu5_node **head, void *data, size_t data_size) {
	lu5_node *new_node = (lu5_node*)malloc(sizeof(lu5_node));
	
	new_node->data = data;
	new_node->next = *head;

	*head = new_node;
}

void lu5_list_iter(lu5_node *node, void (*ptr)(void*)) {
	while (node != NULL) {
		if (ptr != NULL) 
			(*ptr)(node->data);

		if (node->next == NULL) 
			break;
		
		node = node->next;
	};
}


void lu5_close(lu5_State *l5) {

	lu5_close_fonts(l5);

	FT_Done_FreeType(l5->ft);

	lua_close(l5->L);
}