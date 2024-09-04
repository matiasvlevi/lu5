local luax = require('tasks/lib/luax');
local ver = require('tasks/lib/get_tags');

function Builds(props)
    if (props.class == nil) then
        props.class = ""
    end

    return luax('ul', {class="menu " .. props.class, style="margin: 0 1rem"}, {
        luax.map(luax.reverse(props.versions), function(version, i)
            local zipname= props.fmt(version);

            if (props.url == nil) then
                return luax('li', {class="index"}, luax('span', {class="text"}, zipname));
            end

            local link = props.url ..'/' .. 'v' .. version..'/' .. zipname;
            return luax('li', {class="index underline"}, {
                luax('a', {href=link}, zipname),
            })
        end)
    })
end

function DocumentationVersions(props)
    return luax('div', {
        luax('h2', 'Documentation'),
        luax('ul', {class="menu", style="margin: 0 1rem"}, {
            
            luax.map(luax.reverse(props.versions), function(version, i)
                print(version, props.current_latest)
                if (version == props.current_latest) then
                    return luax('li', {class="index"}, {
                        luax('a', {href='./latest', class="flex", style="gap:0.5rem;align-items:center"}, {
                            luax('span', {style="font-size: 1.25rem"}, 'latest '),
                            luax('span', {class="font-size: 1rem; color:var(--grey)"}, {
                                '(v',props.versions[#props.versions],')'
                            }) 
                        }),
                    })
                end


                return luax('li', {class="index", style="font-size: 1.25rem"}, {
                    luax('a', {href='./v' .. version}, 'v' .. version),
                })
            end)
        })
    })
end

function PictureMosaic(props)
    -- TODO: Take a list from props and map it to this:
    return luax('div', {class="mosaic"}, {
        luax('img',{class="demo",
            height="266px",
            src=(props.root .. props.media.assets .. '/space_game.gif')
        }),
        luax('img', {class="demo",
            height="133px", 
            src=(props.root .. props.media.assets .. '/sphere.gif')
        }),

        luax('img',{class="demo",
            height="200px", 
            src=(props.root .. props.media.assets .. '/collisions.gif')
        }),

    })
end

function DownloadBlock(props)
    return luax('div', {class="download"}, {
        luax('h2', 'Download'),

        -- Shown only on windows
        luax('div', {id="download-Windows"}, {
            luax('a', {href="https://github.com/matiasvlevi/lu5/releases/download/v" .. VERSION .. "/lu5-x86_64-win-"..VERSION..".exe"}, {
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
                luax('code', {class="language-sh"}, 'yay -S lu5')
            }),
            luax('br'),
            luax('span', {class="text"}, 'For any other linux distribution, you can build from source'),
            luax('pre', {style="margin: 1rem;"}, {
                luax('code', {class="language-sh"}, {
                    'git clone https://github.com/matiasvlevi/lu5\n',
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

function ReleaseBuilds(props)
    return luax('div', {
        luax('h2', 'Releases'),
        luax('div', {class="builds", style="gap: 0.5rem;"}, {
            Builds({
                class="tags",
                fmt=function(v)
                    return v
                end,
                versions=props.versions
            }),
            Builds({
                url='https://github.com/matiasvlevi/lu5/releases/download',
                fmt=function(v)
                    return "lu5-x86_64-linux-"..v..".zip"
                end,
                versions=props.versions
            }),
            Builds({
                url='https://github.com/matiasvlevi/lu5/releases/download',
                fmt=function(v)
                    if (ver.to_number(v)[2] < 1) then
                        return "lu5-x86_64-win-"..v..".zip"
                    else
                        return "lu5-x86_64-win-"..v..".exe"
                    end
                end,
                versions=props.versions
            })
        })
    })
end

local function Home(props)
    return luax('div', {class='container flex-col gap-8', id='reactive'}, {
        luax('div', {
            luax('p', { style="max-width:34rem;" }, {
                'Lu5 is a free and open-source Lua interpreter for Creative Coding.',
                luax('br'),
            })
        }),

        luax('div', {class="home-section", style=""}, {
            luax('div', {class="flex-col gap-8"}, {
                DownloadBlock(props),
                DocumentationVersions(props)
            }),
            PictureMosaic(props)
        }),
        ReleaseBuilds(props),
        luax('br')
    });
end

return Home;