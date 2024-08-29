return {
    ga={
        gtag_id='G-CYFGDF41F4'
    },
    metadata={
        url         = "https://matiasvlevi.github.io/lu5",
        title       = "lu5, a Lua Interpreter for Creative Coding",
        author      = "Matias Vazquez-Levi",
        keywords    = { "Lua", "Creative Coding", "p5.js", "OpenGL", "Lua Interpreter", "programming", "coding", "learn code" },
        description = "A Lua interpreter for Creative Coding. "..
        "Provides a similar experience to well known p5.js library. "..
        "Perfect learning or quickly running Lua graphical windows.",
    },
    media={
        assets = "assets",
        thumbnail = "lu5_thumbnail.png",
    },
    build={
        dest="./docs",
        source={
            headers='./src/bindings',
            static='./tasks/static',
            js={
                'lu5.js',
                'index.js',
                'hljs.min.js'
            },
            css={
                'style.css',
                'lu5-hljs-theme.css'
            }
        },
    }
}
