var __webpack_exports__ = {};
// This entry need to be wrapped in an IIFE because it uses a non-standard name for the exports (exports).
(() => {
var exports = __webpack_exports__;

Object.defineProperty(exports, "BJ", ({ value: true }));
exports.UC = _createElement;
const defaultOptions = {
    hide_if_can: true,
    resize: 'none'
};
function _createElement(tag, id, host = document.body) {
    let elem = document.getElementById(id);
    if (elem === null) {
        elem = document.createElement(tag);
        elem.setAttribute('id', id);
        if (host)
            host.appendChild(elem);
    }
    return elem;
}
class Console {
    box;
    options;
    constructor(id = 'lu5-console', options = {}) {
        options = { ...defaultOptions, ...options };
        this.box = _createElement('div', id);
        this.box.style.cssText = `
            background-color: #222;
            color: #ddd;
            font-family: Monospace;

            width: auto;
            height: auto;
    
            display: ${options.hide_if_can ? 'none' : 'flex'};
            ${options.hide_if_can ? '' : 'min-height: 1rem;'}
            flex-direction: column-reverse;
    
            padding: 0.4rem;

            overflow-y: scroll;  
            scrollbar-color: #aaa #444;
            scrollbar-width: thin;
            ${this.box.hasAttribute('style') ?
            this.box.getAttribute('style') : ''}
        `;
        this.options = options;
        Console.injectAnsiColorCSS();
    }
    log(str) {
        // Add line
        const line = document.createElement('span');
        line.style.padding = `0.25rem`;
        line.innerHTML = Console.format_colors(str);
        this.update(line);
    }
    static warn_icon = `<span style="color: yellow; font-size: 1.4em; font-weight: normal; white-space-collapse: preserve; margin: 0px 0px 0px 0.2em;">` +
        `&#x26A0;` +
        `</span>`;
    warn(str) {
        const line = document.createElement('span');
        line.style.padding = `0.25rem`;
        line.style.backgroundColor = '#775522';
        line.style.color = '#FFF';
        line.style.fontWeight = 'bold';
        line.innerHTML = Console.warn_icon + ' ' + Console.format_colors(str);
        this.update(line);
    }
    error(str) {
        const line = document.createElement('span');
        line.style.padding = `0.25rem`;
        line.style.backgroundColor = '#772222';
        line.innerHTML = Console.format_colors(str);
        this.update(line);
    }
    clear() {
        if (this.options.hide_if_can)
            this.box.style.display = 'none';
        this.box.innerHTML = '';
    }
    update(line) {
        // Cooldown to prevent being too demanding
        const epsilon = 5;
        this.box.style.display = 'flex';
        setTimeout(() => {
            // Clear oldest lines
            if (this.box.childNodes.length > 32)
                if (this.box.lastChild)
                    this.box.lastChild.remove();
            // Add new line
            this.box.insertBefore(line, this.box.firstChild);
        }, epsilon);
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
exports.Ay = Console;

})();

var __webpack_exports___esModule = __webpack_exports__.BJ;
var __webpack_exports___createElement = __webpack_exports__.UC;
var __webpack_exports__default = __webpack_exports__.Ay;
export { __webpack_exports___esModule as __esModule, __webpack_exports___createElement as _createElement, __webpack_exports__default as default };
