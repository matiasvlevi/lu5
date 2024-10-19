return {
    -- For Dev: use this when publishing documentation for the upcoming version
    current_latest='0.1.6',
    -- For Prod: use this when publishing documentation with a new release
    -- current_latest=VERSION,

    ga={ gtag_id='G-CYFGDF41F4' },
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
        }
    },
    media={
        assets = "assets",
        thumbnail = "lu5_thumbnail.png",
    },
    cdn = {
        -- -- DEV (manually copied builds from lu5-wasm and lu5-components)
        -- lu5_wasm="/bin/wasm/lu5.wasm",
        -- lu5_wasm_lib="/docs/assets/lu5-wasm-lib.min.js",
        -- lu5_console="/docs/assets/lu5-console.min.js",
        -- lu5_editor="/docs/assets/lu5-console.min.js",

        -- PROD
        lu5_wasm="https://unpkg.com/lu5-wasm@latest/dist/lu5.wasm",
        lu5_wasm_lib="https://unpkg.com/lu5-wasm@latest/dist/lu5-wasm-lib.min.js",
        lu5_console="https://unpkg.com/lu5-components@latest/dist/lu5-console.min.js",
        lu5_editor="https://unpkg.com/lu5-components@latest/dist/lu5-editor.min.js"
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
            },
            css={
                'common.css',
                'style.css',
                'editor.css',
                'lu5-hljs-theme.css'
            }
        },
    }
}
