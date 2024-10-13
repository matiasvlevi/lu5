local luax = require('site/lib/luax');

function Download(props)
    return luax('div', {class="download"}, {

        luax('h2', 'Download'),

        -- Shown only on windows
        luax('div', {id="download-Windows"}, {
            luax('a', {href= props.meta.github_url .. "/releases/download/v" .. VERSION .. "/lu5-x86_64-win-"..VERSION..".exe"}, {
                luax('button', {class="download"}, {
                    luax('img', {class="icon", width="24px", src=props.root .. props.media.assets .. '/download.svg'}),
                    luax('span', {class="flex gap-2"}, {
                        'Download for Windows'
                    }),
                })
            })
        }),

        -- Shown only on Linux
        luax('div', {id="download-Linux"}, {

            luax('span', {class="text"}, 'On arch based systems, you can install lu5 from the AUR.'),
            luax('pre', {style="margin: 1rem;"}, {
                luax('code', {class="no-hljs"}, 'yay -S lu5')
            }),
            luax('br'),
            luax('span', {class="text"}, 'For any other linux distribution, you can build from source'),
            luax('pre', {style="margin: 1rem;"}, {
                luax('code', {class="no-hljs"}, {
                    'git clone ', props.meta.github_url, ' --branch v', props.current_latest, '\n',
                    'cd lu5\n',
                    'make\n'
                })
            })
        }),

        -- Shown only on Mac
        luax('div', {id="download-Mac"}, {
            luax('div', {
                luax('span', {class="text"}, 'lu5 is not available on Mac OS :(')
            })
        }),

        -- Shown only on Unknown devices
        luax('div', {id="download-fallback"}, {
            luax('div', {
                luax('span', {class="text small"}, 'lu5 is not available on mobile devices :(')
            })
        }),
    })
end

return Download;