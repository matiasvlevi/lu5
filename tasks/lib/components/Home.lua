local luax = require('tasks/lib/luax')

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

local function Home(props)
    return luax('div', {class='container flex flex-col', style="gap: 1rem;", id='reactive'}, {
        luax('div', {
            luax('p', { style="max-width:34rem;" }, {
                'Lu5 is a free and open-source Lua interpreter for Creative Coding.',
                luax('br'),
            })
        }),
        luax('div', {
            luax('h2', 'Documentation'),
            luax('ul', {class="menu", style="margin: 0 1rem"}, {
                luax('li', {class="index"}, {
                    luax('a', {href='./latest', class="flex", style="gap:0.5rem;align-items:center"}, {
                        luax('span', {style="font-size: 1.25rem"}, 'latest '),
                        luax('span', {class="font-size: 1rem; color:var(--grey)"}, {
                            '(v',props.versions[#props.versions],')'
                        }) 
                    }),
                }),
                luax.map(luax.reverse(props.versions), function(version, i)
                    return luax('li', {class="index", style="font-size: 1.25rem"}, {
                        luax('a', {href='./v'..version}, 'v' .. version),
                    })
                end)
            })
        }),

        luax('div', {style="margin-top: 2rem"}, {
            luax('h2', 'Builds'),
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
                        return "lu5-x86_64-win-"..v..".zip"
                    end,
                    versions=props.versions
                })
            })
        }),
        luax('br')
    });
end

return Home;