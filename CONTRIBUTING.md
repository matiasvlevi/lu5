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

<br/>

For web assembly, you can launch a webserver and open `./examples/index.html`

<br/>


## Docs Build 

> You can skip this step if you havent changed the documentation in the header source files 

Run a documentation build with the command below.

```
make docs
```

Static site is generated in `./docs/*`, make sure to verify that your documentation has been added to the built static site.


The documentation is built by lu5, and the site is written in lua using [this jsx-like utility](https://gist.github.com/matiasvlevi/89ec277944034151e6377294c69eec20)


<br/>

## Ready for a PR

Make sure all tests passed and documentation shows up correctly, and send your PR.