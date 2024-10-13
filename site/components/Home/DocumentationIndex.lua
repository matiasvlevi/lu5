local luax = require('site/lib/luax');

function DocumentationIndex(props)
    return luax('div', {
        luax('h2', 'Documentation'),
        luax('ul', {class="menu", style="margin: 0 1rem"}, {
            
            luax.map(luax.reverse(props.versions), function(version, i)
                local latest_block = ''
                if (version == props.current_latest) then
                    latest_block = latest_block .. luax('li', {class="index"}, {
                        luax('a', {href='./latest', class="flex", style="gap:0.5rem;align-items:center"}, {
                            luax('span', {style="font-size: 1.25rem"}, 'latest '),
                            luax('span', {class="font-size: 1rem; color:var(--grey)"}, {
                                '(v',props.versions[#props.versions - i + 1],')'
                            }) 
                        }),
                    })
                end


                return latest_block .. luax('li', {class="index", style="font-size: 1.25rem"}, {
                    luax('a', {href='./v' .. version}, 'v' .. version),
                })
            end)
        })
    })
end

return DocumentationIndex;