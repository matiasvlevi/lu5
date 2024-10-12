#ifndef _LU5_DECORATORS_H_
#define _LU5_DECORATORS_H_

#ifndef LU5_WASM
#define WASM_IMPORT(module, name)
#define WASM_EXPORT(name) 
#else
#define WASM_IMPORT(module, name) __attribute__((import_module(module), import_name(name))) 
#define WASM_EXPORT(name)         __attribute__((export_name(name))) 
#endif

#endif