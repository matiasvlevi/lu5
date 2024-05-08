# Contributing

lu5's goal is to make coding accessible by exposing simple lua bindings for graphics, math, and various common operations.

### Adding functions

The bindings can be found in `./src/bindings/*.h` and they need to be registered in `./src/lu5_bindings.c` to add them to the lua State

Add a documentation comment for each lua binding.

<br/>

### Adding global variables

If you want to add a global variable that will not change (constant), you might want to add it in `./src/lu5_bindings.c` in `lu5_register_constants`.

If you want to update variables (ex: `mouseX`, `mouseY`) add them in `lu5_update_dynamic_variables`, this will update them after every `draw` call

<br/>

## Build

Build lu5 with the static documentation site

```
make docs
```

Static site is generated in `./docs/*`, make sure to verify that your documentation has been added to the built static site.

> If you encounter any problems with your build or runtime, it is encouraged to submit an [issue](https://github.com/matiasvlevi/lu5/issues) and steps to reproduce.

<br/>


Send your PR !