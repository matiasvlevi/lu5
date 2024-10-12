/******/ (() => { // webpackBootstrap
/******/ 	"use strict";
/******/ 	// The require scope
/******/ 	var __webpack_require__ = {};
/******/ 	
/************************************************************************/
/******/ 	/* webpack/runtime/define property getters */
/******/ 	(() => {
/******/ 		// define getter functions for harmony exports
/******/ 		__webpack_require__.d = (exports, definition) => {
/******/ 			for(var key in definition) {
/******/ 				if(__webpack_require__.o(definition, key) && !__webpack_require__.o(exports, key)) {
/******/ 					Object.defineProperty(exports, key, { enumerable: true, get: definition[key] });
/******/ 				}
/******/ 			}
/******/ 		};
/******/ 	})();
/******/ 	
/******/ 	/* webpack/runtime/hasOwnProperty shorthand */
/******/ 	(() => {
/******/ 		__webpack_require__.o = (obj, prop) => (Object.prototype.hasOwnProperty.call(obj, prop))
/******/ 	})();
/******/ 	
/******/ 	/* webpack/runtime/make namespace object */
/******/ 	(() => {
/******/ 		// define __esModule on exports
/******/ 		__webpack_require__.r = (exports) => {
/******/ 			if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 				Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 			}
/******/ 			Object.defineProperty(exports, '__esModule', { value: true });
/******/ 		};
/******/ 	})();
/******/ 	
/************************************************************************/

// NAMESPACE OBJECT: ./src/wasi.ts
var wasi_namespaceObject = {};
__webpack_require__.r(wasi_namespaceObject);
__webpack_require__.d(wasi_namespaceObject, {
  clock_res_get: () => (clock_res_get),
  clock_time_get: () => (clock_time_get),
  fd_write: () => (fd_write)
});

// NAMESPACE OBJECT: ./src/platform/index.ts
var platform_namespaceObject = {};
__webpack_require__.r(platform_namespaceObject);
__webpack_require__.d(platform_namespaceObject, {
  lu5_GetKeyName: () => (lu5_GetKeyName),
  lu5_background: () => (lu5_background),
  lu5_createWindow: () => (lu5_createWindow),
  lu5_getCursorPos: () => (lu5_getCursorPos),
  lu5_glBegin: () => (lu5_glBegin),
  lu5_glEnd: () => (lu5_glEnd),
  lu5_glVertex2: () => (lu5_glVertex2),
  lu5_load_and_add_font: () => (lu5_load_and_add_font),
  lu5_load_image: () => (lu5_load_image),
  lu5_loop: () => (lu5_loop),
  lu5_noLoop: () => (lu5_noLoop),
  lu5_open_file: () => (lu5_open_file),
  lu5_read_file: () => (lu5_read_file),
  lu5_render_arc_fill: () => (lu5_render_arc_fill),
  lu5_render_arc_stroke: () => (lu5_render_arc_stroke),
  lu5_render_ellipse: () => (lu5_render_ellipse),
  lu5_render_ellipse_w_stroke: () => (lu5_render_ellipse_w_stroke),
  lu5_render_image: () => (lu5_render_image),
  lu5_render_line: () => (lu5_render_line),
  lu5_render_quad: () => (lu5_render_quad),
  lu5_render_quad_fill: () => (lu5_render_quad_fill),
  lu5_render_quad_stroke: () => (lu5_render_quad_stroke),
  lu5_render_text: () => (lu5_render_text),
  lu5_render_triangle_fill: () => (lu5_render_triangle_fill),
  lu5_set_font: () => (lu5_set_font),
  lu5_time_seed: () => (lu5_time_seed),
  lu5_write_file: () => (lu5_write_file)
});

;// ./src/unimplemented.ts
const lu5_bindings_unimplemented = [
    // Image
    'lu5_image_crop',
    // 'lu5_load_image',
    // 'lu5_render_image',
    // 3D
    'lu5_render_debug',
    'lu5_render_box_faces',
    'lu5_render_box_edges',
    'lu5_render_cylinder_faces',
    'lu5_render_cylinder_edges',
    'lu5_render_torus_faces',
    'lu5_render_torus_edges',
    'lu5_render_plane_faces',
    'lu5_render_plane_edges',
    'lu5_render_ellipsoid_faces',
    'lu5_render_ellipsoid_edges',
    // GLFW
    'lu5_swapBuffers',
    'lu5_pollEvents',
    'lu5_setWindowShouldClose',
    'lu5_PushMatrix',
    'lu5_PopMatrix',
    // Other
    'lu5_glVertex2',
    'lu5_init_freetype',
    'lu5_close_fonts',
    'lu5_load_default_font',
];
const wasi_snapshot_preview1_unimplemented = [
    'random_get',
    'args_get',
    'args_sizes_get',
    'environ_get',
    'environ_sizes_get',
    'fd_close',
    'fd_prestat_get',
    'fd_prestat_dir_name',
    'fd_read',
    'fd_seek',
    'proc_exit',
    'path_open',
    'path_unlink_file',
    'path_filestat_get',
    'path_filestat_set_times',
    'path_symlink',
    'path_link',
    'path_remove_directory',
    'poll_oneoff',
    'proc_raise',
    'sched_yield',
    'sock_send',
    'sock_recv',
    'sock_shutdown',
    'sock_close',
    'fd_fdstat_get',
    'fd_fdstat_set_flags',
    'fd_sync',
    'fd_allocate',
    'fd_advise',
    'path_rename',
    'path_open',
    'fd_filestat_get',
    'fd_filestat_set_times',
    'fd_filestat_set_size',
    'fd_filestat_set_times',
    'fd_renumber',
    'fd_datasync',
    'fd_pread',
    'fd_pwrite',
    'fd_readdir',
    'fd_fdstat_set_rights',
    'fd_tell',
    'path_create_directory',
    'path_readlink',
    'path_filestat_set_size',
    'sock_accept',
    'sock_bind',
    'sock_connect',
    'sock_listen',
    'sock_recvmsg',
    'sock_sendmsg',
    'sock_create',
    'sock_shutdown',
    'sock_recv',
    'sock_send',
];


;// ./src/wasi.ts
let stderr_buf = '';
function fd_write(fd, iovecs, iovec_len, nwritten) {
    if (!this.memory)
        return;
    this.refreshMemory();
    const memory = this.memory.buffer;
    let totalBytesWritten = 0;
    const buffers = [];
    for (let i = 0; i < iovec_len; i++) {
        const iovec_ptr = iovecs + (i * 8);
        if (iovec_ptr < 0 || (iovec_ptr + 8) > memory.byteLength) {
            this.error(`fd_write: iovec_ptr (${iovec_ptr}) out of bounds at iovec index ${i}`);
            continue;
        }
        const ptr = this.view.getUint32(iovec_ptr, true);
        const size = this.view.getUint32(iovec_ptr + 4, true);
        if (ptr < 0 || (ptr + size) > memory.byteLength) {
            this.error(`fd_write: Data pointer (${ptr}) out of bounds or invalid size at iovec index ${i}`);
            continue;
        }
        if (size <= 0)
            continue;
        // Extract buffer data
        const buffer = new Uint8Array(this.memory.buffer, ptr, size);
        buffers.push(buffer);
        totalBytesWritten += size;
    }
    // Concatenate all buffers
    let combinedBuffer = new Uint8Array(totalBytesWritten);
    let offset = 0;
    buffers.forEach(buffer => {
        combinedBuffer.set(buffer, offset);
        offset += buffer.length;
    });
    let str = new TextDecoder().decode(combinedBuffer);
    // Log in console
    switch (fd) {
        case 1:
            this.log(str);
            break;
        case 2: {
            stderr_buf += str;
            if (str.includes('\n')) {
                this.error(stderr_buf);
                stderr_buf = '';
            }
            break;
        }
        default:
            this.error('fd_write: unknown file descriptor');
            return 1;
    }
    // Write the total written size at the specified location
    let writtenBytes = totalBytesWritten;
    if (this.view)
        this.view.setUint32(nwritten, writtenBytes, true);
    return 0;
}
function clock_res_get(_clockId, resolution) {
    if (this.view)
        this.view.setBigUint64(resolution, 1000n, true);
    return 0;
}
function clock_time_get(_clockId, _precision, time) {
    if (this.view)
        this.view.setBigUint64(time, BigInt(Date.now()) * 1000000n, true);
    return 0;
}

;// ./src/memory.ts
function get_cstr(mem, ptr, len) {
    if (!mem)
        return '';
    if (len !== undefined) {
        let str_buffer = new Uint8Array(mem.buffer, ptr, len);
        return new TextDecoder().decode(str_buffer);
    }
    // Null terminated
    let str_buffer = new Uint8Array(mem.buffer, ptr, mem.buffer.byteLength - ptr);
    return new TextDecoder().decode(str_buffer.subarray(0, str_buffer.indexOf(0)));
}
function write_cstr(mem, ptr, str_value) {
    if (!mem)
        return;
    let encoder = new TextEncoder();
    let encodedString = encoder.encode(str_value);
    // Add null terminator
    let nullTerminatedString = new Uint8Array(encodedString.length + 1);
    nullTerminatedString.set(encodedString);
    nullTerminatedString[encodedString.length] = 0; // null terminator
    let i8 = new Uint8Array(mem.buffer);
    // Check for buffer overflow
    if ((ptr + nullTerminatedString.length) >= mem.buffer.byteLength) {
        this.error('write_cstr Memory overflow');
        return;
    }
    i8.set(nullTerminatedString, ptr);
}

;// ./src/platform/geometry/2D.ts

function lu5_render_quad(x1, y1, x2, y2, x3, y3, x4, y4, strokeWeight, fill, stroke) {
    if (!this.ctx)
        return;
    this.ctx.fillStyle = this.colorToHex(fill);
    this.ctx.strokeStyle = this.colorToHex(stroke);
    this.ctx.lineWidth = strokeWeight;
    this.ctx.beginPath();
    this.ctx.moveTo(x1, y1);
    this.ctx.lineTo(x2, y2);
    this.ctx.lineTo(x3, y3);
    this.ctx.lineTo(x4, y4);
    this.ctx.closePath();
    this.ctx.stroke();
    this.ctx.fill();
}
function lu5_render_line(x1, y1, x2, y2, strokeWeight, stroke) {
    if (!this.ctx)
        return;
    this.ctx.lineWidth = strokeWeight * 2;
    this.ctx.lineCap = 'round';
    this.ctx.strokeStyle = this.colorToHex(stroke);
    this.ctx.beginPath();
    this.ctx.moveTo(x1, y1);
    this.ctx.lineTo(x2, y2);
    this.ctx.stroke();
}
function lu5_render_ellipse_w_stroke(x, y, h, w, strokeWeight, fill, stroke, _segments) {
    if (!this.ctx)
        return;
    this.ctx.fillStyle = this.colorToHex(fill);
    this.ctx.strokeStyle = this.colorToHex(stroke);
    this.ctx.beginPath();
    this.ctx.ellipse(x, y, w, h, 0, 0, 2 * Math.PI);
    this.ctx.lineWidth = strokeWeight;
    this.ctx.stroke();
    this.ctx.fill();
}
function lu5_render_ellipse(x, y, w, h, color, _segments) {
    if (!this.ctx)
        return;
    this.ctx.fillStyle = this.colorToHex(color);
    this.ctx.beginPath();
    this.ctx.ellipse(x, y, w, h, 0, 0, 2 * Math.PI);
    this.ctx.fill();
}
function lu5_render_arc_fill(x, y, rx, ry, start_angle, end_angle, _segments, color) {
    if (!this.ctx)
        return;
    this.ctx.fillStyle = this.colorToHex(color);
    this.ctx.beginPath();
    this.ctx.ellipse(x, y, rx, ry, 0, start_angle, end_angle);
    this.ctx.lineTo(x, y);
    this.ctx.closePath();
    this.ctx.fill();
}
function lu5_render_arc_stroke(x, y, w, h, strokeWeight, start_angle, end_angle, _segments, color) {
    if (!this.ctx)
        return;
    this.ctx.strokeStyle = this.colorToHex(color);
    this.ctx.beginPath();
    this.ctx.ellipse(x, y, w, h, 0, start_angle, end_angle);
    this.ctx.lineWidth = strokeWeight;
    this.ctx.stroke();
}
function lu5_render_quad_fill(x1, y1, x2, y2, x3, y3, x4, y4, color) {
    if (!this.ctx)
        return;
    this.ctx.fillStyle = this.colorToHex(color);
    this.ctx.beginPath();
    this.ctx.moveTo(x1, y1);
    this.ctx.lineTo(x2, y2);
    this.ctx.lineTo(x3, y3);
    this.ctx.lineTo(x4, y4);
    this.ctx.closePath();
    this.ctx.fill();
}
function lu5_render_quad_stroke(x1, y1, x2, y2, x3, y3, x4, y4, strokeWeight, color) {
    if (!this.ctx)
        return;
    this.ctx.strokeStyle = this.colorToHex(color);
    const px = Math.min(x1, x2, x3, x4);
    const py = Math.min(y1, y2, y3, y4);
    const w = Math.max(x1, x2, x3, x4) - px;
    const h = Math.max(y1, y2, y3, y4) - py;
    this.ctx.lineWidth = strokeWeight;
    this.ctx.strokeRect(px, py, w, h);
}
function lu5_render_text(text_ptr, x, y, fontSize, textAlign, _font, color) {
    if (!this.ctx)
        return;
    const text = get_cstr(this.memory, text_ptr);
    switch (textAlign) {
        case 1:
            this.ctx.textAlign = "center";
            break;
        case 2:
            this.ctx.textAlign = "right";
            break;
        case 3:
            this.ctx.textAlign = "left";
            break;
    }
    ;
    this.ctx.font = `${fontSize}px ${this.ctx.font.split(' ')[1]}`;
    this.ctx.fillStyle = this.colorToHex(color);
    this.ctx.fillText(text, x, y - 4);
}
function lu5_render_triangle_fill(x1, y1, x2, y2, x3, y3, color) {
    if (!this.ctx)
        return;
    this.ctx.beginPath();
    this.ctx.fillStyle = this.colorToHex(color);
    this.ctx.moveTo(x1, y1);
    this.ctx.lineTo(x2, y2);
    this.ctx.lineTo(x3, y3);
    this.ctx.closePath();
    this.ctx.fill();
    this.ctx.stroke();
    return 0;
}
/**
 * custom shapes
 */
let is_first_vertex = true;
function lu5_glBegin(_mode, color) {
    if (!this.ctx)
        return;
    this.ctx.fillStyle = this.colorToHex(color);
    this.ctx.beginPath();
}
function lu5_glVertex2(x, y) {
    if (!this.ctx)
        return;
    if (is_first_vertex) {
        this.ctx.moveTo(x, y);
        is_first_vertex = false;
    }
    else {
        this.ctx.lineTo(x, y);
    }
}
function lu5_glEnd() {
    if (!this.ctx)
        return;
    this.ctx.closePath();
    is_first_vertex = true;
    this.ctx.fill();
    this.ctx.stroke();
}

;// ./src/platform/image.ts

let image_images = [];
function lu5_load_image(_L, path_str) {
    const path = get_cstr(this.memory, path_str);
    // Add image
    const img = new Image();
    img.src = path;
    image_images.push(img);
    // Return an image struct, with an image index as texture ptr
    this.refreshMemory();
    const lu5_image = this.calls.malloc(4 * 3);
    this.view.setUint32(lu5_image, image_images.length - 1); // texture id
    this.view.setInt32(lu5_image + 1, img.width);
    this.view.setInt32(lu5_image + 2, img.height);
    return lu5_image;
}
function lu5_render_image(_L, image_ptr, x, y, w, h, color) {
    // Get the texture ptr
    const image_index = this.view.getUint32(image_ptr);
    // Ignore if still unloaded
    const img = image_images[image_index];
    if (!img.complete)
        return;
    this.ctx.globalAlpha = (this.colorToRGBA(color)[3]) / 255;
    this.ctx.drawImage(img, x, y, w, h);
    this.ctx.globalAlpha = 1;
}

;// ./src/platform/font.ts

function lu5_load_and_add_font(_lu5, _font_name_ptr) {
    this.warn(`Calling \x1b[90m'loadFont'\x1b[0m on the Web is ignored. Instead, use textFont directly.`);
    return 1;
}
function lu5_set_font(fontname_ptr) {
    const name = get_cstr(this.memory, fontname_ptr);
    this.ctx.font = `${this.ctx.font.split(' ')[0]} ${name}`;
    return 0;
}

;// ./src/platform/fs.ts
async function lu5_open_file(file_path_ptr, mode_str_ptr) {
    this.warn('File I/O is not supported in lu5-wasm yet');
    return 0;
}
async function lu5_read_file(file_path_ptr, file_size_ptr, err_ptr) {
    this.warn('File I/O is not supported in lu5-wasm yet');
    return 0;
}
function lu5_write_file() {
    this.warn('File I/O is not supported in lu5-wasm yet');
    return 0;
}

;// ./src/common/dom.ts
function get_or_create_by_id(tag, id, host = document.body) {
    let elem = document.getElementById(id);
    if (elem === null) {
        elem = document.createElement(tag);
        elem.setAttribute('id', id);
        if (host)
            host.appendChild(elem);
        else
            window.onload = () => host.appendChild(elem);
    }
    return elem;
}

;// ./src/platform/window.ts

function lu5_createWindow(_L, w, h, _title_ptr, mode) {
    if (!this.wasm)
        return 0;
    this.depth_mode = mode;
    if (mode == 1) {
        this.warn('3D Mode is not yet supported in lu5-wasm.');
        this.loop = false;
        return 0;
    }
    const canvas = get_or_create_by_id('canvas', this.canvas_id);
    canvas.style.display = 'inline';
    // Set dimensions
    canvas.width = w;
    canvas.height = h;
    // Set rendering context
    switch (mode) {
        case 0:
            this.ctx = canvas.getContext('2d');
            break;
        case 1:
            this.gl = canvas.getContext('webgl');
            break;
        default: break;
    }
    // Bind Events
    this.events['handleWheel'] = this.handleWheel.bind(this);
    document.addEventListener('wheel', this.events['handleWheel']);
    this.events['handleKeydown'] = this.handleKeydown.bind(this);
    document.addEventListener('keydown', this.events['handleKeydown']);
    this.events['handleKeyup'] = this.handleKeyup.bind(this);
    document.addEventListener('keyup', this.events['handleKeyup']);
    canvas.addEventListener('mousemove', this.handleMousemove.bind(this));
    canvas.addEventListener('mousedown', this.handleMousedown.bind(this));
    canvas.addEventListener('mouseup', this.handleMouseup.bind(this));
    return 0;
}
function lu5_background(color) {
    switch (this.depth_mode) {
        case 0:
            if (!this.ctx)
                break;
            this.ctx.fillStyle = this.colorToHex(color);
            this.ctx.fillRect(0, 0, this.ctx.canvas.width, this.ctx.canvas.height);
            this.ctx.fill();
            break;
        case 1:
            if (!this.gl)
                break;
            this.gl.clearColor(0.0, 0.0, 0.0, 1.0);
            this.gl.clear(this.gl.COLOR_BUFFER_BIT);
            break;
        default:
            break;
    }
}
function lu5_getCursorPos(_window, mouseX_ptr, mouseY_ptr) {
    this.refreshMemory();
    if (this.view) {
        this.view.setFloat64(mouseX_ptr, this.mouseX, true);
        this.view.setFloat64(mouseY_ptr, this.mouseY, true);
    }
    return 0;
}
function lu5_noLoop() {
    this.loop = false;
}
function lu5_loop() {
    if (!this.loop) {
        requestAnimationFrame(this.frame);
    }
    this.loop = true;
}
function lu5_time_seed() {
    return Math.floor(Math.random() * 1000000);
}

;// ./src/platform/index.ts






// create a map
function lu5_GetKeyName(key, scancode) {
    if (this.keyname_ptr == null) {
        this.calls.free(this.keyname_ptr);
    }
    let name = null;
    // check if alphanumeric and return the character
    if (key >= 65 && key <= 90) {
        name = String.fromCharCode(key);
    }
    // Numbers
    if (key >= 48 && key <= 57) {
        name = String.fromCharCode(key);
    }
    // Numpad
    if (key >= 320 && key <= 329) {
        name = 'Numpad ' + (key - 320);
    }
    // Function keys
    if (key >= 290 && key <= 299) {
        name = 'F' + (key - 290 + 1);
    }
    if (name === null) {
        this.keyname_ptr = null;
        return this.keyname_ptr;
    }
    ;
    this.keyname_ptr = this.calls.malloc(name.length);
    write_cstr(this.memory, this.keyname_ptr, name);
    return this.keyname_ptr;
}

;// ./src/color.ts
function colorToHex(ptr) {
    this.refreshMemory();
    if (!this.view)
        return '#00000000';
    const alpha = this.view.getUint8(ptr);
    if (alpha == 0)
        return '#00000000';
    const color = '#' +
        this.view.getUint8(ptr + 3).toString(16).padStart(2, '0') +
        this.view.getUint8(ptr + 2).toString(16).padStart(2, '0') +
        this.view.getUint8(ptr + 1).toString(16).padStart(2, '0') +
        alpha.toString(16).padStart(2, '0');
    return color;
}
function colorToRGBA(ptr) {
    this.refreshMemory();
    if (!this.view)
        return [0, 0, 0, 0];
    const alpha = this.view.getUint8(ptr);
    if (alpha == 0)
        return [0, 0, 0, 0];
    return [
        this.view.getUint8(ptr + 3),
        this.view.getUint8(ptr + 2),
        this.view.getUint8(ptr + 1),
        alpha
    ];
}

;// ./src/glfw.ts
const RELEASE = 0;
const PRESS = 1;
const REPEAT = 2;
const MOD_SUPER = 0x0008;
const MOD_CONTROL = 0x0002;
/**
 * Get the GLFW mod bits from a KeyboardEvent
 *
 * @param e The event
 * @returns the GLFW mod bits
 */
const fromKeyboardEvent = (e) => (+e.metaKey << MOD_SUPER) |
    (+e.ctrlKey << MOD_CONTROL);
/**
 * KeyboardEvent keyCode to GLFW Key Map
 */
const fromKeyCode = {
    0: 0, // Unknown
    8: 259, // Backspace
    9: 258, // Tab
    13: 257, // Enter
    16: 340, // Shift (Left Shift)
    17: 341, // Ctrl (Left Ctrl)
    18: 342, // Alt (Left Alt)
    19: 284, // Pause
    20: 280, // Caps Lock
    27: 256, // Escape
    32: 32, // Space
    33: 266, // Page Up
    34: 267, // Page Down
    35: 269, // End
    36: 268, // Home
    37: 263, // Left Arrow
    38: 265, // Up Arrow
    39: 262, // Right Arrow
    40: 264, // Down Arrow
    45: 260, // Insert
    46: 261, // Delete
    48: 48, // 0
    49: 49, // 1
    50: 50, // 2
    51: 51, // 3
    52: 52, // 4
    53: 53, // 5
    54: 54, // 6
    55: 55, // 7
    56: 56, // 8
    57: 57, // 9
    65: 65, // A
    66: 66, // B
    67: 67, // C
    68: 68, // D
    69: 69, // E
    70: 70, // F
    71: 71, // G
    72: 72, // H
    73: 73, // I
    74: 74, // J
    75: 75, // K
    76: 76, // L
    77: 77, // M
    78: 78, // N
    79: 79, // O
    80: 80, // P
    81: 81, // Q
    82: 82, // R
    83: 83, // S
    84: 84, // T
    85: 85, // U
    86: 86, // V
    87: 87, // W
    88: 88, // X
    89: 89, // Y
    90: 90, // Z
    91: 343, // Left Super (Windows/Command key)
    92: 344, // Right Super (Windows/Command key)
    93: 348, // Menu
    96: 320, // Numpad 0
    97: 321, // Numpad 1
    98: 322, // Numpad 2
    99: 323, // Numpad 3
    100: 324, // Numpad 4
    101: 325, // Numpad 5
    102: 326, // Numpad 6
    103: 327, // Numpad 7
    104: 328, // Numpad 8
    105: 329, // Numpad 9
    106: 332, // Numpad Multiply
    107: 334, // Numpad Add
    109: 333, // Numpad Subtract
    110: 330, // Numpad Decimal
    111: 331, // Numpad Divide
    112: 290, // F1
    113: 291, // F2
    114: 292, // F3
    115: 293, // F4
    116: 294, // F5
    117: 295, // F6
    118: 296, // F7
    119: 297, // F8
    120: 298, // F9
    121: 299, // F10
    122: 300, // F11
    123: 301, // F12
    144: 282, // Num Lock
    145: 281, // Scroll Lock
    186: 59, // Semicolon (;)
    187: 61, // Equal (=)
    188: 44, // Comma (,)
    189: 45, // Minus (-)
    190: 46, // Period (.)
    191: 47, // Slash (/)
    192: 96, // Backtick (`)
    219: 91, // Left Bracket ([)
    220: 92, // Backslash (\)
    221: 93, // Right Bracket (])
    222: 39 // Apostrophe (')
};

;// ./src/lu5.ts
var __classPrivateFieldGet = (undefined && undefined.__classPrivateFieldGet) || function (receiver, state, kind, f) {
    if (kind === "a" && !f) throw new TypeError("Private accessor was defined without a getter");
    if (typeof state === "function" ? receiver !== state || !f : !state.has(receiver)) throw new TypeError("Cannot read private member from an object whose class did not declare it");
    return kind === "m" ? f : kind === "a" ? f.call(receiver) : f ? f.value : state.get(receiver);
};
var _LU5_instances, _LU5_run;






class LU5 {
    constructor() {
        _LU5_instances.add(this);
        this.colorToHex = colorToHex.bind(this);
        this.colorToRGBA = colorToRGBA.bind(this);
        this.wasm;
        this.canvas_id = 'lu5-canvas';
        this.fd = [];
        this.l5 = null;
        this.ctx = null;
        this.gl = null;
        this.memory = null;
        this.view = null;
        this.lastTime = 0;
        this.mouseX = 0;
        this.mouseY = 0;
        this.loop = true;
        this.frame = undefined;
        this.debug_tag = undefined;
        this.depth_mode = 0;
        this.events = {};
    }
    write(fd, method, msg) {
        const handlers = this.fd[fd];
        if (!handlers)
            return;
        handlers.forEach((c) => {
            if (c[method])
                c[method](msg);
        });
    }
    error(msg) {
        // Replace prefix
        msg = msg.replace(/\[string ".*?"\]:(\d+):/g, (_, linenumber) => `line ${linenumber}: `);
        // Add error prefix if not found
        if (!msg.includes(LU5.err_prefix))
            msg = `${LU5.err_prefix} ${msg}`;
        // Write error
        this.write(2, 'error', msg);
    }
    log(msg) { this.write(1, 'log', msg); }
    warn(msg) { this.write(1, 'warn', msg); }
    clear() {
        // Clear all attached fds
        this.fd.forEach(fd => (fd) ? fd.forEach(c => c.clear()) : 0);
        return this;
    }
    handle_exception(e) {
        if (e instanceof WebAssembly.RuntimeError) {
            if (!e.message.includes('unreachable')) {
                this.log(e.message);
                this.log(e.stack);
            }
            else {
                // Unrechable, currently reachable since setjmp/longjmp 
                // do not work in wasi-libc
            }
        }
        else if (e instanceof WebAssembly.Exception) {
            if (e.is(this.debug_tag)) {
                this.error(e.getArg(this.debug_tag, 0));
            }
            else {
                this.error('Unknown exception');
            }
        }
        else {
            this.error(e.toString());
        }
        // Stop script
        this.loop = false;
        // Clear memory and remove event listeners
        if (this.l5) {
            this.calls._lu5_close(this.l5);
            document.removeEventListener('wheel', this.events.handleWheel);
            document.removeEventListener('keydown', this.events.handleKeydown);
            document.removeEventListener('keyup', this.events.handleKeyup);
            // Remove all canvas event listeners
            if (this.ctx && this.ctx.canvas.parentNode) {
                let new_element = this.ctx.canvas.cloneNode(true);
                this.ctx.canvas.parentNode.replaceChild(new_element, this.ctx.canvas);
            }
        }
    }
    static wrap_calls(vm) {
        const methods = {};
        for (const [name, method] of Object.entries(vm.wasm.exports)) {
            methods[name] = function () {
                try {
                    return method(...arguments);
                }
                catch (e) {
                    vm.handle_exception(e);
                }
            };
        }
        return methods;
    }
    refreshMemory() {
        if (this.memory)
            if (this.view === null || this.view.buffer.byteLength === 0) {
                this.view = new DataView(this.memory.buffer);
            }
    }
    static makeEnv(bind, symbols, implemented) {
        const env = {};
        const syms = [...new Set([...symbols, ...Object.keys(implemented)])];
        for (let sym of syms) {
            env[sym] = (implemented[sym] == undefined) ? (() => 0) : implemented[sym].bind(bind);
        }
        return env;
    }
    static async compile(lu5_wasm_path) {
        const response = await fetch(lu5_wasm_path);
        const buffer = await response.arrayBuffer();
        return await WebAssembly.compile(buffer);
    }
    static async instantiate(module) {
        const lu5 = new LU5();
        lu5.debug_tag = new WebAssembly.Tag({ parameters: ["i32"] });
        const tagToIndexMap = new Map();
        tagToIndexMap.set(lu5.debug_tag, 0);
        lu5.wasm = await WebAssembly.instantiate(module, {
            env: {
                ...LU5.makeEnv(lu5, lu5_bindings_unimplemented, platform_namespaceObject),
                ...LU5.env
            },
            wasi_snapshot_preview1: LU5.makeEnv(lu5, wasi_snapshot_preview1_unimplemented, wasi_namespaceObject)
        });
        lu5.memory = lu5.wasm.exports.memory;
        lu5.calls = LU5.wrap_calls(lu5);
        return lu5;
    }
    async attach(fd, console) {
        if (typeof fd === 'string') {
            switch (fd) {
                case 'stdout':
                    fd = 1;
                    break;
                case 'stderr':
                    fd = 2;
                    break;
                default:
                    fd = 3;
                    break;
            }
        }
        if (this.fd[fd] === undefined)
            this.fd[fd] = [];
        this.fd[fd].push(console);
        return this;
    }
    async setCanvas(id) {
        this.canvas_id = id || undefined;
        return this;
    }
    handleWheel(e) {
        if (!this.wasm)
            return;
        this.calls._lu5_mouse_scroll_callback(null, (e.deltaX > 0) ? 1 : -1, (e.deltaY > 0) ? 1 : -1);
    }
    ;
    handleKeydown(e) {
        if (!this.wasm)
            return;
        this.calls._lu5_key_callback(null, (fromKeyCode[e.keyCode] || 0), e.key, // Use scan code to map with Name later in glfwGetKetName
        e.repeat ? REPEAT : PRESS, fromKeyboardEvent(e));
    }
    handleKeyup(e) {
        if (!this.wasm)
            return;
        this.calls._lu5_key_callback(null, (fromKeyCode[e.keyCode] || 0), e.key, // Use scan code to map with Name later in glfwGetKetName
        RELEASE, fromKeyboardEvent(e));
    }
    handleMousemove(e) {
        if (!this.wasm)
            return;
        const rect = this.ctx.canvas.getBoundingClientRect();
        this.mouseX = Math.round(e.clientX - rect.left);
        this.mouseY = Math.round(e.clientY - rect.top);
        this.calls._lu5_mouse_cursor_callback(null, this.mouseX, this.mouseY);
    }
    handleMousedown(e) {
        if (!this.wasm)
            return;
        this.calls._lu5_mouse_button_callback(null, e.button, 1, 0);
    }
    handleMouseup(e) {
        if (!this.wasm)
            return;
        this.calls._lu5_mouse_button_callback(null, e.button, 0, 0);
    }
    execute(source) {
        return new Promise(res => {
            __classPrivateFieldGet(this, _LU5_instances, "m", _LU5_run).call(this, source, () => res(this));
        });
    }
    async reset() {
        this.loop = false;
        await new Promise(r => setTimeout(() => {
            if (!this.wasm) {
                r(undefined);
                return;
            }
            if (this.l5) {
                this.calls._lu5_close(this.l5);
            }
            if (this.ctx && !this.canvas_id) {
                this.ctx.canvas.remove();
            }
            else if (this.ctx) {
                this.ctx.canvas.style.display = 'none';
            }
            this.fd = [];
            delete this.wasm;
            r(undefined);
        }));
        return this;
    }
}
_LU5_instances = new WeakSet(), _LU5_run = function _LU5_run(source, done = () => { }) {
    if (!this.wasm) {
        this.warn('lu5 wasm hasn\'t loaded yet.');
        return;
    }
    if (!this.l5) {
        Object.defineProperty(this, 'l5', {
            writable: false,
            value: this.calls._lu5_get_handle()
        });
        // init when running for the first time
        this.calls._lu5_init(this.l5);
    }
    // Allocate memory for lua source
    const source_ptr = this.calls.malloc(source.length);
    // Set lua source in memory
    write_cstr(this.memory, source_ptr, source);
    if (!this.l5) {
        this.calls.free(source_ptr);
        return;
    }
    ;
    switch (this.calls._lu5_setup(this.l5, null, source_ptr)) {
        case 0:
            const target_fps = this.view.getInt32(this.l5 + 8, true);
            let elapsed = 0;
            let fpsInterval = 1000.0 / target_fps;
            let then = window.performance.now();
            // Single frame call
            this.frame = (function (now) {
                if (!this.loop)
                    return;
                requestAnimationFrame(this.frame);
                elapsed = now - then;
                if (target_fps == -1) {
                    then = now;
                    this.calls._lu5_animation_frame(this.l5, elapsed);
                }
                else if (elapsed >= fpsInterval) {
                    then = now;
                    this.calls._lu5_animation_frame(this.l5, elapsed);
                }
            }).bind(this);
            requestAnimationFrame(this.frame);
            break;
        case undefined:
        case 1:
        default:
            this.calls.free(source_ptr);
            done();
            return;
    }
};
LU5.err_prefix = '\x1b[30;41m ERROR \x1b[0m';
LU5.env = {
    getTempRet0() { return 0; },
    saveSetjmp() {
        // // TODO: Figure this out to catch exceptions
        // console.log('saveSetjmp',...arguments);
        return 0;
    },
    testSetjmp() {
        // // TODO: Figure this out to catch exceptions
        // console.log('testSetjmp', ...arguments);
        return 0;
    }
};

;// ./src/common/script.ts
async function get_script_source(script) {
    let src = script.getAttribute('src');
    return (src) ?
        fetch(src).then(r => r.text()) :
        script.textContent;
}
function get_canvas_id(script) {
    if (script.hasAttribute('canvas')) {
        return script.getAttribute('canvas');
    }
    else if (script.hasAttribute('src')) {
        return script.getAttribute('src')
            .split('/').join('').split('.')
            .filter(l => l.length != 0).pop();
    }
    return '';
}
async function get_script() {
    const script = document.querySelectorAll('script[type="text/lua"]')[0];
    if (script == undefined) {
        console.warn('No lua scripts found...');
        return { id: '', source: '' };
    }
    return {
        id: get_canvas_id(script),
        source: await get_script_source(script)
    };
}

;// ./src/lu5-wasm.ts



Object.defineProperty(window, '_lu5_instantiate_script', {
    value: document.currentScript,
    writable: false
});
const DEV = false;
const LU5_WASM_CDN = DEV ? '../dist/lu5.wasm' : `https://unpkg.com/lu5-wasm@latest/dist/lu5.wasm`;
window._get_or_create_by_id = get_or_create_by_id;
// If included as a library, leak this function to the global scope.
if (document.currentScript.hasAttribute('lib')) {
    window.lu5 = {
        init: (wasm_path = LU5_WASM_CDN) => LU5.compile(wasm_path).then(module => LU5.instantiate(module)),
        compile: (wasm_path = LU5_WASM_CDN) => LU5.compile(wasm_path),
        instantiate: (module) => LU5.instantiate(module),
        Console: class {
            constructor() {
                console.warn("`lu5-console` is required to use the DOM console emulator");
                return null;
            }
        }
    };
}
else {
    window.onload = () => {
        let wasm_bin_path = LU5_WASM_CDN;
        // Use wasm attribute to determine lu5 wasm binary url,
        // default is passed argument
        if (window._lu5_instantiate_script.hasAttribute('wasm')) {
            wasm_bin_path = window._lu5_instantiate_script.getAttribute('wasm');
        }
        // Start lu5
        LU5.compile(wasm_bin_path)
            .then(mod => LU5.instantiate(mod))
            .then(vm => vm.attach(1, console))
            .then(vm => vm.attach(2, console))
            .then(async (vm) => {
            // Find lua script
            const { id, source } = await get_script();
            // Set canvas and execute
            return vm.setCanvas(id).then(vm => vm.execute(source));
        })
            .catch(console.error);
    };
}

/******/ })()
;