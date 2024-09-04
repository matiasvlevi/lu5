#include "lu5_style.h"
#include "lu5_state.h"

#include <lauxlib.h>
#include <stdlib.h>

void lu5_style_push(lu5_State *l5, lu5_style_setting *style)
{
	if (l5->style_stack_len >= 0 && l5->style_stack_len < LU5_MAX_STYLE_STACK) {
		lu5_style_setting *new_style = (lu5_style_setting*)malloc(sizeof(lu5_style_setting));

		*new_style = *style;

		l5->style_stack[l5->style_stack_len] = new_style;
		l5->style_stack_len++;
	}
}

void lu5_style_pop(lu5_State *l5)
{
	if (l5->style_stack_len > 0 && l5->style_stack_len <= LU5_MAX_STYLE_STACK) {
		lu5_style_setting *popped = l5->style_stack[l5->style_stack_len - 1];
		if (popped != NULL) {
			free(popped);
			l5->style_stack_len--;
		} else {
			luaL_error(l5->L, "Could not pop style from stack, popped element was null...");
		}
	}
}

void lu5_style_clear(lu5_State *l5)
{
    for (int i = 0; i < l5->style_stack_len; i++) 
    {
        if (l5->style_stack[i] != NULL)
            free(l5->style_stack[i]);

        l5->style_stack[i] = NULL;
    }
}