# Build

> If you encounter any problems with your build or runtime, it is encouraged to submit an [issue](https://github.com/matiasvlevi/lu5/issues) and steps to reproduce.

<br/>

Clone the repository with submodules

```sh
git clone --recurse-submodules https://github.com/matiasvlevi/lu5
```

<br/>

## GNU/Linux

#### Dependencies

* `glu`, `glew`, `glfw`, `freetype2`


```
make
```


<br/>

## wasm32-wasi

#### Dependencies

* `wasi-sdk-24` See how to build [here](https://github.com/WebAssembly/wasi-sdk)

```
make PLATFORM=wasm
```


<br/>

## Windows

Windows builds are done from an arch based environement with mingw64 installed.

> Windows builds are subject to change since I'm not satisfied with the current handling of libraries with the AUR. 

### Cross compile to Windows from an arch-based distribution

#### Dependencies

* `wine` (multilib)
* `mingw-w64-zlib` (AUR)
* `mingw-w64-brotli` (AUR)
* `mingw-w64-bzip2` (AUR)
* `mingw-w64-glfw` (AUR)
* `mingw-w64-freetype` (AUR)
* `mingw-w64-lua` (AUR)

> You'll need to install [NSIS](https://nsis.sourceforge.io/Download) to build the lu5 installer.
> On a linux system you can use `wine` to run the NSIS setup, and install it in `~/.wine/drive_c/Program Files (x86)/`.



Build the executable

```
make PLATFORM=win
```

Build the installer

```
make PLATFORM=win installer
```

<br/>

### Compile for Windows on Windows using MSYS

If you are on windows, you can use an [MSYS2](https://www.msys2.org/) environement.


Run the following command in the MSYS command line

```
pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-lua mingw-w64-x86_64-glfw mingw-w64-x86_64-freetype
```

build

```
make PLATFORM=win
```

<br/>