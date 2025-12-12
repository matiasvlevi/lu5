local luax = require('site/lib/luax');

local Download = require('site/components/Home/Download');
local DocumentationIndex = require('site/components/Home/DocumentationIndex');
local PictureMosaic = require('site/components/Home/PictureMosaic');
local Releases = require('site/components/Home/Releases');

local function Home(props)
    return luax('div', {class='container flex-col gap-8', id='reactive'}, {
        luax('div', {
            luax('p', { style="max-width:34rem;" }, {
                'Lu5 is a free and open-source Lua interpreter for Creative Coding.',
                luax('br')
            })
        }),
        luax('div', {class="home-section", style=""}, {
            luax('div', {class="flex-col gap-8"}, {
                luax('div', {
                    luax('h2', 'CDN'),
                    luax('span', {class="text"}, {
                        'lu5 can now run on the web with ',
                        luax('a', {href='https://github.com/matiasvlevi/lu5-wasm'}, 'lu5-wasm')
                    }),
                    luax('pre', {
                        luax('code', {class="language-html hljs cdn"}, {
                            '&lt;script src="https://unpkg.com/lu5-wasm@latest/dist/lu5-wasm.min.js"&gt;&lt;/script&gt;'
                        })
                    }),
                }),

                luax('div', {}, {
                    luax('p', {
                        'you can try our ', luax('a', {href="./editor"}, {'Online Editor Here'})
                    })
                }),

                Download(props),
                DocumentationIndex(props)
            }),
            PictureMosaic(props)
        }),
        Releases(props),
        luax('br')
    });
end

return Home;