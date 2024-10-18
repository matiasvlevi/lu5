local luax = require('site/lib/luax')
local Config = require('site/config');

local icon_play = require('site/components/Editor/icon_play');
local icon_stop = require('site/components/Editor/icon_stop');

function Editor(props)
    return luax('', {
        luax('main', {class="editor flex-col"}, {
            luax('header', {class="ide-top"}, {
                luax('div', {class="menu flex"}, {
                    luax('a', {class="logo-wrap", href="../"}, {
                        luax('img', {class="logo", src='../'.. props.media.assets..'/logo.svg'}),
                    }),
                    luax('button',{ class="menu-item"}, 'File'),
                    luax('button',{ class="menu-item"}, 'Edit'),
                    luax('button',{ class="menu-item"}, 'Sketch'),
                    luax('button',{ class="menu-item"}, 'Help'),

                }),
                luax('div', {class="flex", style="max-height: 50px; margin: 0.5rem 0.5rem;"}, {
                    luax('button', {class="action", onclick="run()"}, {
                        icon_play(0.5)
                    }),
                    luax('button', {class="action", onclick="stop()"}, 
                        icon_stop(0.5)
                    ),
                })
            }),
            luax('div', {class="ide-area"}, {
                luax('div', {class="ide-code-area flex-col flex-grow"}, {
                    luax('div', {id="lu5-editor", style="height: 65%;"}),

                    luax('div', {class="vertical separator"}),
                    
                    luax('div',{class="flex-col", style="height:100%"}, {
                        luax('div', {style="height: min-content; padding: 0.5rem;", class="bg-darkgrey"}, {
                            luax('span', {class="text white"}, 'Console')
                        }),
                        luax('div', {id="lu5-console", class="flex-grow"})
                    })
                }),

                luax('div', {class="horizontal separator"}),
                
                luax('div', {class="ide-play-area flex-grow"}, {
                    luax('canvas', {id="lu5-sketch"})
                })
            })
        })
    })
end

return Editor;