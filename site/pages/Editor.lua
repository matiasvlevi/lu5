local luax = require('site/lib/luax')
local Config = require('site/config');

-- Menubar
local Menubar = require('site/components/Editor/Menubar');

-- Icons
local icon_play = require('site/components/Editor/icon_play');
local icon_stop = require('site/components/Editor/icon_stop');

-- CSS
require('site/lib/css');
local editor_css = import('site/components/Editor/editor.css');
local menubar_css = import('site/components/Editor/menubar.css');
local popup_css = import('site/components/Editor/popup.css');

local menubar_buttons = {
    buttons={
        { 
            label= 'File',
            options= {
                { label= 'Save', onclick='window.editor.save()' },
                { label= 'Save As', onclick='window.editor.saveAs()' },
                { label= 'Open', onclick='window.editor.open()' },
                { label= 'Share', onclick='alert(`TODO: Implement share`);' }
            }
        },
        { 
            label= 'Edit',
            options= {
                { label= 'Format Code', onclick='alert(`TODO: Format code`)' }
            }
        },
        { 
            label= 'Sketch',
            options= {
                { label= 'Run', onclick='window.editor.run()' },
                { label= 'Stop', onclick='window.editor.stop()' },
            }
        },
        { 
            label= 'Help',
            options= {
                { label= 'Reference', href='https://matiasvlevi.github.io/lu5/v0.1.7' },
                { label= 'About', href='https://matiasvlevi.github.io/lu5/' },
            }
        }
    }
};

function Editor(props)
    return luax('', {
        luax.css({ editor_css, menubar_css, popup_css }),
        luax('dialog', {class="popup open-sketch"}, {
            luax('p', 'Select sketch'),
            luax('div', {class="flex-col gap-4"}, {
                
                luax('div', {class="sketch-selector", value=0}, {}),
                
                luax('div', {class="flex gap-2"}, {
                    luax('button', {class="formbtn", value="cancel"}, 'Cancel'),
                    luax('button', {class="formbtn", autoFocus=true, value="default"}, 'Confirm')
                })
            })
        }),
        luax('dialog', {class="popup save-sketch"}, {
            luax('p', 'Save sketch'),
            luax('div', {class="flex-col gap-4"}, {
                luax('input', { class="sketch-name", type="text", placeholder="name" }),
                luax('div', {class="flex gap-2"}, {
                    luax('button', {class="formbtn", value="cancel"}, 'Cancel'),
                    luax('button', {class="formbtn", autoFocus=true, value="default"}, 'Confirm')
                })
            })
        }),
        luax('dialog', {class="popup generic"}, {
            luax('div', {class="flex-col gap-4"}, {
                luax('p', ''),
                luax('div', {class="buttons flex gap-2"}, {
                    luax('span', {class="text grey"}, '')
                }),
                luax('button', {class="formbtn", autoFocus=true, value="cancel"}, 'close')
            })
        }),
        luax('main', {class="editor flex-col"}, {
            luax('div', {class="ide-top"}, {
                luax('div', {class="menu flex"}, {
                    luax('a', {class="logo-wrap", href="../"}, {
                        luax('img', {class="logo", src='../'.. props.media.assets..'/logo.svg'}),
                    }),
                    Menubar(menubar_buttons);

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
                    luax('div', {id="lu5-editor", style="height: 70%; min-width: 20rem;"}),

                    luax('div', {class="vertical separator"}),
                    
                    luax('div',{class="flex-col", style="background-color: rgb(34, 34, 34); height:100%; overflow: auto;"}, {
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