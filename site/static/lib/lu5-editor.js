import * as __WEBPACK_EXTERNAL_MODULE_https_matiasvlevi_github_io_lu5_assets_codemirror_min_js_8b5f8f67__ from "https://matiasvlevi.github.io/lu5/assets/codemirror.min.js";
import * as __WEBPACK_EXTERNAL_MODULE_https_unpkg_com_lu5_components_latest_dist_lu5_console_min_js_2f653820__ from "https://unpkg.com/lu5-components@latest/dist/lu5-console.min.js";
import * as __WEBPACK_EXTERNAL_MODULE_https_unpkg_com_lu5_wasm_latest_dist_lu5_wasm_lib_min_js_047a1424__ from "https://unpkg.com/lu5-wasm@latest/dist/lu5-wasm-lib.min.js";
/******/ var __webpack_modules__ = ({

/***/ 43:
/***/ (function(__unused_webpack_module, exports, __webpack_require__) {


var __createBinding = (this && this.__createBinding) || (Object.create ? (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    var desc = Object.getOwnPropertyDescriptor(m, k);
    if (!desc || ("get" in desc ? !m.__esModule : desc.writable || desc.configurable)) {
      desc = { enumerable: true, get: function() { return m[k]; } };
    }
    Object.defineProperty(o, k2, desc);
}) : (function(o, m, k, k2) {
    if (k2 === undefined) k2 = k;
    o[k2] = m[k];
}));
var __setModuleDefault = (this && this.__setModuleDefault) || (Object.create ? (function(o, v) {
    Object.defineProperty(o, "default", { enumerable: true, value: v });
}) : function(o, v) {
    o["default"] = v;
});
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (k !== "default" && Object.prototype.hasOwnProperty.call(mod, k)) __createBinding(result, mod, k);
    __setModuleDefault(result, mod);
    return result;
};
var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", ({ value: true }));
const console_1 = __importDefault(__webpack_require__(567));
const lu5 = __importStar(__webpack_require__(196));
const codemirror_1 = __webpack_require__(214);
let tabSize = new codemirror_1.Compartment;
const initialText = `function setup()
  createWindow(400, 400);
end

function draw()
  background('purple');
end`;
class Editor {
    vm;
    module;
    editor;
    console;
    id;
    constructor(id = 'lu5-editor') {
        this.id = id;
        this.vm = null;
        this.module = null;
        this.editor = null;
        this.console = null;
    }
    async init() {
        const targetElement = document.getElementById(this.id);
        this.module = await lu5.compile();
        this.editor = new codemirror_1.EditorView({
            doc: initialText,
            extensions: [
                (0, codemirror_1.lineNumbers)(),
                (0, codemirror_1.highlightSpecialChars)(),
                (0, codemirror_1.history)(),
                (0, codemirror_1.drawSelection)(),
                codemirror_1.EditorState.allowMultipleSelections.of(true),
                (0, codemirror_1.indentOnInput)(),
                (0, codemirror_1.syntaxHighlighting)(codemirror_1.defaultHighlightStyle, { fallback: true }),
                codemirror_1.keymap.of([
                    ...codemirror_1.defaultKeymap,
                    ...codemirror_1.historyKeymap,
                    codemirror_1.indentWithTab
                ]),
                tabSize.of(codemirror_1.EditorState.tabSize.of(2))
            ],
            parent: targetElement,
        });
        this.console = new console_1.default('lu5-console', {
            hide_if_can: false,
            resize: 'vertical'
        });
        return this;
    }
    async run() {
        if (!this.editor || !this.module || !this.console)
            return;
        const source = this.editor.state.doc.toString();
        if (this.vm) {
            await this.stop();
        }
        this.vm = await (lu5.instantiate(this.module)
            .then(vm => vm.setCanvas('lu5-sketch'))
            .then(vm => vm.attach(1, this.console))
            .then(vm => vm.attach(2, this.console)));
        if (!this.vm)
            return;
        return await this.vm.execute(source);
    }
    async stop() {
        if (!this.vm)
            return;
        this.vm.loop = false;
        await this.vm.clear().reset();
        this.vm = null;
        return this;
    }
}
exports["default"] = Editor;


/***/ }),

/***/ 156:
/***/ (function(__unused_webpack_module, exports, __webpack_require__) {


var __importDefault = (this && this.__importDefault) || function (mod) {
    return (mod && mod.__esModule) ? mod : { "default": mod };
};
Object.defineProperty(exports, "__esModule", ({ value: true }));
const editor_1 = __importDefault(__webpack_require__(43));
const panes_1 = __webpack_require__(839);
window.onload = () => {
    window.editor = new editor_1.default();
    window.editor.init();
    window.run = function () { window.editor.run(); };
    window.stop = function () { window.editor.stop(); };
    (0, panes_1.init_panes)();
};


/***/ }),

/***/ 839:
/***/ ((__unused_webpack_module, exports) => {


Object.defineProperty(exports, "__esModule", ({ value: true }));
exports.dragElement = dragElement;
exports.init_panes = init_panes;
function dragElement(element, direction) {
    let md;
    const first = element.previousSibling;
    const second = element.nextSibling;
    element.onmousedown = onMouseDown;
    function onMouseDown(e) {
        if (direction === "H") {
            md = {
                e,
                offsetLeft: element.offsetLeft,
                offsetTop: element.offsetTop,
                firstWidth: first.offsetWidth,
                secondWidth: second.offsetWidth
            };
        }
        else {
            md = {
                e,
                offsetLeft: element.offsetLeft,
                offsetTop: element.offsetTop,
                firstWidth: first.offsetHeight,
                secondWidth: second.offsetHeight
            };
        }
        document.onmousemove = onMouseMove;
        document.onmouseup = () => {
            document.onmousemove = document.onmouseup = null;
        };
    }
    function onMouseMove(e) {
        var delta = {
            x: e.clientX - md.e.clientX,
            y: e.clientY - md.e.clientY
        };
        if (direction === "H") // Horizontal
         {
            // Prevent negative-sized elements
            delta.x = Math.min(Math.max(delta.x, -md.firstWidth), md.secondWidth);
            element.style.left = md.offsetLeft + delta.x + "px";
            const first_width = (md.firstWidth + delta.x);
            if (first_width < 20 * 16)
                return;
            first.style.width = (md.firstWidth + delta.x) + "px";
            second.style.width = (md.secondWidth - delta.x) + "px";
        }
        else if (direction === "V") {
            delta.y = Math.min(Math.max(delta.y, -md.firstWidth), md.secondWidth);
            const second_height = (md.secondWidth - delta.y);
            if (second_height < 3 * 24)
                return;
            element.style.top = md.offsetTop + delta.y + "px";
            const first_height = (md.firstWidth + delta.y);
            first.style.height = first_height + "px";
            second.style.height = second_height + "px";
        }
    }
}
function init_panes() {
    dragElement(document.querySelector('.horizontal.separator'), 'H');
    dragElement(document.querySelector('.vertical.separator'), 'V');
}


/***/ }),

/***/ 214:
/***/ ((module) => {

module.exports = __WEBPACK_EXTERNAL_MODULE_https_matiasvlevi_github_io_lu5_assets_codemirror_min_js_8b5f8f67__;

/***/ }),

/***/ 567:
/***/ ((module) => {

module.exports = __WEBPACK_EXTERNAL_MODULE_https_unpkg_com_lu5_components_latest_dist_lu5_console_min_js_2f653820__;

/***/ }),

/***/ 196:
/***/ ((module) => {

module.exports = __WEBPACK_EXTERNAL_MODULE_https_unpkg_com_lu5_wasm_latest_dist_lu5_wasm_lib_min_js_047a1424__;

/***/ })

/******/ });
/************************************************************************/
/******/ // The module cache
/******/ var __webpack_module_cache__ = {};
/******/ 
/******/ // The require function
/******/ function __webpack_require__(moduleId) {
/******/ 	// Check if module is in cache
/******/ 	var cachedModule = __webpack_module_cache__[moduleId];
/******/ 	if (cachedModule !== undefined) {
/******/ 		return cachedModule.exports;
/******/ 	}
/******/ 	// Create a new module (and put it into the cache)
/******/ 	var module = __webpack_module_cache__[moduleId] = {
/******/ 		// no module.id needed
/******/ 		// no module.loaded needed
/******/ 		exports: {}
/******/ 	};
/******/ 
/******/ 	// Execute the module function
/******/ 	__webpack_modules__[moduleId].call(module.exports, module, module.exports, __webpack_require__);
/******/ 
/******/ 	// Return the exports of the module
/******/ 	return module.exports;
/******/ }
/******/ 
/************************************************************************/
/******/ 
/******/ // startup
/******/ // Load entry module and return exports
/******/ // This entry module is referenced by other modules so it can't be inlined
/******/ var __webpack_exports__ = __webpack_require__(156);
/******/ 
