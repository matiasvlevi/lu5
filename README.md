# lu5

Raylib wrappers for a similar feel to p5.js

This sketch draws a circle at position `300, 300`.

```lua
function setup()
    createWindow(600, 600);
end

function draw()
    background(51);

    circle(300, 300, 16);
end
```



## Build

Build with `make`

```sh
make
```

You can then install it on linux with

```sh
sudo make install
```



## Running Lua Sketches

Specify the path of the file you want to execute

```sh
lu5 file.lua
```

--- 

<br/>

### Projected command utilities

> NOT IMPLEMENTED YET

Help menu

```sh
lu5 --help
```

Create a boiler plate sketch source file

```sh
lu5 --init file.lua
```

Open in a live environement, provides a GUI text editor for the sketch source

```sh
lu5 --live file.lua
```


