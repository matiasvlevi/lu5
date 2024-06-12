# lu5 TODO

A list of possible functions to implement in lu5, these do not require any major implementation in lu5.

### Cli options

Errors will always terminate the application

```sh
lu5 sketch.lua --onerror exit
```

Most errors will appear as warnings, lu5 will avoid terminating with an error as much as possible

```sh
lu5 sketch.lua --onerror try-warn
```

See `./src/lu5_types.h` for error handling source

---

### Environment

- [ ] `isLooping()`
- [ ] `loop()`
- [ ] `noLoop()`
- [ ] `redraw()`
- [ ] `fullscreen()`
- [x] `windowResized()`

### Geometry

- [ ] `rectMode()`
- [ ] `translate()`
- [ ] `rotate()`

### Typography

- [ ] `textWidth()`
- [ ] `textAscent()`
- [ ] `textDescent()`
- [ ] `textWrap()`
- [x] `textSize()`

### Math

- [x] `random()`
- [x] `randomSeed()`
- [ ] `randomGaussian()`
- [ ] `noise()`
- [ ] `noiseSeed()`
- [ ] `noiseDetail()`

### Conversion

- [ ] `float()`
- [ ] `int()`
- [ ] `str()`
- [ ] `boolean()`
- [ ] `byte()`
- [ ] `char()`
- [ ] `unchar()`
- [ ] `hex()`
- [ ] `unhex()`

### Load formats

- [ ] `loadStrings()` Load text by lines
- [ ] `loadJSON()` 
