#include "lu5_state.h"

#include "lu5_color.h"
#include "lu5_font.h"
#include "lu5_image.h"

lu5_State lu5 = {
	// use LU5_ERROR_LOG for no logging
	.log_level = LU5_WARN_LOG,
	.style = {
		.fontSize = 22,
		.fill = LU5_WHITE,
		.stroke = LU5_BLACK,
		.strokeWeight = 1,
		.font_current = NULL
	},
	.style_cache = {
		.fontSize = 22,
		.fill = LU5_WHITE,
		.stroke = LU5_BLACK,
		.strokeWeight = 1,
		.font_current = NULL
	}, 
	.env = {
		// Set no limit
		.target_framerate = -1
	}
};

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

static lu5_node *lu5_list_elem_close(lu5_node *node, void(*callback)(void*)) 
{
	if (callback != NULL) 
		(*callback)(node->data);

	lu5_node *next = node->next;
	free(node);

	return next;
}

void lu5_list_iter_close(lu5_node *node, void(*callback)(void*)) 
{
	while (node != NULL) {
		lu5_node *next_node = lu5_list_elem_close(node, callback);

		if (next_node == NULL) 
			break;
		
		node = next_node;
	};
}


void lu5_close(lu5_State *l5) 
{
	lu5_close_images(l5);

	lu5_close_fonts(l5);

	FT_Done_FreeType(l5->ft);

	lua_close(l5->L);
}
