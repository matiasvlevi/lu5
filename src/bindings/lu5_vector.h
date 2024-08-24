#ifndef _LU5_VECTOR_BINDINGS_H_
#define _LU5_VECTOR_BINDINGS_H_

#include <lua.h>
#include <lauxlib.h>

#define LU5_VECTOR "lu5_vector_"

typedef struct {
	double x;
	double y;
} lu5_vector;

/**
 * Create a vector instance
 *
 * @param x The first component of the vector
 * @param y The second component of the vector
 *
 * @return Vector The created vector
 *
 * @example
 * local point = createVector(80, 125);
 *
 * print(point);
 * @example
 */
int createVector(lua_State *L);

/**
 * @name Vector.print
 * Since a `Vector` implements a `print` method, it can be used in the <a href="./io.html#print">`print`</a> function
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
 * local a = createVector(3, 5);
 * local b = createVector(1, 3);
 * 
 * local distance = a:dist(b);
 * print(distance);
 * @example
 */
int lu5_vector_dot(lua_State *L);

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
 * print(a:dot(b));
 * print(Vector.dot(a, b));
 * @example
 */
int lu5_vector_dot(lua_State *L);

/**
 * @name Vector.mult
 *
 * @param a The first vector
 * @param b The second vector
 *
 * @return Vector The added vector
 *
 * @example
 * local a = createVector(3, 5);
 * local b = createVector(1, 3);
 * 
 * print(a:mult(b));
 * print(Vector.mult(a, b));
 * @example
 */
int lu5_vector_mult(lua_State *L);

/**
 * @name Vector.add
 *
 * @param a The first vector
 * @param b The second vector
 *
 * @return Vector The multiplied vector
 *
 * @example
 * local a = createVector(1, 4);
 * local b = createVector(8, 2);
 * 
 * print(a:add(b));
 * print(Vector.add(a, b));
 * @example
 */
int lu5_vector_add(lua_State *L);

/*
 * Bind the vector to lua_State
 */
int lu5_bind_vector(lua_State *L);

#endif
