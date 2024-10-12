#ifndef _LU5_VECTOR_BINDINGS_H_
#define _LU5_VECTOR_BINDINGS_H_

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#define LU5_VECTOR "lu5_vector_"

typedef struct {
	lua_Number x;
	lua_Number y;
	lua_Number z;
} lu5_vector;

lu5_vector* lu5_check_vector(lua_State* L, int index);

/**
 * Create a vector instance.
 *
 * @param x The first component of the vector
 * @param y The second component of the vector
 *
 * @call
 * @param x The first component of the vector
 * @param y The second component of the vector
 * @param z The third component of the vector
 *
 * @return Vector The created vector
 *
 * @example 1
 * local point = createVector(80, 125);
 *
 * print(point);
 * @example
 *
 *
 * @example 2
 * local point = createVector(130, 200, 60);
 *
 * print(point);
 * @example
 */
int createVector(lua_State *L);

/**
 * @name Vector.print
 * Since a `Vector` implements a `print` method, it can be used in the <a href="./io.html#print">`print`</a> function.
 *
 * @example
 * local a = createVector(3, 5);
 * 
 * -- With print
 * print(a);
 *
 * -- With class method
 * Vector.print(a);
 *
 * -- with instance
 * a:print();
 * @example
 */
int lu5_vector_print(lua_State *L);

/**
 * @name Vector.dist
 *
 * @param a The first point (vector)
 * @param b The second point (vector)
 *
 * @return number The distance between the two points
 *
 * @example
 * local a = createVector(300, 500);
 * local b = createVector(200, 250);
 * 
 * local distance = a:dist(b);
 * print(distance);
 * @example
 */
int lu5_vector_dist(lua_State *L);

/**
 * @name Vector.dot
 *
 * @param a The first vector
 * @param b The second vector
 *
 * @return number The dot product
 *
 * @example
 * local a = createVector(3, 5);
 * local b = createVector(1, 3);
 * 
 * -- From prototype
 * print(a:dot(b)); -- 18.0
 *
 * -- With static method
 * print(Vector.dot(a, b)); -- 18.0
 *
 * -- With concat syntax
 * print(a .. b); -- 18.0
 * @example
 */
int lu5_vector_dot(lua_State *L);

/**
 * @name Vector.add
 *
 * @param a The first vector
 * @param b The second vector
 *
 * @return Vector The added vector
 *
 * @example
 * local a = createVector(4, 2);
 * local b = createVector(2, 1);
 *
 * -- Non-mutable
 * print(Vector.add(a, b)); -- { 6.0, 3.0 }
 * print(a + b);            -- { 6.0, 3.0 }
 * print(a);                -- { 4.0, 2.0 }
 * 
 * -- Mutable
 * print(a:add(b));	-- { 6.0, 3.0 }
 * print(a) 		-- { 6.0, 3.0 }
 * @example
 */
int lu5_vector_add(lua_State *L);

/**
 * @name Vector.sub
 *
 * @param a The first vector
 * @param b The second vector
 *
 * @return Vector The subtracted vector
 *
 * @example
 * local a = createVector(3, 5);
 * local b = createVector(2, 3);
 *
 * -- Non-mutable
 * print(Vector.sub(a, b)); -- { 1.0, 2.0 }
 * print(a - b);            -- { 1.0, 2.0 }
 * print(a);                -- { 3.0, 5.0 }
 * 
 * -- Mutable
 * print(a:sub(b)); -- { 1.0, 2.0 }
 * print(a);        -- { 1.0, 2.0 }
 * @example
 */
int lu5_vector_sub(lua_State *L);

/**
 * @name Vector.mult
 *
 * @param a The first vector
 * @param b The second vector
 *
 * @return Vector The multiplied vector
 *
 * @example
 * local a = createVector(3, 5);
 * local b = createVector(2, 3);
 *
 * -- Non-mutable
 * print(Vector.mult(a, b)); -- { 6.0, 15.0 }
 * print(a * b);             -- { 6.0, 15.0 }
 * print(a);                 -- { 3.0, 5.0 }
 * 
 * -- Mutable
 * print(a:mult(b)); -- { 3.0, 15.0 }
 * print(a);         -- { 3.0, 15.0 }
 * @example
 */
int lu5_vector_mult(lua_State *L);

/**
 * @name Vector.div
 *
 * @param a The first vector
 * @param b The second vector
 *
 * @return Vector The divided vector
 *
 * @example
 * local a = createVector(4, 2);
 * local b = createVector(2, 1);
 *
 * -- Non-mutable
 * print(Vector.div(a, b)); -- { 2.0, 2.0 }
 * print(a / b);            -- { 2.0, 2.0 }
 * print(a);                -- { 4.0, 2.0 }
 * 
 * -- Mutable
 * print(a:div(b));	-- { 2.0, 2.0 }
 * print(a) 		-- { 2.0, 2.0 }
 * @example
 */
int lu5_vector_div(lua_State *L);



/**
 * @name Vector.idiv
 *
 * @param a The first vector
 * @param b The second vector
 *
 * @return Vector The divided vector
 *
 * @example
 * local a = createVector(7, 8);
 * local b = createVector(2, 3);
 * 
 * -- Non-mutable
 * print(Vector.idiv(a, b)) -- { 3.0, 2.0 }
 * print(a // b);           -- { 3.0, 2.0 }
 * print(a);                -- { 7.0, 8.0 }
 * 
 * -- Mutable
 * print(a:idiv(b)); -- { 3.0, 2.0 }
 * print(a)          -- { 3.0, 2.0 }
 * @example
 */
int lu5_vector_idiv(lua_State *L);


/**
 * @name Vector.copy
 *
 * @return Vector The copied vector
 *
 * @example
 * local a = createVector(300, 450, 400);
 * 
 * local copy_1 = a:copy();
 *
 * local copy_2 = Vector.copy(a);
 * @example
 */
int lu5_vector_copy(lua_State *L);

/**
 * @name Vector swizzling
 *
 * @return Vector The composed vector
 *
 * @example
 * local a = createVector(300, 450, 400);
 * 
 * local copy = a.xyz;
 *
 * local a_2d = a.xy; -- { 300, 450 }

 * local b = a.xyx; -- { 300, 450, 300 }
 * local c = a.zxy; -- { 400, 300, 450 }
 * @example
 */

/*
 * Bind the vector to lua_State
 */
int lu5_bind_vector(lua_State *L);

int lu5_vector_mut_mult(lua_State *L);
int lu5_vector_mut_sub(lua_State *L);
int lu5_vector_mut_div(lua_State *L);
int lu5_vector_mut_idiv(lua_State *L);

#endif
