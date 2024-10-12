# lu5 Website

The documentation is built by lu5, and the site is written in lua using [this jsx-like utility](https://gist.github.com/matiasvlevi/89ec277944034151e6377294c69eec20)

# Build

lu5 is used to build the website, you could build the documentation like so:

```sh
cd ..
lu5 site/tasks/build_docs.lua
```

> If you are contributing, it is recommended to use `make docs` from the root of the project instead. This helps prevent versions mismatch between the interpreter and the docs site.
