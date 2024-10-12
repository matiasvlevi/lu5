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
/************************************************************************/
var __webpack_exports__ = {};
/* unused harmony export LU5Console */
class LU5Console {
    constructor(id = 'lu5-console') {
        this.box = window._get_or_create_by_id && window._get_or_create_by_id('div', id);
        this.box.style.cssText = `
            background-color: #222;
            color: #ddd;
            font-family: Monospace;
    
            display: none;
            flex-direction: column-reverse;
    
            padding: 0.4rem;

            width: auto;
            height: auto;

            overflow-y: scroll;  
            scrollbar-color: #aaa #444;
            scrollbar-width: thin;
            ${this.box.hasAttribute('style') ?
            this.box.getAttribute('style') : ''}
        `;
        LU5Console.injectAnsiColorCSS();
    }
    log(str) {
        // Add line
        const line = document.createElement('span');
        line.style.padding = `0.25rem`;
        line.innerHTML = LU5Console.format_colors(str);
        this.update(line);
    }
    warn(str) {
        const line = document.createElement('span');
        line.style.padding = `0.25rem`;
        line.style.backgroundColor = '#775522';
        line.style.color = '#FFF';
        line.style.fontWeight = 'bold';
        line.innerHTML = LU5Console.warn_icon + ' ' + LU5Console.format_colors(str);
        this.update(line);
    }
    error(str) {
        const line = document.createElement('span');
        line.style.padding = `0.25rem`;
        line.style.backgroundColor = '#772222';
        line.innerHTML = LU5Console.format_colors(str);
        this.update(line);
    }
    clear() {
        this.box.style.display = 'none';
        this.box.innerHTML = '';
    }
    update(line) {
        this.box.style.display = 'flex';
        setTimeout(() => {
            // Clear oldest lines
            if (this.box.childNodes.length > 32)
                this.box.lastChild.remove();
            // Add new line
            this.box.insertBefore(line, this.box.firstChild);
        });
    }
    static injectAnsiColorCSS() {
        if (document.querySelector('style#ansi') !== null)
            return;
        const style = document.createElement('style');
        style.setAttribute('id', 'ansi');
        style.innerHTML = `
            span.ansi-30 { color: black; }
            span.ansi-31 { color: red; }
            span.ansi-32 { color: green; }
            span.ansi-33 { color: yellow; }
            span.ansi-34 { color: blue; }
            span.ansi-35 { color: magenta; }
            span.ansi-36 { color: cyan; }
            span.ansi-37 { color: white; }

            span.ansi-90 { color: #9B9B9B; }
            span.ansi-91 { filter: brightness(0.5); color: red; }
            span.ansi-92 { filter: brightness(0.5); color: green; }
            span.ansi-93 { filter: brightness(0.5); color: yellow; }
            span.ansi-94 { filter: brightness(0.5); color: blue; }
            span.ansi-95 { filter: brightness(0.5); color: magenta; }
            span.ansi-96 { filter: brightness(0.5); color: cyan; }
            span.ansi-97 { filter: brightness(0.5); color: white; }

            span.ansi-30-41 { background-color: red; color: black; white-space-collapse: break-spaces; font-weight: bold;}
        `;
        document.getElementsByTagName('head')[0].appendChild(style);
    }
    static format_colors(str) {
        return str.replaceAll(/\x1b\[(0)?([0-9;]*)m/g, (_match, isReset, code) => {
            return isReset ? '</span>' : `<span class="ansi-${code.replaceAll(';', '-')}">`;
        });
    }
}
LU5Console.warn_icon = `<span style="color: yellow; font-size: 1.4em; font-weight: normal; white-space-collapse: preserve; margin: 0px 0px 0px 0.2em;">` +
    `&#x26A0;` +
    `</span>`;
window.lu5.Console = LU5Console;

/******/ })()
;