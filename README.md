

<p align="center">
    <img src="./docs/assets/logo.svg"/>
</p>


<h4 align="center">Lua interpreter for Creative Coding</h4>

<p align="center">
	<a href="https://matiasvlevi.github.io/lu5/">Website</a> •
	<a href="https://matiasvlevi.github.io/lu5/latest">Documentation</a> •
	<a href="./CONTRIBUTING.md">Contributing</a>
</p>

<br/>

Provides a similar experience to <a href="https://p5js.org">p5.js</a> in Lua.

<br/>


This sketch draws a circle at position `300, 300`.

```lua
function setup()
    createWindow(600, 600);
end

function draw()
    background(51);

    circle(300, 300, 32);
end
```

### Run

```sh
lu5 file.lua
```

<br/>

# Install

### Windows

Use the installer found on the [project's homepage](https://matiasvlevi.github.io/lu5/) or in the [project's releases](https://github.com/matiasvlevi/lu5/releases).


### Linux

for Arch based systems, use the AUR

```sh
yay -S lu5
```

for other distributions, you might want to [build from source](./BUILD.md).


<br/>

### Examples

* Examples can be found in the [website's documentation](https://matiasvlevi.github.io/lu5/latest)
* Examples in `examples/*.lua`

> Note: Run all the examples with `make examples`

<br/>

### Roadmap

See [lu5's roadmap](./ROADMAP.md)


### Contributions

Contributions to expand the lu5 api are welcomed in any form. 

[Contribution docs](./CONTRIBUTING.md) are provided for contributions with Pull requests.

<br/>

---

License MIT