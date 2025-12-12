
--- Site environement 
--  Set `false` to Build the site for local development 
--  Set `true` to Build the site for deployment on github pages 
local PROD=true;

--- Documentation presentation
--  Specify the previous release tag when publishing documentation for an unreleased version (no tag yet)
--  Specify `LAST_RELEASE=VERSION` when publishing documentation for new released version, make sure lu5's VERSION is set to the new tag.
local LAST_RELEASE='0.1.6'

return {
    metadata={
        author      = "Matias Vazquez-Levi",
        github_url  = "https://github.com/matiasvlevi/lu5", 
        url         = "https://matiasvlevi.github.io/lu5",
        title       = "lu5, a Lua Interpreter for Creative Coding",

        keywords    = { "Lua", "Creative Coding", "p5.js", 
                        "OpenGL", "Lua Interpreter", "programming", 
                        "coding", "learn code" },

        description = "lu5 is a Lua interpreter for Creative Coding. "..
                  "lu5 serves as a tool for creating games, simulations and art. "..
                  "It is designed to render 2D and 3D graphics, and provides a "..
                  "simple and expressive API similar to p5.js. ",
        alt_descriptions = {
            reference = "Reference documentation for lu5, this documentation provides "..
                        "descriptions and examples of lu5's functionality. ",
            editor = "A web editor for lu5, a Lua interpreter for Creative Coding. "..
                    "lu5 leverages the power of WebAssembly to run a Lua interpreter in your browser."
        }
    },
    media={
        assets = "assets",
        thumbnail = "lu5_thumbnail.png",
    },
    build={
        dest="./docs",
        source={
            headers='./src/bindings',
            static='./site/static',
            js={
                'menu.js',
                'image.js',
                'download.js',
                'search.js'
            },
            lib={
                'lu5-wasm.min.js',
                'lu5-wasm-lib.min.js',
                'lu5-console.min.js',
                'lu5-editor.min.js',
                'codemirror.min.js'
            },
            css={
                'common.css',
                'docs.css',
                'lu5-hljs-theme.css'
            }
        },
    },
    ga={ gtag_id='G-CYFGDF41F4' },
    cdn = {
        -- for DEV (manually copied builds from lu5-wasm and lu5-components)
        lu5_wasm     = PROD and "https://unpkg.com/lu5-wasm@latest/dist/lu5.wasm"                 or "/bin/wasm/lu5.wasm",
        lu5_wasm_lib = PROD and "https://unpkg.com/lu5-wasm@latest/dist/lu5-wasm-lib.min.js"      or "/docs/assets/lu5-wasm-lib.min.js",
        lu5_console  = PROD and "https://unpkg.com/lu5-components@latest/dist/lu5-console.min.js" or "/docs/assets/lu5-console.min.js",
        lu5_editor   = PROD and "https://unpkg.com/lu5-components@latest/dist/lu5-editor.min.js"  or "/docs/assets/lu5-editor.min.js",
        codemirror   = PROD and "https://matiasvlevi.github.io/lu5/assets/codemirror.min.js"      or "../assets/codemirror.min.js",
    },
    current_latest=LAST_RELEASE or VERSION
}
