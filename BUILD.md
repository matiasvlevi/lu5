# Build

> If you encounter any problems with your build or runtime, it is encouraged to submit an [issue](https://github.com/matiasvlevi/lu5/issues) and steps to reproduce.

<br/>

### GNU/Linux

Clone with submodules, since we're using a lua mirror on linux

```sh
git clone --recurse-submodules https://github.com/matiasvlevi/lu5
cd lu5
make
```

you can then install the executable in `/usr/bin`

```sh
sudo make install
```

<br/>

### Windows

If you are on windows, you can use an [MSYS2](https://www.msys2.org/) environement.

Windows builds can be done from an arch linux environement with mingw64 installed. 

Install dependencies on Windows (MSYS)

```
pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-lua mingw-w64-x86_64-glfw mingw-w64-x86_64-freetype
```

Install dependencies on arch linux

```
yay -S mingw-w64-zlib mingw-w64-gcc mingw-w64-brotli mingw-w64-bzip2 mingw-w64-lua mingw-w64-freetype mingw-w64-winpthreads
```

build

```
make PLATFORM=win
```

build installer (requires wine if on linux)

```
make PLATFORM=win zip
```


<br/>