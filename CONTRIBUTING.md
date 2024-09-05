# Contributing

lu5's goal is to make coding accessible by exposing simple lua bindings for graphics, math, and various common operations.

<br/>

### Adding functions

The bindings can be found in `./src/bindings/*.h` and they need to be registered in `./src/lu5_bindings.c` to add them to the lua State

Add a documentation comment for each lua binding.

<br/>

## Build

Build the source, guide [here](./BUILD.md)

<br/>


## Tests

You can test with unit tests, which are written in `tests/*.lua`

```
make tests
```

you can also test with all the examples in the repository

```
make examples
```

and the larger multi-file projects:

```
make projects
```

<br/>


## Docs Build 

Build lu5 with the static documentation site

```
make docs
```

Static site is generated in `./docs/*`, make sure to verify that your documentation has been added to the built static site.



<br/>

## Ready for a PR

Make sure all tests passed and documentation shows up correctly, and send your PR.