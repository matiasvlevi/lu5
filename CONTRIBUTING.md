# Contributing

Add all the exposed lua bindings in `./src/bindings/*.h`

Include your bindings in `./src/lu5_bindings.c` and register them to the lua state using `LUA_ADD_FUNCTION` macro

Add a documentation comment for each lua binding.

Build the application and the static documentation site.

```
make docs
```

Send a PR!