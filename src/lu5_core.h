#ifndef _LU5_CORE_H_
#define _LU5_CORE_H_

#include "./lu5_state.h"

#include <setjmp.h>

WASM_EXPORT("_lu5_get_handle")
lu5_State *lu5_get_handle(void);

WASM_EXPORT("_lu5_init")            
void lu5_init(lu5_State *l5);

// Export lu5 runtime
WASM_EXPORT("_lu5_setup")            
int lu5_run_sketch(lu5_State *l5, const char *filename, const char *source);

WASM_EXPORT("_lu5_animation_frame") 
void lu5_animation_frame(lu5_State *l5, float delta_time);

WASM_EXPORT("_lu5_close")
void lu5_close(lu5_State *l5);





#endif