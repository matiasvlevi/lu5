

<p align="center">
    <img src="./docs/assets/logo.svg"/>
</p>

<h4 align="center">Lua interpreter for Creative Coding</h4>

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

### Command utilities

Help menu

```sh
lu5 --help
```

Create a boiler plate sketch source file

```sh
lu5 --init file.lua
```
<br>

### Preview

![lu5 preview circle](./docs/assets/lu5_preview_2.png)
![lu5 preview instances](./docs/assets/lu5_preview.png)

<br>

### Live code editor

> NOT IMPLEMENTED

Open in a live environement, provides a GUI text editor for the sketch source

```sh
lu5 --live file.lua
```


