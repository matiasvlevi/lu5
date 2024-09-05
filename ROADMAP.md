# Roadmap

This roadmap describes major feature sets and future implementations for lu5.

Phases are denoted with `Px` and ordered chronologically but they could also be implemented in parralel.

<br/>

### `P1` - Basic 2D 
`Mostly complete` from `v0.0.1` to `v0.0.6`

* 2D shapes
* Math, Vectors
* Text rendering

> Some of the 2D shapes `triangle`, `quad` are missing implementation for `stroke`.

<br/>

### `P2` - Basic 3D
`Current` from `v0.1.6` to `v0.x.x`

* 3D shapes
* 3D models

<br/>

### `P3` - Audio I/O

`ahead`

* Audio In
* FFT Analyzer
* Audio Out

<br/>

### `P4` - Image & Video I/O

`ahead`

* Get webcam feed, write it to texture.
* Generate screenshots, GIFs or sequences of images.

type `lu5_image` can be used in this phase

<br/>

### `P5` - GLSL Shaders

`ahead`

Allow building and linking with GLSL shaders.

Similar to [p5js shaders](https://p5js.org/reference/p5/shader/) but with opengl and not webgl